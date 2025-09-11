#include <stdio.h>
#include <string.h>
#include "../incs/repository.h"


int main() {
    Repository *repo = NULL;
    char input[256];

    printf("Welcome to uGit!\n");

    while (1) {
        printf("ugit> ");               // Prompt like a terminal
        if (!fgets(input, sizeof(input), stdin)) break; // Read input
        input[strcspn(input, "\n")] = 0; // Remove newline

        // Split command and argument
        char *command = strtok(input, " ");
        char *arg = strtok(NULL, " ");

        if (!command) continue;

        if (strcmp(command, "exit") == 0) {
            break; // Exit program
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
        else if (strcmp(command, "log") == 0) {
            if (!repo) {
                printf("Error: please initialize repository first using 'init'.\n");
                continue;
            }
            list_staging_files(repo->staging);
        }
        else {
            printf("Unknown command: %s\n", command);
        }
    }

    if (repo) free_repository(repo);

    printf("Goodbye!\n");
    return 0;
}
