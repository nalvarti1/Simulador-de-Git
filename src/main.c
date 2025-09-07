#include <stdio.h>
#include <string.h>
#include "repository.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: ugit <comando>\n");
        return 1;
    }

    // Solo implementamos init por ahora
    if (strcmp(argv[1], "init") == 0) {
        Repository *repo = init_repository();
        // Aquí repo queda listo para usarse con add y commit
    } else {
        printf("Comando no reconocido.\n");
    }

    return 0;
}
