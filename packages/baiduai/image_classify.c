#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include <webclient.h>
#include <cJSON.h>
#include <dfs_posix.h>
#include <packages/baiduai/base/http.h>

#ifdef DRV_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif
#define LOG_TAG             "baiduai_image"
#include <drv_log.h>

//#define BD_AI_BAIKE //�Ƿ�֧�ְٶȰٿ�

#define MAX_ENCODE_IMAGE_SIZE  24576 //����������ͼ���С
#define MAX_IMAGE_SIZE         16384 //ͼ�������С

//��ȡTOKEN��API
const char *access_token = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=KZBGteXWwP1X5ueGjpv6Zj0G&client_secret=eXiWixjzPbbijmEWeWclZSaILU1cpB0j";

//�ٶ�AI��APIֵ
const char *BAIDU_AI_API[] = {
    "https://aip.baidubce.com/rest/2.0/face/v3/search",
    "https://aip.baidubce.com/rest/2.0/image-classify/v2/advanced_general", /* advanced General Url */
    "https://aip.baidubce.com/rest/2.0/image-classify/v2/dish",             /* dish Detect Url*/
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/car",              /* car Detect Url */
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/vehicle_detect",   /* vehicle Detect Url */
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/vehicle_damage",
    "https://aip.baidubce.com/rest/2.0/image-classify/v2/logo",
    "https://aip.baidubce.com/rest/2.0/realtime_search/v1/logo/add",
    "https://aip.baidubce.com/rest/2.0/realtime_search/v1/logo/delete",
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/animal",
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/plant",
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/object_detect",
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/landmark",
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/flower",
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/classify/ingredient",
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/redwine",
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/currency",
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/realtime_search/dish/add",
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/realtime_search/dish/search",
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/realtime_search/dish/delete",
    "https://aip.baidubce.com/rest/2.0/image-classify/v1/multi_object_detect",
    "https://aip.baidubce.com/api/v1/solution/direct/imagerecognition/combination"
};

