
static const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* encode image */
int base64_encode(unsigned char * bytes_to_encode, unsigned char *encode, int bytes_len)
{
    int i = 0, j = 0, encode_size = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (bytes_len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);

        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; i < 4; i++)
            {
                encode[encode_size++] = base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
        {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for(j = 0; (j < i + 1); j++)
        {
            encode[encode_size++] = base64_chars[char_array_4[j]];
        }

        while ((i++ < 3))
        {
            encode[encode_size++] = '=';
        }
    }

    return encode_size;
}

static const char *ALPHA_BASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int encode(const unsigned char *buf, const long size, unsigned char *base64Char) {
    int a = 0;
    int i = 0;
    while (i < size) {
        unsigned char b0 = buf[i++];
        unsigned char b1 = (i < size) ? buf[i++] : 0;
        unsigned char b2 = (i < size) ? buf[i++] : 0;

        int int63 = 0x3F; //  00111111
        int int255 = 0xFF; // 11111111
        base64Char[a++] = ALPHA_BASE[(b0 >> 2) & int63];
        base64Char[a++] = ALPHA_BASE[((b0 << 4) | ((b1 & int255) >> 4)) & int63];
        base64Char[a++] = ALPHA_BASE[((b1 << 2) | ((b2 & int255) >> 6)) & int63];
        base64Char[a++] = ALPHA_BASE[b2 & int63];
    }
    switch (size % 3) {
        case 1:
            base64Char[--a] = '=';
        case 2:
            base64Char[--a] = '=';
    }
    return a;
}

//char *decode(const char *base64Char, const long base64CharSize, char *originChar, long originCharSize) {
//    int toInt[128] = {-1};
//    for (int i = 0; i < 64; i++) {
//        toInt[ALPHA_BASE[i]] = i;
//    }
//    int int255 = 0xFF;
//    int index = 0;
//    for (int i = 0; i < base64CharSize; i += 4) {
//        int c0 = toInt[base64Char[i]];
//        int c1 = toInt[base64Char[i + 1]];
//        originChar[index++] = (((c0 << 2) | (c1 >> 4)) & int255);
//        if (index >= originCharSize) {
//            return originChar;
//        }
//        int c2 = toInt[base64Char[i + 2]];
//        originChar[index++] = (((c1 << 4) | (c2 >> 2)) & int255);
//        if (index >= originCharSize) {
//            return originChar;
//        }
//        int c3 = toInt[base64Char[i + 3]];
//        originChar[index++] = (((c2 << 6) | c3) & int255);
//    }
//    return originChar;
//}
