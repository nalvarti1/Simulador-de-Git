#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../incs/repository.h"
#include "../incs/staging.h"

Repository *init_repository() {
    Repository *repo = malloc(sizeof(Repository));
    if (!repo) { fprintf(stderr,"Error allocating repo\n"); exit(1); }
    strncpy(repo->name, "ugit-repo", sizeof(repo->name)-1);
    repo->name[sizeof(repo->name)-1] = '\0';
    repo->staging = init_staging_area(); // or init_staging() según tu nombre
    repo->HEAD = NULL;
    srand((unsigned)time(NULL));
    printf("Initialized empty uGit repository: %s\n", repo->name);
    return repo;
}

void free_repository(Repository *repo) {
    if (repo->staging) {
        free_staging(repo->staging);
    }
    free(repo);
}
