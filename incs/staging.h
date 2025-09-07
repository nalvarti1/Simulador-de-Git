#ifndef STAGING_H
#define STAGING_H

#include "file.h"

typedef struct {
    File **files;   // Arreglo dinámico de archivos agregados
    int count;      // Número de archivos agregados
} StagingArea;

#endif
