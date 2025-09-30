#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "staging.h"
#include "hashtable.h"    // Incluir hashtable para índice de commits

// Forward declaration
typedef struct Commit Commit;

typedef struct Repository {
    char name[256];            // Nombre del repositorio
    StagingArea *staging;      // Área de preparación para commits
    Commit *HEAD;              // Puntero al commit más reciente (lista enlazada)
    HashTable *commit_index;   // HASHTABLE: Índice para búsqueda 
} Repository;

Repository* init_repository(); // Inicializa un repositorio y retorna un puntero a el
void free_repository(Repository *repo); // Libera la memoria usada por el repositorio

#endif