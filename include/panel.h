#ifndef PANEL_H
#define PANEL_H

#define LEN 1024

#define AUTOFREE \
  __attribute__(( cleanup( cleanup_func ) ))

void cleanup_func(char **p);

void main_panel();
_Bool choose(list_t alfabeto);
void panel_key();
void panel_encrypt(list_t alfabeto);
void panel_decrypt(list_t alfabeto);
int str_int(char *string, int *teste, int qnt);

#endif
