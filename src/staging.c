#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incs/staging.h"

StagingArea* init_staging_area() {
    StagingArea *s = malloc(sizeof(StagingArea));
    if (!s) return NULL;
    s->count = 0;
    for (int i = 0; i < MAX_FILES; i++) s->files[i] = NULL;
    return s;
}

bool add_file_to_staging(StagingArea *staging, const char *filename) {
    if (!staging || !filename) return false;
    if (staging->count >= MAX_FILES) {
        printf("Error: staging area full.\n");
        return false;
    }

    // Check duplicate
    for (int i = 0; i < staging->count; i++) {
        if (strcmp(staging->files[i], filename) == 0) {
            printf("file '%s' is already in staging area.\n", filename);
            return false;
        }
    }

    staging->files[staging->count] = strdup(filename);
    if (!staging->files[staging->count]) {
        fprintf(stderr, "Error: memory allocation failed in add_file_to_staging\n");
        return false;
    }
    staging->count++;
    printf("file '%s' added to staging area.\n", filename);
    return true;
}


void list_staging_files(StagingArea *staging) {
    if (!staging) return;
    if (staging->count == 0) {
        printf("staging area is empty.\n");
        return;
    }
    printf("files in staging area:\n");
    for (int i = 0; i < staging->count; i++) {
        printf(" - %s\n", staging->files[i]);
    }
}

void free_staging(StagingArea *staging) {
    if (!staging) return;
    for (int i = 0; i < staging->count; i++) {
        free(staging->files[i]);
    }

    free(staging);
}
