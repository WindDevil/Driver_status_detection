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

//#define BD_AI_BAIKE //是否支持百度百科

#define MAX_ENCODE_IMAGE_SIZE  24576 //编码后的最大的图像大小
#define MAX_IMAGE_SIZE         16384 //图像的最大大小

//获取TOKEN的API
const char *access_token = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=KZBGteXWwP1X5ueGjpv6Zj0G&client_secret=eXiWixjzPbbijmEWeWclZSaILU1cpB0j";

//百度AI的API值
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

//终于要面对的一个函数，学会如何去请求一个东西，如何解析JSON
rt_err_t baidu_ai_sample(char *filename)
{
    unsigned char *ai_token = RT_NULL; //申请到的token的值
    int ai_token_len = 0; //申请到的token的长度
    rt_err_t result = RT_EOK; //到时候的返回值，默认是OK就行了
    int fd; //file id嘛，文件ID
    unsigned char *buff_ptr = RT_NULL; //RGB数据的指针
    unsigned char *encode_ptr = RT_NULL; //base64编码后的数据指针

    rt_size_t total_length, encode_size, post_uri_size; //总长度、编码后的长度、发送的URI的长度

    rt_uint8_t *post_uri = RT_NULL; //URI的值的指针

    const char image_arg[] = "image=";
    rt_uint8_t image_arg_len = rt_strlen(image_arg); //URI里固定的段落

    //const char image_type_arg[] = "image_type=";
    //rt_uint8_t image_type_arg_len = rt_strlen(image_type_arg); //URI里固定的段落

    //const char image_type_base64_arg[] = "BASE64";
    //rt_uint8_t image_type_base64_arg_len = rt_strlen(image_type_base64_arg); //URI里固定的段落

    //const char group_id_list_arg[] = "group_id_list=";
    //rt_uint8_t group_id_list_arg_len = rt_strlen(group_id_list_arg); //URI里固定的段落

    //const char group_id_arg[] = "guet";
    //rt_uint8_t group_id_arg_len = rt_strlen(group_id_arg); //URI里固定的段落

    const char token_arg[] = "?access_token=";
    rt_uint8_t token_arg_len = rt_strlen(token_arg); //URI里固定的段落

    const char image_head_arg[] = "{\"image\":\"";
    rt_uint8_t image_head_arg_len = rt_strlen(image_head_arg); //图片数据的头

    const char image_tail_arg[] = "\",";
    rt_uint8_t image_tail_arg_len = rt_strlen(image_tail_arg); //图片数据的尾

    const char image_type_base64_arg[] = "\"image_type\":\"BASE64\",";
    rt_uint8_t image_type_base64_arg_len = rt_strlen(image_type_base64_arg); //图片类型

    const char group_id_list_arg[] = "\"group_id_list\":\"guet\"}";
    rt_uint8_t group_id_list_arg_len = rt_strlen(group_id_list_arg); //识别列表

    //const char post_data_test[]="{\"image\":\"027d8308a2ec665acb1bdf63e513bcb9\",\"image_type\":\"BASE64\",\"group_id_list\":\"guet\"}";
    //rt_uint8_t post_data_test_len = rt_strlen(post_data_test);
#ifdef BD_AI_BAIKE
    const char baike_args[] = "&baike_num=5";
    rt_uint8_t baike_args_len = rt_strlen(baike_args);
#endif

    rt_uint8_t *post_data = RT_NULL; //发送的数据
    rt_size_t post_data_size = 0; //发送数据的大小
    //rt_size_t percent_len = 0; //百分比编码后的数据长度


    static int index = 0; //索引

    /* step1: get token */ //第一步，获取token
    ai_token = rt_malloc(256); //申请部分空间储存token
    if (ai_token == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto __exit;
    } //判断是否申请到了空间
    LOG_D("start to get baidu ai token"); //LOG
    ai_token_len = get_ai_token(access_token, ai_token); //获取token存在ai_token并储存其长度
    LOG_D("token : %s", ai_token); //LOG
    if (ai_token_len <= 0)
    {
        result = -RT_ENOMEM;
        goto __exit;
    } //判断没有申请到token
    LOG_D("get baidu ai token success"); //LOG

    /* step2: get picture data */ //获取图像数据
    LOG_D("open filename : %s", filename); //LOG

    fd = open(filename, 0, O_RDONLY); //用只读的方式打开某个文件
    if (fd < 0)
    {
        rt_kprintf("open file: %s failed\n", filename);
        result = -RT_ENOMEM;
        goto __exit;
    } //判断是否打开文件

    buff_ptr = rt_malloc(MAX_IMAGE_SIZE); //为图片数据申请空间
    if (buff_ptr == RT_NULL)
    {
        rt_kprintf("no memory\n");
        result = -RT_ENOMEM;
        close(fd);
        goto __exit;
    } //判断空间是否申请成功

    total_length = read(fd, buff_ptr, MAX_IMAGE_SIZE); //总长度，真的读出来的图片大小，而非最大图片大小
    if (total_length > MAX_IMAGE_SIZE)
    {
        LOG_E("image size too big.\n");
        result = -RT_ERROR;
        goto __exit;
    } //判断图片是否超标
    LOG_D("open file success.");
    /* close file and release memory */
    close(fd); //关闭文件

    /* step3: encode image */ //图片base64编码
    LOG_D("encode image start.");
    encode_ptr = rt_malloc(MAX_ENCODE_IMAGE_SIZE); //申请空间base64编码后的图片数据
    encode_size = encode(buff_ptr, total_length, encode_ptr); //编码后的大小返回，编码后的数据放置

    /* step4: get post uri */ //获取请求URI
    index = strlen(BAIDU_AI_API[0]); //获取API的长度
    post_uri_size = index; //初始化URI的初始长度为API的长度
    post_uri = rt_malloc(256); //为URI申请空间

    rt_memcpy(post_uri, BAIDU_AI_API[0], post_uri_size); //装填Bai_Du API
    rt_memcpy(&post_uri[post_uri_size], token_arg, token_arg_len); //装填token前缀
    post_uri_size += token_arg_len; //累计URI长度
    rt_memcpy(&post_uri[post_uri_size], ai_token, ai_token_len); //装填token的值
    post_uri_size += ai_token_len; //累计URI长度

    LOG_D("post uri: %s", post_uri); //LOG

    /* step5: percentage code post data */ //百分比编码image
#ifdef BD_AI_BAIKE
    post_data = rt_malloc(encode_size * 3 + image_arg_len + baike_args_len);
#else
    post_data = rt_malloc(image_head_arg_len + encode_size +image_tail_arg_len + image_type_base64_arg_len +group_id_list_arg_len); //申请（计算图片数据大小和长度 + 图片数据前缀的长度）
#endif

    if (post_data == RT_NULL)
    {
        LOG_E("no memory.\n");
        result = -RT_ERROR;
        goto __exit;
    } //判断空间是否申请成功
    rt_memcpy(post_data, image_head_arg, image_head_arg_len); //装载图片数据前缀
    post_data_size = image_head_arg_len;//计算总长度

    rt_memcpy(&post_data[post_data_size], encode_ptr, encode_size); //装载图片数据
    post_data_size += encode_size; //计算总长度

    rt_memcpy(&post_data[post_data_size], image_tail_arg, image_tail_arg_len); //装载图片数据后缀
    post_data_size += image_tail_arg_len; //计算总长度

    rt_memcpy(&post_data[post_data_size], image_type_base64_arg, image_type_base64_arg_len); //装载图片类型
    post_data_size += image_type_base64_arg_len; //计算总长度

    rt_memcpy(&post_data[post_data_size], group_id_list_arg, group_id_list_arg_len); //装载用户组
    post_data_size += group_id_list_arg_len; //计算总长度


#ifdef BD_AI_BAIKE
    if (percent_len < encode_size * 3)
    {
        rt_memcpy(&post_data[post_data_size], baike_args, baike_args_len);
        post_data_size += baike_args_len;
    }
#endif


    LOG_D("post data: %s", post_data); //LOG
    /* step: upload image to baidu ai */
    get_ai_result((const char *)post_uri, (const char *)post_data, post_data_size); //获取结果

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
