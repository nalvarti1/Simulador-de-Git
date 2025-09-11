#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incs/repository.h"
#include "../incs/staging.h"

Repository *init_repository() {
    Repository *repo = malloc(sizeof(Repository));
    strcpy(repo->name, "ugit-repo");
    repo->staging = init_staging_area();

    printf("Initialized empty uGit repository: %s\n", repo->name);
    return repo;
}

void free_repository(Repository *repo) {
    if (repo->staging) {
        free_staging(repo->staging);
    }
    free(repo);
}
