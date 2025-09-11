#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incs/staging.h"

StagingArea* init_staging_area() {
    StagingArea *staging = malloc(sizeof(StagingArea));
    staging->count = 0;
    return staging;
}
// Agrega un archivo al staging area y retorna exito o fallo de la operacion
bool add_file_to_staging(StagingArea *staging, const char *filename) {
    if (staging->count >= MAX_FILES) {
        printf("Error: full staging area.\n");
        return false;
    }

    for (int i = 0; i < staging->count; i++) {
        if (strcmp(staging->files[i], filename) == 0) {
            printf("file '%s' is in staging area.\n", filename);
            return false;
        }
    }

    staging->files[staging->count] = strdup(filename);
    staging->count++;
    printf("file '%s' added to staging area.\n", filename);
    return true;
}

// Lista los archivos actualmente en el staging area 
void list_staging_files(StagingArea *staging) {
    printf("files in staging area:\n");
    for (int i = 0; i < staging->count; i++) {
        printf(" - %s\n", staging->files[i]);
    }
}
// Libera la memoria usada por el staging area 
void free_staging(StagingArea *staging) {
    for (int i = 0; i < staging->count; i++) {
        free(staging->files[i]);
    }
    free(staging->files);
    free(staging);
}
