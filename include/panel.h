#ifndef PANEL_H
#define PANEL_H

#ifdef __unix__         
    #include <stdlib.h>

#elif defined(_WIN32) || defined(WIN32) 

   #define OS_Windows

   #include <windows.h>

#endif

#define LEN 1024

#define AUTOFREE \
  __attribute__(( cleanup( cleanup_func ) ))

void cleanup_func(char **p);

void main_panel();
_Bool choose();
void panel_chave();
void panel_encriptar(list_t alfabeto);
void panel_desencriptar();

#endif