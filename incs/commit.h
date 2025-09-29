#ifndef COMMIT_H
#define COMMIT_H
#include <stdio.h>
#include <time.h> // necesario para time_t
#include <stdbool.h>
#include "file.h"
#include "staging.h"

// Forward declaration
typedef struct Repository Repository;

#define MAX_FILES 1000

typedef struct Commit {
    char id[9];       // ID del commit (8 caracteres + null terminator)
    char message[256]; // Mensaje del commit
    File *files[MAX_FILES]; // Archivos en el commit
    int file_count;  // Numero de archivos en el commit
    struct Commit *parent; // Puntero al commit padre (NULL si es el primer commit)
    time_t date;    // Fecha del commit
} Commit;


Commit* find_commit_by_id(Repository *repo, const char *id);
Commit* create_commit_from_staging(Repository *repo, const char *message); // Crea un commit a partir del staging area
void free_commit(Commit *c); // Libera la memoria usada por el commit
void print_commit_summary(Commit *c); // Imprime resumen de un commit
void list_commits(Commit *head); // Lista todos los commits desde head
void checkout_commit(Repository *repo, const char *commit_id);
void free_commit_history(Commit *head);


#endif