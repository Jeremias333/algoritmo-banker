#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

//Error CONSTANTES
#define DEFAULT_ERR_MSG "\nOcorreu um problema: "
#define CLOSE_MSG "PROGRAMA ENCERRADO\n"

void print_err(char *err);


int main(int argc, char **argv) {
    printf("Production area operating...\n");

    return 0;
}

void print_err(char *err){
    printf("%s\n", err);
    printf(CLOSE_MSG);
    exit(1);
}