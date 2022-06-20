#ifndef MD_MODULE_H
#define MD_MODULE_H

int mdc_euclides(unsigned int x, unsigned int y);
unsigned int isprime(unsigned long int num);
int in_mod(int x, int y);
int* comb_linear_mdc(int num1, int num2);
unsigned long int fast_mod_pow(unsigned long int base,
                          unsigned long int expo,
                          unsigned long int mod);

#endif