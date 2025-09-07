#ifndef STAGING_H
#define STAGING_H

#include "file.h"

typedef struct {
    File **files;   // Arreglo dinamico de archivos agregados
    int count;      // Numero de archivos agregados
} StagingArea;

#endif
