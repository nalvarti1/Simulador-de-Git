#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../incs/repository.h"
#include "../incs/staging.h"
#include "../incs/commit.h"
#include "../incs/file.h"

// Programador: [Tu Nombre Aquí]

int main() {
    Repository *repo = NULL;
    char input[256];

    printf("Welcome to uGit!\n");

    while (1) {
        printf("ugit> ");
        if (!fgets(input, sizeof(input), stdin)) break;

        input[strcspn(input, "\n")] = 0;

        if (strncmp(input, "commit -m ", 10) == 0) {
            if (!repo) {
                printf("Error: please initialize repository first using 'init'.\n");
                continue;
            }

            char *msg_start = input + 10;
            if (msg_start[0] == '"') {
                msg_start++;
                char *end = strrchr(msg_start, '"');
                if (end) *end = '\0';
            }

            Commit *c = create_commit_from_staging(repo, msg_start);
            if (!c) {
                // El mensaje de error ya se imprime dentro de la función
            }
            continue;
        }

        char *command = strtok(input, " ");
        char *arg = strtok(NULL, " ");

        if (!command) continue;

        if (strcmp(command, "exit") == 0) {
            break;
        }
        else if (strcmp(command, "init") == 0) {
            if (!repo) repo = init_repository();
            else printf("Repository already initialized.\n");
        }
        else if (strcmp(command, "add") == 0) {
            if (!repo) {
                printf("Error: please initialize repository first using 'init'.\n");
                continue;
            }
            if (!arg) {
                printf("You must specify a file to add.\n");
                continue;
            }
            add_file_to_staging(repo->staging, arg);
        }
        else if (strcmp(command, "log") == 0 || strcmp(command, "history") == 0) {
            if (!repo) {
                printf("Error: please initialize repository first using 'init'.\n");
                continue;
            }
            if (!repo->HEAD) {
                printf("No commits yet.\n");
                continue;
            }
            list_commits(repo->HEAD);
        }
        // --- BLOQUE PARA CHECKOUT ---
        else if (strcmp(command, "checkout") == 0) {
            if (!repo) {
                printf("Error: please initialize repository first using 'init'.\n");
                continue;
            }
            if (!arg) {
                printf("You must specify a commit id to checkout.\n");
                continue;
            }
            checkout_commit(repo, arg);
        }
        else {
            printf("Unknown command: %s\n", command);
        }
    }

    if (repo) free_repository(repo);

    printf("Goodbye!\n");
    return 0;
}