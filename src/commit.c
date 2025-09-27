#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../incs/commit.h"
#include "../incs/file.h"
#include "../incs/staging.h"
#include "../incs/repository.h"

// Programador: [Tu Nombre Aquí]

static void generate_commit_id(char out[9]) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < 8; i++) {
        out[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    out[8] = '\0';
}

Commit* create_commit_from_staging(Repository *repo, const char *message) {
    if (!repo || !repo->staging) return NULL;

    if (repo->staging->count == 0) {
        printf("Staging area is empty. Nothing to commit.\n");
        return NULL;
    }

    Commit *c = calloc(1, sizeof(Commit));
    if (!c) {
        fprintf(stderr, "Error: could not allocate memory for commit\n");
        return NULL;
    }

    c->file_count = repo->staging->count;

    for (int i = 0; i < c->file_count; i++) {
        const char *fname = repo->staging->files[i];
        if (!fname) {
            fprintf(stderr, "Warning: null filename in staging at index %d\n", i);
            c->files[i] = NULL;
            continue;
        }
        File *f = create_file(fname);
        if (!f) {
            fprintf(stderr, "Error: could not create file object for '%s'\n", fname);
            for (int j = 0; j < i; j++) {
                if (c->files[j]) free_file(c->files[j]);
            }
            free(c);
            return NULL;
        }
        c->files[i] = f;
    }

    for (int i = c->file_count; i < MAX_FILES; i++) c->files[i] = NULL;

    strncpy(c->message, message ? message : "", sizeof(c->message) - 1);
    c->message[sizeof(c->message) - 1] = '\0';

    generate_commit_id(c->id);
    c->date = time(NULL);
    c->parent = repo->HEAD;

    repo->HEAD = c;

    free_staging(repo->staging);
    repo->staging = init_staging_area();

    printf("[%s] %s\n%d files committed.\n", c->id, c->message, c->file_count);
    return c;
}

void list_commits(Commit *head) {
    Commit *curr = head;
    while (curr) {
        char buf[64];
        struct tm *tm_info = localtime(&curr->date);
        if (tm_info) {
            strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
        } else {
            strncpy(buf, "unknown date", sizeof(buf));
            buf[sizeof(buf)-1] = '\0';
        }
        printf("Commit %s\nDate: %s\nMessage: %s\nFiles: %d\n\n",
               curr->id, buf, curr->message, curr->file_count);
        curr = curr->parent;
    }
}

void free_commit(Commit *c) {
    if (!c) return;
    for (int i = 0; i < c->file_count; i++) {
        if (c->files[i]) free_file(c->files[i]);
    }
    free(c);
}

// --- NUEVAS FUNCIONES PARA CHECKOUT ---

Commit* find_commit_by_id(Commit *head, const char *id) {
    Commit *current = head;
    while (current != NULL) {
        if (strncmp(current->id, id, 8) == 0) {
            return current;
        }
        current = current->parent;
    }
    return NULL;
}

void checkout_commit(Repository *repo, const char *commit_id) {
    if (!repo || !commit_id) {
        return;
    }

    Commit *target_commit = find_commit_by_id(repo->HEAD, commit_id);

    if (target_commit) {
        repo->HEAD = target_commit;
        printf("Switched to commit %s\n", target_commit->id);
    } else {
        printf("Error: commit '%s' not found in history.\n", commit_id);
    }
}
void free_commit_history(Commit *head) {
    Commit *current = head;
    Commit *next;
    while (current != NULL) {
        next = current->parent; // Guarda el puntero al siguiente
        free_commit(current);   // Libera el commit actual
        current = next;         // Avanza al siguiente
    }
}