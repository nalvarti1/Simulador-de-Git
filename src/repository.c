#include <stdio.h>
#include <stdlib.h>
#include "repository.h"

Repository* init_repository() {
    Repository* repo = malloc(sizeof(Repository));
    if (!repo) {
        printf("Error: initialize repository\n");
        exit(1);
    }

    repo->staging = malloc(sizeof(StagingArea));
    if (!repo->staging) {
        printf("Error: initialize staging area.\n");
        free(repo);
        exit(1);
    }

    repo->staging->count = 0;

    // ✅ Inicializar todas las posiciones en NULL
    for (int i = 0; i < MAX_FILES; i++) {
        repo->staging->files[i] = NULL;
    }

    printf("Repository initialized succesfully\n");
    return repo;
}

