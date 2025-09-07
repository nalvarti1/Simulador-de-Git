#ifndef FILE_H
#define FILE_H

typedef struct {
    char name[256];   // Nombre del archivo
    char *content;    // Contenido del archivo
} File;

#endif
