#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "staging.h"

// Declaración adelantada (forward declaration)
typedef struct Commit Commit;

typedef struct {
    Commit *HEAD;          // Último commit
    StagingArea *staging;  // Área de preparación
} Repository;

Repository* init_repository();

#endif
