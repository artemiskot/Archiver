#include "stringHelpers.h"

void bin2hex(unsigned char b, std::vector<unsigned char>& res)
{
    unsigned char h = b >> 4;
    res[0] = '0' + h + (-(h > 9) & ('A' - '9' - 1));
    unsigned char l = b & 0xf;
    res[1] = '0' + l + (-(l > 9) & ('A' - '9' - 1));
}

void uCharsToHex(unsigned char* aData, size_t aSize, std::string& res)
{
    std::vector<unsigned char> b(2);
    for (size_t i = 0; i < aSize; i++)
    {
        bin2hex(aData[i], b);
        res += ' ';
        res += b[0];
        res += b[1];
    }
}

std::string toHex(const unsigned char* aData, int aSize)
{
    std::string result;
    uCharsToHex((unsigned char*)aData, aSize, result);
    return result;
}
