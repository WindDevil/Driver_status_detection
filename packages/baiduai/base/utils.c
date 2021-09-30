/*
 * @Descripttion :
 * @version      :
 * @Author       : Kevincoooool
 * @Date         : 2021-01-07 15:05:22
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-01-12 09:07:22
 * @FilePath     : \n_esp-adf\1_take_pic_http_to_cloud\main\urlcode.c
 */
#include <stdio.h>
#include <string.h>

int http_percentage_coding(unsigned char *org_data, unsigned char *new_data, int len)
{
    int i = 0;
    unsigned char org_char = 0;

    while (len--)
    {
        org_char = *(org_data++);
        switch (org_char)
        {
        case ':' :
            new_data[i++] = '%';
            new_data[i++] = '3';
            new_data[i++] = 'A';
        break;

        case '/' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = 'F';
        break;

        case '?' :
            new_data[i++] = '%';
            new_data[i++] = '3';
            new_data[i++] = 'F';
        break;

        case '#' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = '3';
        break;

        case '[' :
            new_data[i++] = '%';
            new_data[i++] = '5';
            new_data[i++] = 'B';
        break;

        case ']' :
            new_data[i++] = '%';
            new_data[i++] = '5';
            new_data[i++] = 'D';
        break;

        case '@' :
            new_data[i++] = '%';
            new_data[i++] = '4';
            new_data[i++] = '0';
        break;

        case '!' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = '1';
        break;

        case '$' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = '4';
        break;

        case '&' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = '6';
        break;

        case '\'' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = '7';
        break;

        case '(' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = '8';
        break;

        case ')' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = '9';
        break;

        case '*' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = 'A';
        break;

        case '+' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = 'B';
        break;

        case ',' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = 'C';
        break;

        case ';' :
            new_data[i++] = '%';
            new_data[i++] = '3';
            new_data[i++] = 'B';
        break;

        case '=' :
            new_data[i++] = '%';
            new_data[i++] = '3';
            new_data[i++] = 'D';
        break;

        case '%' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = '5';
        break;

        case ' ' :
            new_data[i++] = '%';
            new_data[i++] = '2';
            new_data[i++] = '0';
        break;

        default:
            new_data[i++] = org_char;
        break;
        }
    }
    return i;
}
/**
 * @brief URLEncode ���ַ���URL����
 *
 * @param str ԭ�ַ���
 * @param strSize ԭ�ַ�������(����������\0)
 * @param result ����������ĵ�ַ
 * @param resultSize ����������Ĵ�С(��������\0)
 *
 * @return: >0:resultstring ��ʵ����Ч�ĳ���
 *            0: ����ʧ��.
 */
int URLEncode(const unsigned char *str, const int strSize, unsigned char *result, const int resultSize)
{
    int i;
    int j = 0; //for result index
    char ch;
    char buffer[3];

    if ((str == NULL) || (result == NULL) || (strSize <= 0) || (resultSize <= 0))
    {
        return 0;
    }
    result[0] = 'i';
    result[1] = 'm';
    result[2] = 'a';
    result[3] = 'g';
    result[4] = 'e';
    result[5] = '=';
    j=6;
    for (i = 0; (i < strSize) && (j < resultSize); ++i)
    {
        ch = str[i];
        if (((ch >= 'A') && (ch < 'Z')) ||
            ((ch >= 'a') && (ch < 'z')) ||
            ((ch >= '0') && (ch < '9')))
        {
            result[j++] = ch;
        }
        else if (ch == ' ')
        {
            result[j++] = '+';
        }
        else if (ch == '.' || ch == '-' || ch == '_' || ch == '*')
        {
            result[j++] = ch;
        }
        else
        {
            if (j + 3 < resultSize)
            {
                sprintf(buffer, "%%%02X", (unsigned char)ch);
                result[j]=(unsigned char)buffer[0];
                result[j+1]=(unsigned char)buffer[1];
                result[j+2]=(unsigned char)buffer[2];
                j += 3;
            }
            else
            {
                return 0;
            }
        }
    }

    result[j] = '\0';
    return j;
}

