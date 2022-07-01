#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

//Error CONSTANTES
#define DEFAULT_ERR_MSG "\nOcorreu um problema: "
#define CLOSE_MSG "PROGRAMA ENCERRADO\n"

//Path files CONSTANTES
#define PATH_CUSTOMER "customers.txt"
#define PATH_COMMANDS "commands.txt"
#define PATH_RESULT "result.txt"

// Files POINTERS
FILE *customers_file;
FILE *commands_file;
FILE *result_file;
FILE *temp_file;

void print_err(char *err);
void get_file_error();
void prepare_to_write_result();


int main(int argc, char **argv) {
    printf("Dev area operating...\n");

    //Verify initial erros
    get_file_error(PATH_CUSTOMER);
    get_file_error(PATH_COMMANDS);


    fclose(result_file)

    return 0;
}

void print_err(char *err) {
    printf("%s\n", err);
    printf(CLOSE_MSG);
    exit(1);
}

void get_file_error(char *file_name) {
    char *temp[3];
    *temp = &file_name[strlen(file_name)-3];

    if(strcmp(*temp, "txt") != 0){
        char *ERR = DEFAULT_ERR_MSG"O arquivo passado não é um arquivo .txt";
        print_err(ERR);
        exit(1);
    }

    temp_file = fopen(file_name, "r");

    if (temp_file == NULL){
        char *ERR = DEFAULT_ERR_MSG"Ao abrir o arquivo. Está vazio ou não existe";
        print_err(ERR);
        exit(1);
    }

    fclose(temp_file);
}

void prepare_to_write_result(){
    //Resetando o arquivo a primeira vez que o programa é executado
    result_file = fopen(PATH_RESULT, "w");

    fclose(result_file);

    //Abrindo arquivo para append no arquivo
    result_file = fopen(PATH_RESULT, "a");
}