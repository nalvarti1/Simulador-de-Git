#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "staging.h"
#include "hashtable.h"

// Forward declaration
typedef struct Commit Commit;

typedef struct Repository {
    char name[256];
    StagingArea *staging;
    Commit *HEAD;
    HashTable *commit_index;
} Repository;

Repository* init_repository(); // Inicializa un repositorio y retorna un puntero a el
void free_repository(Repository *repo); // Libera la memoria usada por el repositorio

#endif