#include "funcs.h"



char*** lerarquivo(const char* filepath, int* numRows, int* numCols) {
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Contar o número de linhas e colunas
    *numRows = 0;
    *numCols = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        (*numRows)++;
        if (*numCols == 0) {
            // Contar o número de colunas na primeira linha
            char* token = strtok(buffer, ";");
            while (token != NULL) {
                (*numCols)++;
                token = strtok(NULL, ";");
            }
        }
    }

    // Voltar para o início do arquivo
    fseek(file, 0, SEEK_SET);

    // Alocar matriz dinamicamente
    char*** matriz = (char***)malloc(*numRows * sizeof(char**));
    for (int i = 0; i < *numRows; i++) {
        matriz[i] = (char**)malloc(*numCols * sizeof(char*));
        for (int j = 0; j < *numCols; j++) {
            matriz[i][j] = (char*)malloc(1024 * sizeof(char));
        }
    }

    // Preencher a matriz com os dados do arquivo
    for (int i = 0; i < *numRows; i++) {
        fgets(buffer, sizeof(buffer), file);
        char* token = strtok(buffer, ";");
        for (int j = 0; j < *numCols; j++) {
            strcpy(matriz[i][j], token);
            token = strtok(NULL, ";");
        }
    }

    fclose(file);
    return matriz;
}

void printarquivo(char*** matriz, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%s\t", matriz[i][j]);
        }
        // printf("\n");
    }
}