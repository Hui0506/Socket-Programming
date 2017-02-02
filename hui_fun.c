#ifndef hui_fun_h
#define hui_fun_h

char * _itoa(int value, char* string, int radix)
{
    char tmp[33];
    char* tp = tmp;
    int i;
    unsigned v;
    int sign;
    char* sp;
    if (radix > 36 || radix <= 1)
    {
        return 0;
    }
    sign = (radix == 10 && value < 0);
    if (sign)
        v = -value;
    else
        v = (unsigned)value;
    while (v || tp == tmp)
    {
        i = v % radix;
        v = v /radix;
        if (i < 10)
            *tp++ = i + '0';
        else
            *tp++ = i + 'a' - 10;
    }
    if (string  == 0)
        string = (char*)malloc((tp-tmp) + sign + 1);
    sp = string;
    if (sign)
        *sp++ = '-';
    while (tp > tmp)
        *sp++ = *--tp;        
    *sp = 0;
    return string;
}
int Sum(int result[], int index)
{
    int sum = 0;
    for (int i = 0; i < index; i++)
    {
        sum = sum + result[i];
    }
    return sum;
}
int Max(int result[], int index)
{
    int max = result[0];
    for (int i = 1; i < index; i++)
    {
        if (result[i] > max)
        {
            max = result[i];
        }
    }
    return max;
}
int Min(int result[], int index)
{
    int min = result[0];
    for (int i = 0; i < index; i++)
    {
        if (result[i] < min)
        {
            min = result[i];
        }
    }
    return min;
}
int Sos(int result[], int index)
{
    int sos = 0;
    for (int i = 0; i < index; i++)
    {
        sos = sos + pow(result[i], 2);
    }
    return sos;
}
#endif
