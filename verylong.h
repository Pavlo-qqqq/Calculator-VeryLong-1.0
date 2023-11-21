#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
const int SZ = 1000;
class VeryLong
{
private:
    char vlstr[SZ];
    int vlen;
    VeryLong multdigit(const int) const;
    VeryLong mult10(const VeryLong verylong) const;
    int compareAbs(const VeryLong& other) const;
    VeryLong negate() const;
    VeryLong add(const VeryLong&) const;
public:
    VeryLong() : vlen(0)
    {
        vlstr[0] = '\0';
    }
    VeryLong(const char s[SZ])
    {
        strcpy_s(vlstr, s); vlen = strlen(s);
    }
    VeryLong(const unsigned long n)
    {
        _ltoa_s(n, vlstr, 10);
        _strrev(vlstr);
        vlen = strlen(vlstr);
    }

    string putvl() const;
    void input_vl(const char* s);
    VeryLong operator + (const VeryLong);
    VeryLong operator * (const VeryLong);
    VeryLong operator - (const VeryLong& other) const;
    VeryLong operator / (const VeryLong& divisor);

    const char* getVlStr() const {
        return vlstr;
    }
};
