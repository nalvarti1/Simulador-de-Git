#ifndef FILE_H
#define FILE_H
#include <stdlib.h>

typedef struct {
    char name[256];   // Nombre del archivo
    char *content;    // Contenido del archivo
    size_t size;      // Tamaño del contenido
} File;

// Crea un archivo simulado solo con el nombre
File* create_file(const char *name);
void free_file(File *f); // Libera la memoria usada por el archivo

#endif