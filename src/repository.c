#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <time.h>
#include "../incs/repository.h"
#include "../incs/staging.h"
#include "../incs/commit.h"
#include "../incs/commit.h"

Repository *init_repository() {
    Repository *repo = malloc(sizeof(Repository));
    if (!repo) { fprintf(stderr,"Error allocating repo\n"); exit(1); }
    
    strncpy(repo->name, "ugit-repo", sizeof(repo->name)-1);
    repo->name[sizeof(repo->name)-1] = '\0';
    
    repo->staging = init_staging_area();        // Inicializar area de staging
    repo->HEAD = NULL;                          // Sin commits inicialmente
    
    // INTEGRACION HASHTABLE: Crear indice de commits para busqueda O(1)
    repo->commit_index = hash_create();
    if (!repo->commit_index) {
        free_staging(repo->staging);
        free(repo);
        fprintf(stderr,"Error creating commit index\n");
        exit(1);
    }
    
    srand((unsigned)time(NULL));  // Semilla para IDs aleatorios
    if (!repo) { fprintf(stderr,"Error allocating repo\n"); exit(1); }
    strncpy(repo->name, "ugit-repo", sizeof(repo->name)-1);
    repo->name[sizeof(repo->name)-1] = '\0';
    repo->staging = init_staging_area();
    repo->HEAD = NULL;
    srand((unsigned)time(NULL));
    printf("Initialized empty uGit repository: %s\n", repo->name);
    return repo;
}
void free_repository(Repository *repo) {
    if (!repo) return;
    
    // Liberar area de staging
    if (repo->staging) {
        free_staging(repo->staging);
    }
    
    // Liberar indice de commits
    if (repo->commit_index) {
        hash_destroy(repo->commit_index);
    }
    
    // Liberar historial de commits (lista enlazada)
    if (repo->HEAD) {
        free_commit_history(repo->HEAD);
    }
    
    if (repo->HEAD) {
        free_commit_history(repo->HEAD); // Liberar commits
    }
    free(repo);
}