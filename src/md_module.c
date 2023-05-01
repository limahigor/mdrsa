#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
//
#include "../include/md_module.h"

#define PRIMO 1
#define N_PRIMO 0

#define troca(x, y)             \
    {                           \
        __typeof(x) temp = (x); \
        (x) = (y);              \
        (y) = (temp);           \
    }

int mdc_euclides(unsigned int x, unsigned int y)
{
    if (x < y)
        troca(x, y);

    if ((x % y) == 0)
        return y;

    return mdc_euclides(y, (x % y));
}

unsigned int isprime(unsigned long int num)
{
    unsigned long int raizq;

    if (num < 3)
    {
        if (num < 2)
            return N_PRIMO;
        return PRIMO;
    }

    if ((num % 2) == 0)
        return N_PRIMO;

    raizq = sqrt(num);

    for (int c = 3; c <= raizq; c += 2)
    {
        if (num % c == 0)
            return N_PRIMO;
    }

    return PRIMO;
}

unsigned long int fast_mod_pow(unsigned long int base,
                               unsigned long int expo,
                               unsigned long int mod)
{

    unsigned long int pot, resul;
    pot = base % mod;
    resul = 1;

    for (; expo > 0; expo /= 2)
    {
        if ((expo % 2) == 1)
            resul = (resul * pot) % mod;
        pot = (pot * pot) % mod;
    }

    return resul;
}

int *comb_linear_mdc(int num1, int num2)
{
    int *array, *array2, *resul;
    int temp, x, y;
    int qnt = 0, qnt2 = 0, qnt3;

    if (num1 == 1)
    {
        x = 0;
        y = 1;
        return 0;
    }

    if (num2 == 1)
    {
        x = 1;
        y = 0;
        return 0;
    }

    array = (int *)malloc(sizeof(int));
    array2 = (int *)malloc(sizeof(int) * 2);

    do
    {
        *(array + qnt) = num1 / num2;
        qnt++;
        array = realloc(array, sizeof(int) * (qnt + 1));

        temp = num2;
        num2 = num1 % num2;
        num1 = temp;
    } while (num1 % num2);

    qnt3 = qnt - 2;

    *array2 = 1;
    *(array2 + 1) = *(array + (qnt - 1));
    qnt--;
    qnt2 = 2;

    for (int c = qnt - 1; c >= 0; c--)
    {
        array2 = realloc(array2, sizeof(int) * (++qnt2));

        int temp1 = *(array + c);
        int temp2 = *(array2 + (qnt2 - 2));
        int temp3 = *(array2 + (qnt2 - 3));

        *(array2 + (qnt2 - 1)) = (temp1 * temp2) + temp3;
    }

    y = *(array2 + (qnt2 - 1));

    if (qnt3 % 2 == 0)
    {
        x = *(array2 + (qnt2 - 2)) * (-1);
        y = *(array2 + (qnt2 - 1));
    }
    else
    {
        x = *(array2 + (qnt2 - 2));
        y = *(array2 + (qnt2 - 1)) * (-1);
    }

    free(array);
    free(array2);

    resul = (int *)malloc(sizeof(int) * 2);

    *(resul + 0) = x;
    *(resul + 1) = y;

    return resul;
}

int in_mod(int x, int y)
{
    int *resul;
    int inverso;
    resul = (int *)malloc(sizeof(int) * 2);

    if (x == 1)
        return x;

    if (!(mdc_euclides(x, y) == 1))
        return 0;

    resul = comb_linear_mdc(x, y);

    inverso = *(resul + 0);

    while (inverso < 0)
    {
        inverso += y;
    }

    while (inverso > y)
    {
        inverso -= y;
    }

    free(resul);

    return inverso;
}