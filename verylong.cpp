#include "verylong.h"

std::string VeryLong::putvl() const
{
    char temp[SZ];
    strcpy_s(temp, vlstr);
    _strrev(temp);
    return std::string(temp);
}

void VeryLong::input_vl(const char* s)
{
    strcpy_s(vlstr, s);
    vlen = strlen(s);
    _strrev(vlstr);
}

VeryLong VeryLong ::operator + (const VeryLong other)
{
    char temp[SZ];
    int j;
    int maxlen = (vlen > other.vlen) ? vlen : other.vlen;
    int carry = 0;

    if (vlstr[vlen - 1] == '-') {
        if (other.vlstr[other.vlen - 1] == '-')
            return((other).negate() + (*this).negate()).negate();
        else
            return(other)-(*this).negate();
    }
    else if (other.vlstr[other.vlen - 1] == '-')
    {
        return(*this) - (other).negate();
    }

    for (j = 0; j < maxlen; j++)
    {
        int d1 = (j > vlen - 1) ? 0 : vlstr[j] - '0';
        int d2 = (j > other.vlen - 1) ? 0 : other.vlstr[j] - '0';
        int digitsum = d1 + d2 + carry;
        if (digitsum >= 10)
        {
            digitsum -= 10; carry = 1;
        }
        else
            carry = 0;
        temp[j] = digitsum + '0';
    }
    if (carry == 1)
        temp[j++] = '1';
    temp[j] = '\0';
    return VeryLong(temp);
}

VeryLong VeryLong ::operator * (const VeryLong other)
{

    if (vlstr[vlen - 1] == '-')
    {
        if (other.vlstr[other.vlen - 1] == '-')
            return(other).negate() * (*this).negate();
        else
            return((*this).negate() * (other)).negate();
    }
    else if (other.vlstr[other.vlen - 1] == '-')
    {
        return((other).negate() * (*this)).negate();
    }

    VeryLong pprod;
    VeryLong tempsum;
    for (int j = 0; j < other.vlen; j++)
    {
        int digit = other.vlstr[j] - '0';
        pprod = multdigit(digit);
        for (int k = 0; k < j; k++)
            pprod = mult10(pprod);
        tempsum = tempsum + pprod;
    }
    return tempsum;
}

VeryLong VeryLong::operator - (const VeryLong& other) const
{
    char result[SZ];
    int borrow = 0;
    int i = 0;

    if (vlstr[vlen - 1] == '-')
    {
        if (other.vlstr[other.vlen - 1] == '-')
            return (other).negate() - (*this).negate();
        else
            return ((*this).negate() + (other)).negate();
    }
    else if (other.vlstr[other.vlen - 1] == '-')
    {
        return(other).negate() + (*this);
    }

    if (compareAbs(other) < 0)
    {
        return (other - *this).negate();
    }

    for (i = 0; i < vlen || i < other.vlen; ++i)
    {
        int digit1 = (i < vlen) ? (vlstr[i] - '0') : 0;
        int digit2 = (i < other.vlen) ? (other.vlstr[i] - '0') : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result[i] = diff + '0';
    }
    if (borrow > 0)
    {
        result[i] = borrow + '0';
        ++i;
    }
    result[i] = '\0';

    while (i > 1 && result[i - 1] == '0')
    {
        result[i - 1] = '\0';
        --i;
    }
    return VeryLong(result);
}

VeryLong VeryLong::operator / (const VeryLong& denominator)
{
    VeryLong numerator = *this;
    VeryLong integer;
    int count = 0;

    if (vlstr[vlen - 1] == '-')
    {
        if (denominator.vlstr[denominator.vlen - 1] == '-')
            return (*this).negate() / (denominator).negate();
        else
            return ((*this).negate() / denominator).negate();
    }
    else if (denominator.vlstr[denominator.vlen - 1] == '-')
    {
        return (*this / (denominator).negate()).negate();
    }
    if (denominator.compareAbs(VeryLong("0")) == 0)
    {
        cout << "Division by zero is not allowed." << endl;
        exit(1);
    }

    while (numerator.compareAbs(denominator) >= 0)
    {
        numerator = numerator - denominator;
        count++;
    }

    integer = VeryLong(count);

    if (numerator.compareAbs(VeryLong("0")) == 0)
        return integer;
    else
    {
        VeryLong fractional = VeryLong(".");

        while (numerator.compareAbs(denominator) == -1)
        {
            if (numerator.compareAbs(VeryLong("0")) == 0)
                return integer.add(fractional);

            numerator = numerator.add(VeryLong("0"));

            if (numerator.compareAbs(denominator) == -1)
            {
                fractional = fractional.add(VeryLong("0"));
            }
            else
            {
                int count2 = 0;
                if (fractional.vlen < 10)
                {
                    while (numerator.compareAbs(denominator) >= 0)
                    {
                        numerator = numerator - denominator;
                        count2++;
                    }
                    fractional = fractional.add(count2);
                }
            }
        }
        return integer.add(fractional);
    }
}

VeryLong VeryLong::multdigit(const int d2) const
{
    char temp[SZ];
    int j, carry = 0;
    for (j = 0; j < vlen; j++)
    {
        int d1 = vlstr[j] - '0';
        int digitprod = d1 * d2;
        digitprod += carry;
        if (digitprod >= 10)
        {
            carry = digitprod / 10;
            digitprod -= carry * 10;
        }
        else
            carry = 0;
        temp[j] = digitprod + '0';
    }
    if (carry != 0)
        temp[j++] = carry + '0';
    temp[j] = '\0';
    return VeryLong(temp);
}

VeryLong VeryLong::mult10(const VeryLong other) const
{
    char temp[SZ];
    for (int j = other.vlen - 1; j >= 0; j--)
        temp[j + 1] = other.vlstr[j];
    temp[0] = '0';
    temp[other.vlen + 1] = '\0';
    return VeryLong(temp);
}

int VeryLong::compareAbs(const VeryLong& other) const
{
    if (vlen > other.vlen)
    {
        return 1;
    }
    else if (vlen < other.vlen)
    {
        return -1;
    }
    else
    {
        for (int i = vlen - 1; i >= 0; --i)
        {
            if (vlstr[i] > other.vlstr[i])
            {
                return 1;
            }
            else if (vlstr[i] < other.vlstr[i])
            {
                return -1;
            }
        }
        return 0;
    }
}

VeryLong VeryLong::negate() const
{
    char result[SZ];
    int i = 0;

    for (i = 0; i < vlen; ++i)
    {
        result[i] = vlstr[i];
    }

    if (result[i - 1] == '-')
    {
        result[i - 1] = '\0';
    }
    else
    {
        result[i] = '-';
        result[i + 1] = '\0';
    }

    return VeryLong(result);
}

VeryLong VeryLong::add(const VeryLong& other) const
{
    char temp[SZ];
    int j = 0;
    for (; j < other.vlen; j++)
    {
        temp[j] = other.vlstr[j];
    }
    for (int i = 0; i < vlen; i++, j++)
    {
        temp[j] = vlstr[i];
    }
    temp[j] = '\0';
    return VeryLong(temp);
}

