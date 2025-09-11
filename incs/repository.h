#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "staging.h"

// Declaracion adelantada (forward declaration)
typedef struct Commit Commit;

typedef struct {
    char name[50];         // Nombre del repositorio
    StagingArea *staging;  // Area de preparacion
} Repository;

Repository* init_repository();
void free_repository(Repository *repo);

#endif
