#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

//Error CONSTANTES
#define DEFAULT_ERR_MSG "\nOcorreu um problema: "
#define CLOSE_MSG "PROGRAMA ENCERRADO\n"

//Path files CONSTANTES
#define PATH_CUSTOMER "customer.txt"
#define PATH_COMMANDS "commands.txt"
#define PATH_RESULT "result.txt"

// Files POINTERS
FILE *customers_file;
FILE *commands_file;
FILE *result_file;
FILE *temp_file;

// Customer VARS
int number_of_customers = 0; //Quantidade de instancias de clientes

// Resource VARS
int number_of_resources = 0;//Quantidade de instancia de recursos

// Commands VARS
int number_of_commands;//Quantidade de comandos

// General VARS
int qntd_params;

// Function PROTOTYPES
void print_err(char *err);

void get_file_error();
void prepare_to_write_result();
void read_customers(char *filename);
void read_commands(char *filename);
void get_over_resource(int qntd);
int count_characters(const char *str, char character);

int request_resources(int customer_num, int request[]);
int release_resources(int customer_num, int request[]);


int main(int argc, char **argv) {
    printf("Dev area operating...\n");
    qntd_params = argc-1;
    number_of_resources = argc; //


    //Verify initial erros
    get_file_error(PATH_CUSTOMER);
    get_file_error(PATH_COMMANDS);

    read_customers(PATH_CUSTOMER);
    read_commands(PATH_COMMANDS);
    prepare_to_write_result();

    //Inicializando variáveis
    int maximum_customers[number_of_customers][number_of_resources]; //Quantidade máxima de demanda por cliente
    int allocation_customer[number_of_customers][number_of_resources]; //Valor atualmente alocado para cada cliente
    int need_customer[number_of_customers][number_of_resources]; //Necessidade restante de cada cliente

    int available_resources[number_of_resources];// Quantidade atualmente disponível de cada recurso

    fclose(result_file);

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
        printf("Falha no arquivo: %s\n", file_name);
        print_err(ERR);
        exit(1);
    }

    temp_file = fopen(file_name, "r");

    if (temp_file == NULL){
        char *ERR = DEFAULT_ERR_MSG"Ao abrir o arquivo. Está vazio ou não existe";
        printf("Falha no arquivo: %s\n", file_name);
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

void read_customers(char *filename){
    customers_file = fopen(filename, "r");
    int character_code;
    int lines_in_file = 0;
    char line_str[20];

    int count_char = 0;


    while(!feof(customers_file)){
        character_code = fgetc(customers_file);
        if(character_code == '\n'){
            lines_in_file++;
        }
    }
    // printf("%s\n", line_str);

    lines_in_file++;//Pegando uma linha a mais para ficar na mesma quantidade de linhas do arquivo.
    number_of_customers = lines_in_file+1; //Quantidade total de clientes

    fseek(customers_file, 0, SEEK_SET);
    while (!feof(customers_file)){
        fgets(line_str, sizeof(line_str), customers_file);
        count_char = count_characters(line_str, ','); // Ele irá retornar a quantidade de ',' na string
                                                    // A quantidade de ',' + 1 é a quantidade de clientes
                                                    // No arquivo.
        get_over_resource(count_char+1);

    }
    // Popular arrays com os valores lidos do arquivo

    fclose(customers_file);

}

void read_commands(char *filename){
    commands_file = fopen(filename, "r");

    int character_code;
    int lines_in_file = 0;
    char line_str[20];

    int count_char = 0;

    while(!feof(commands_file)){
        character_code = fgetc(commands_file);
        if(character_code == '\n'){
            lines_in_file++;
        }
    }

    lines_in_file++;//Pegando uma linha a mais para ficar na mesma quantidade de linhas do arquivo.
    number_of_customers = lines_in_file+1; //Quantidade total de clientes

    fseek(commands_file, 0, SEEK_SET);

    while (!feof(customers_file)){
        fgets(line_str, sizeof(line_str), customers_file);
        // printf("%s\n", line_str);

        if (line_str[0] == '*'){
            // printf("caracter em C: %c\n", line_str[1]);
            continue;
        }

        count_char = count_characters(line_str, ' '); // Ele irá retornar a quantidade de ' ' na string (linha)
                                                    // A quantidade de ' ' - 1 é a quantidade de clientes
                                                    // No arquivo comando.
        get_over_resource(count_char-1);
    }
    // Popular arrays com os valores lidos do arquivo

    fclose(customers_file);

}

// Levanta erro em caso de recursos serem incompatíveis com instancias de clientes
void get_over_resource(int resources_needs_in_file){
    if(qntd_params != resources_needs_in_file){
        char *ERR = DEFAULT_ERR_MSG"Não há recursos suficientes para atender a demanda";
        print_err(ERR);
    }
}

int count_characters(const char *str, char character){
    const char *p = str;
    int count = 0;

    do {
        if (*p == character){
            count++;
        }
    } while (*(p++));

    return count;
}