//����Ҫ��Ե�һ��������ѧ�����ȥ����һ����������ν���JSON
rt_err_t baidu_ai_sample(char *filename)
{
    unsigned char *ai_token = RT_NULL; //���뵽��token��ֵ
    int ai_token_len = 0; //���뵽��token�ĳ���
    rt_err_t result = RT_EOK; //��ʱ��ķ���ֵ��Ĭ����OK������
    int fd; //file id��ļ�ID
    unsigned char *buff_ptr = RT_NULL; //RGB���ݵ�ָ��
    unsigned char *encode_ptr = RT_NULL; //base64����������ָ��

    rt_size_t total_length, encode_size, post_uri_size; //�ܳ��ȡ������ĳ��ȡ����͵�URI�ĳ���

    rt_uint8_t *post_uri = RT_NULL; //URI��ֵ��ָ��

    const char image_arg[] = "image=";
    rt_uint8_t image_arg_len = rt_strlen(image_arg); //URI��̶��Ķ���

    //const char image_type_arg[] = "image_type=";
    //rt_uint8_t image_type_arg_len = rt_strlen(image_type_arg); //URI��̶��Ķ���

    //const char image_type_base64_arg[] = "BASE64";
    //rt_uint8_t image_type_base64_arg_len = rt_strlen(image_type_base64_arg); //URI��̶��Ķ���

    //const char group_id_list_arg[] = "group_id_list=";
    //rt_uint8_t group_id_list_arg_len = rt_strlen(group_id_list_arg); //URI��̶��Ķ���

    //const char group_id_arg[] = "guet";
    //rt_uint8_t group_id_arg_len = rt_strlen(group_id_arg); //URI��̶��Ķ���

    const char token_arg[] = "?access_token=";
    rt_uint8_t token_arg_len = rt_strlen(token_arg); //URI��̶��Ķ���

    const char image_head_arg[] = "{\"image\":\"";
    rt_uint8_t image_head_arg_len = rt_strlen(image_head_arg); //ͼƬ���ݵ�ͷ

    const char image_tail_arg[] = "\",";
    rt_uint8_t image_tail_arg_len = rt_strlen(image_tail_arg); //ͼƬ���ݵ�β

    const char image_type_base64_arg[] = "\"image_type\":\"BASE64\",";
    rt_uint8_t image_type_base64_arg_len = rt_strlen(image_type_base64_arg); //ͼƬ����

    const char group_id_list_arg[] = "\"group_id_list\":\"guet\"}";
    rt_uint8_t group_id_list_arg_len = rt_strlen(group_id_list_arg); //ʶ���б�

    //const char post_data_test[]="{\"image\":\"027d8308a2ec665acb1bdf63e513bcb9\",\"image_type\":\"BASE64\",\"group_id_list\":\"guet\"}";
    //rt_uint8_t post_data_test_len = rt_strlen(post_data_test);
#ifdef BD_AI_BAIKE
    const char baike_args[] = "&baike_num=5";
    rt_uint8_t baike_args_len = rt_strlen(baike_args);
#endif

    rt_uint8_t *post_data = RT_NULL; //���͵�����
    rt_size_t post_data_size = 0; //�������ݵĴ�С
    //rt_size_t percent_len = 0; //�ٷֱȱ��������ݳ���


    static int index = 0; //����

    /* step1: get token */ //��һ������ȡtoken
    ai_token = rt_malloc(256); //���벿�ֿռ䴢��token
    if (ai_token == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto __exit;
    } //�ж��Ƿ����뵽�˿ռ�
    LOG_D("start to get baidu ai token"); //LOG
    ai_token_len = get_ai_token(access_token, ai_token); //��ȡtoken����ai_token�������䳤��
    LOG_D("token : %s", ai_token); //LOG
    if (ai_token_len <= 0)
    {
        result = -RT_ENOMEM;
        goto __exit;
    } //�ж�û�����뵽token
    LOG_D("get baidu ai token success"); //LOG

    /* step2: get picture data */ //��ȡͼ������
    LOG_D("open filename : %s", filename); //LOG

    fd = open(filename, 0, O_RDONLY); //��ֻ���ķ�ʽ��ĳ���ļ�
    if (fd < 0)
    {
        rt_kprintf("open file: %s failed\n", filename);
        result = -RT_ENOMEM;
        goto __exit;
    } //�ж��Ƿ���ļ�

    buff_ptr = rt_malloc(MAX_IMAGE_SIZE); //ΪͼƬ��������ռ�
    if (buff_ptr == RT_NULL)
    {
        rt_kprintf("no memory\n");
        result = -RT_ENOMEM;
        close(fd);
        goto __exit;
    } //�жϿռ��Ƿ�����ɹ�

    total_length = read(fd, buff_ptr, MAX_IMAGE_SIZE); //�ܳ��ȣ���Ķ�������ͼƬ��С���������ͼƬ��С
    if (total_length > MAX_IMAGE_SIZE)
    {
        LOG_E("image size too big.\n");
        result = -RT_ERROR;
        goto __exit;
    } //�ж�ͼƬ�Ƿ񳬱�
    LOG_D("open file success.");
    /* close file and release memory */
    close(fd); //�ر��ļ�

    /* step3: encode image */ //ͼƬbase64����
    LOG_D("encode image start.");
    encode_ptr = rt_malloc(MAX_ENCODE_IMAGE_SIZE); //����ռ�base64������ͼƬ����
    encode_size = encode(buff_ptr, total_length, encode_ptr); //�����Ĵ�С���أ����������ݷ���

    /* step4: get post uri */ //��ȡ����URI
    index = strlen(BAIDU_AI_API[0]); //��ȡAPI�ĳ���
    post_uri_size = index; //��ʼ��URI�ĳ�ʼ����ΪAPI�ĳ���
    post_uri = rt_malloc(256); //ΪURI����ռ�

    rt_memcpy(post_uri, BAIDU_AI_API[0], post_uri_size); //װ��Bai_Du API
    rt_memcpy(&post_uri[post_uri_size], token_arg, token_arg_len); //װ��tokenǰ׺
    post_uri_size += token_arg_len; //�ۼ�URI����
    rt_memcpy(&post_uri[post_uri_size], ai_token, ai_token_len); //װ��token��ֵ
    post_uri_size += ai_token_len; //�ۼ�URI����

    LOG_D("post uri: %s", post_uri); //LOG

    /* step5: percentage code post data */ //�ٷֱȱ���image
#ifdef BD_AI_BAIKE
    post_data = rt_malloc(encode_size * 3 + image_arg_len + baike_args_len);
#else
    post_data = rt_malloc(image_head_arg_len + encode_size +image_tail_arg_len + image_type_base64_arg_len +group_id_list_arg_len); //���루����ͼƬ���ݴ�С�ͳ��� + ͼƬ����ǰ׺�ĳ��ȣ�
#endif

    if (post_data == RT_NULL)
    {
        LOG_E("no memory.\n");
        result = -RT_ERROR;
        goto __exit;
    } //�жϿռ��Ƿ�����ɹ�
    rt_memcpy(post_data, image_head_arg, image_head_arg_len); //װ��ͼƬ����ǰ׺
    post_data_size = image_head_arg_len;//�����ܳ���

    rt_memcpy(&post_data[post_data_size], encode_ptr, encode_size); //װ��ͼƬ����
    post_data_size += encode_size; //�����ܳ���

    rt_memcpy(&post_data[post_data_size], image_tail_arg, image_tail_arg_len); //װ��ͼƬ���ݺ�׺
    post_data_size += image_tail_arg_len; //�����ܳ���

    rt_memcpy(&post_data[post_data_size], image_type_base64_arg, image_type_base64_arg_len); //װ��ͼƬ����
    post_data_size += image_type_base64_arg_len; //�����ܳ���

    rt_memcpy(&post_data[post_data_size], group_id_list_arg, group_id_list_arg_len); //װ���û���
    post_data_size += group_id_list_arg_len; //�����ܳ���


#ifdef BD_AI_BAIKE
    if (percent_len < encode_size * 3)
    {
        rt_memcpy(&post_data[post_data_size], baike_args, baike_args_len);
        post_data_size += baike_args_len;
    }
#endif


    LOG_D("post data: %s", post_data); //LOG
    /* step: upload image to baidu ai */
    get_ai_result((const char *)post_uri, (const char *)post_data, post_data_size); //��ȡ���

__exit:

    if(ai_token)
    {
        rt_free(ai_token);
    }

    if (buff_ptr)
    {
        rt_free(buff_ptr);
    }

    if (encode_ptr)
    {
        rt_free(encode_ptr);
    }

    if (post_data)
    {
        rt_free(post_data);
    }
    
    return result;

}

static int baidu_ai(int argc, char **argv)
{
    if (argc == 2)
    {
        baidu_ai_sample(argv[1]);
    }
    else
    {
        rt_kprintf("baidu_ai xxx.jpg\n");
    }
    
    return RT_EOK;
}
MSH_CMD_EXPORT(baidu_ai, baidu_ai sample);
