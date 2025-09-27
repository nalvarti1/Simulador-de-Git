#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "staging.h"

// Forward declaration
typedef struct Commit Commit;

typedef struct Repository {
    char name[256];
    StagingArea *staging;
    Commit *HEAD;
} Repository;

Repository* init_repository(); // Inicializa un repositorio y retorna un puntero a el
void free_repository(Repository *repo); // Libera la memoria usada por el repositorio

#endif