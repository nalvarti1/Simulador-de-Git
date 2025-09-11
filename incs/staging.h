#ifndef STAGING_H
#define STAGING_H
#include<stdbool.h>

#include "file.h" 
#define MAX_FILES 1000 // Maximo numero de archivos en el staging area

typedef struct {
    char *files[MAX_FILES];  // Nombres de archivos en staging area
    int count;      // Numero de archivos agregados
} StagingArea;

// Inicializa area de preparacion (staging area) y retorna un puntero a ella 
StagingArea *init_staging_area();

// Agrega un archivo al staging area y retorna exito o fallo de la operacion 
bool add_file_to_staging(StagingArea *staging, const char *filename);

// Lista los archivos actualmente en el staging area 
void list_staging_files(StagingArea *staging);

// Libera la memoria usada por el staging area
void free_staging(StagingArea *staging);

#endif
