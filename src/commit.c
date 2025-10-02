#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../incs/commit.h"
#include "../incs/file.h"
#include "../incs/staging.h"
#include "../incs/repository.h"

// Genera un ID de commit aleatorio de 8 caracteres
static void generate_commit_id(char out[9]) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < 8; i++) {
        out[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    out[8] = '\0';
}

// Crea un commit a partir del staging area y lo asocia al repositorio
Commit* create_commit_from_staging(Repository *repo, const char *message) {
    if (!repo || !repo->staging) return NULL;

    if (repo->staging->count == 0) {
        printf("Staging area is empty. Nothing to commit.\n");
        return NULL;
    }

    Commit *c = calloc(1, sizeof(Commit)); // zero-initialize
    if (!c) {
        fprintf(stderr, "Error: could not allocate memory for commit\n");
        return NULL;
    }

    // Numero de archivos a copiar
    c->file_count = repo->staging->count;

    // Copia profunda: crear File* nuevos para el commit
    for (int i = 0; i < c->file_count; i++) {
        const char *fname = repo->staging->files[i];
        if (!fname) {
            fprintf(stderr, "Warning: null filename in staging at index %d\n", i);
            c->files[i] = NULL;
            continue;
        }
        File *f = create_file(fname); // create_file debe crear un File* independiente
        if (!f) {
            fprintf(stderr, "Error: could not create file object for '%s'\n", fname);
            // liberar lo creado hasta ahora
            for (int j = 0; j < i; j++) {
                if (c->files[j]) free_file(c->files[j]);
            }
            free(c);
            return NULL;
        }
        c->files[i] = f;
    }

    // Inicializar el resto a NULL 
    for (int i = c->file_count; i < MAX_FILES; i++) c->files[i] = NULL;

    // Copiar mensaje (safe)
    strncpy(c->message, message ? message : "", sizeof(c->message) - 1);
    c->message[sizeof(c->message) - 1] = '\0';

    // ID, fecha y enlace al padre
    generate_commit_id(c->id);
    c->date = time(NULL);
    c->parent = repo->HEAD;

    // Actualizar HEAD en repo (para acceso secuencial)
    repo->HEAD = c;

    // INTEGRACIÓN HASHTABLE: Agregar commit al indice para busqueda O(1)
    // Esto permite encontrar cualquier commit por ID sin recorrer la lista
    if (repo->commit_index) {
        hash_insert(repo->commit_index, c->id, c);
    }

    // Limpiar staging area despues del commit
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

/**
 * FUNCION CLAVE DE INTEGRACIÓN HASHTABLE:
 * Busca un commit por ID usando hashtable en lugar de busqueda lineal
 * 
 * ANTES (sin hashtable): O(n) - recorrer toda la lista enlazada
 * DESPUÉS (con hashtable): O(1) - acceso directo por clave
 */
Commit* find_commit_by_id(Repository *repo, const char *id) {
    if (!repo || !repo->commit_index || !id) {
        return NULL;
    }
    
    // Busqueda O(1) en hashtable en lugar de O(n) en lista enlazada
    return (Commit*)hash_get(repo->commit_index, id);
}

/**
 * BENEFICIO DEL HASHTABLE EN CHECKOUT:
 * Permite cambiar a cualquier commit instantaneamente
 * usando find_commit_by_id() que es O(1) gracias al hashtable
 */
void checkout_commit(Repository *repo, const char *commit_id) {
    if (!repo || !commit_id) {
        return;
    }

    // Usar hashtable para encontrar commit en O(1) en lugar de O(n)
    Commit *target_commit = find_commit_by_id(repo, commit_id);

    if (target_commit) {
        repo->HEAD = target_commit;  // Cambiar HEAD al commit encontrado
        printf("Switched to commit %s\n", target_commit->id);
    } else {
        printf("Error: commit '%s' not found in history.\n", commit_id);
    }
}

// Libera toda la historia de commits
void free_commit_history(Commit *head) {
    Commit *current = head;
    Commit *next;
    while (current != NULL) {
        next = current->parent;
        free_commit(current);
        current = next;
    }
}