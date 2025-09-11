#include <stdio.h>
#include <string.h>
#include "../incs/repository.h"
#include "../incs/staging.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: ugit <command>\n");
        return 1;
    }

    // Solo implementamos init y add por ahora
    if (strcmp(argv[1], "init") == 0) {
        init_repository();
    } 
    else if (strcmp(argv[1], "add") == 0) {
        if (argc < 3) {
            printf("ugit add: missing file operand\n");
            return 1;
        }
        // inicializar staging area si no existe
        static StagingArea *staging = NULL;
        if (!staging) {
            staging = init_staging_area();
        }
        add_file_to_staging(staging, argv[2]);
        list_staging_files(staging);
        free_staging(staging);

    } 
    else {
        printf("ugit: unknown command '%s'\n", argv[1]);
    }
    
    return 0;
}
