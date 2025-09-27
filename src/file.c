#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incs/file.h"

File* create_file(const char *name) {
    File *f = malloc(sizeof(File));
    if (!f) return NULL;

    strncpy(f->name, name, sizeof(f->name) - 1);
    f->name[sizeof(f->name) - 1] = '\0';

    // Contenido ficticio
    const char *dummy = "contenido simulado";
    f->size = strlen(dummy);
    f->content = malloc(f->size + 1);
    if (!f->content) { free(f); return NULL; }

    strcpy(f->content, dummy);

    return f;
}

// Libera la memoria usada por el archivo
void free_file(File *f) {
    if (!f) return;
    free(f->content);
    free(f);
}