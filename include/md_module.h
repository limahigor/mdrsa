#ifndef MD_MODULE_H
#define MD_MODULE_H

int mdc_euclides(unsigned int x, unsigned int y);
unsigned int isprime(unsigned long int num);
unsigned int fast_mod_pow(unsigned  long int expo,
                          unsigned long int base,
                          unsigned long int mod);

//funções para teste
void maior_primo(int intervalo);

#endif