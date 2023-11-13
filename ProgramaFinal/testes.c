#include "funcs.h"
#include <dirent.h>


#define CAMINHO "C:\\Users\\netos\\Documents\\Programacao\\C\\PIM_ADS_Gerenciamento-de-museus\\ProgramaFinal\\tickets.csv"

int main2() {
    int numRows, numCols;
    char*** matriz = lerarquivo(CAMINHO, &numRows, &numCols);
    printarquivo(matriz, numRows, numCols);

    // Liberar a memória alocada
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            free(matriz[i][j]);
        }
        free(matriz[i]);
    }
    free(matriz);
    printf("\nrows:%i \ncols:%i\n\n", numRows, numCols);
    system("pause");

    return 0;
}


// Declaração da função de leitura de arquivo CSV (como definida anteriormente)
// char ***lerarquivo(const char *filepath, int *numRows, int *numCols);

void listarConteudoPasta(const char *caminho) {
    DIR *dir;
    struct dirent *entrada;

    dir = opendir(caminho);

    if (dir == NULL) {
        perror("Erro ao abrir a pasta");
        exit(EXIT_FAILURE);
    }

    printf("Lendo arquivos CSV da pasta '%s':\n", caminho);

    while ((entrada = readdir(dir)) != NULL) {
        if (strstr(entrada->d_name, ".csv")) {
            char caminho_completo[1024];
            snprintf(caminho_completo, sizeof(caminho_completo), "%s/%s", caminho, entrada->d_name);

            int numRows, numCols;
            printf("%s", caminho_completo);
            char ***matriz = lerarquivo(caminho_completo, &numRows, &numCols);

            if (matriz != NULL) {
                printf("Arquivo: %s\n", entrada->d_name);
                printf("Número de linhas: %d\n", numRows);
                printf("Número de colunas: %d\n", numCols);

                // Processar a matriz conforme necessário

                // Liberar memória alocada
                for (int i = 0; i < numRows; i++) {
                    for (int j = 0; j < numCols; j++) {
                        free(matriz[i][j]);
                    }
                    free(matriz[i]);
                }
                free(matriz);
            } else {
                printf("Erro ao processar o arquivo: %s\n", entrada->d_name);
            }
        }
    }

    closedir(dir);
}

int main() {
    const char *caminho = "C:\\Users\\netos\\Documents\\Programacao\\C\\PIM_ADS_Gerenciamento-de-museus\\ProgramaFinal2\\tickets";  // Substitua pelo caminho da sua pasta
    listarConteudoPasta(caminho);

    return 0;
}