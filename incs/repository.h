#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "staging.h"

// Declaracion adelantada (forward declaration)
typedef struct Commit Commit;

typedef struct {
    Commit *HEAD;          // Ultimo commit
    StagingArea *staging;  // Area de preparacion
} Repository;

Repository* init_repository();

#endif
