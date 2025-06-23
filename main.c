#include "main.h"

void display_project_info(void) {
    printf("=== %s ===\n", PROJECT_NAME);
    printf("Version: %s\n", PROJECT_VERSION);
    printf("Author: %s\n", AUTHOR);
    printf("CI/CD Embedded Project\n");
    printf("======================\n");
}

int main(void) {
    printf("Iniciando proyecto CI/CD Embedded...\n\n");
    
    display_project_info();
    
    printf("\nProyecto listo para CI/CD!\n");
    
    return 0;
}