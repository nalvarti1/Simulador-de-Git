#include <stdio.h>
#include <stdlib.h>
#include "repository.h"

Repository* init_repository() {
    // 1. Reservar memoria para el repositorio
    Repository *repo = (Repository*) malloc(sizeof(Repository));
    if (repo == NULL) {
        printf("Error: no se pudo crear el repositorio.\n");
        exit(1);
    }

    // 2. Inicializar HEAD a NULL (no hay commits)
    repo->HEAD = NULL;

    // 3. Crear el staging area vacío
    repo->staging = (StagingArea*) malloc(sizeof(StagingArea));
    if (repo->staging == NULL) {
        printf("Error: no se pudo crear el staging area.\n");
        free(repo);
        exit(1);
    }
    repo->staging->files = NULL;
    repo->staging->count = 0;

    // 4. Mensaje de confirmación
    printf("Initialized empty uGit repository\n");

    return repo;
}
