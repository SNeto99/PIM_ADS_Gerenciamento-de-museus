#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void listarArquivosCSV(const char *caminho, char ***caminhos, int *numArquivos) {
    DIR *dir;
    struct dirent *entrada;
    int numArq = 0;
    char **arquivos = NULL;

    dir = opendir(caminho);

    if (dir == NULL) {
        perror("Erro ao abrir a pasta");
        exit(EXIT_FAILURE);
    }

    while ((entrada = readdir(dir)) != NULL) {
        if (strstr(entrada->d_name, ".txt")) {
            char caminho_completo[1024];
            snprintf(caminho_completo, sizeof(caminho_completo), "%s/%s", caminho, entrada->d_name);

            // Alocar memória para armazenar o caminho do arquivo
            arquivos = (char **)realloc(arquivos, (numArq + 1) * sizeof(char *));
            arquivos[numArq] = strdup(caminho_completo);
            numArq++;
        }
    }

    closedir(dir);

    *caminhos = arquivos;
    *numArquivos = numArq;
}

int main() {
    const char *caminho = "C:\\Users\\netos\\Documents\\Programacao\\C\\PIM_ADS_Gerenciamento-de-museus\\ProgramaFinal\\Questionarios";  // Substitua pelo caminho da sua pasta
    char **caminhos;
    int numArquivos;

    listarArquivosCSV(caminho, &caminhos, &numArquivos);

    printf("Caminhos dos arquivos CSV na pasta '%s':\n", caminho);
    for (int i = 0; i < numArquivos; i++) {
        printf("%s\n", caminhos[i]);
        free(caminhos[i]);
    }
    free(caminhos);

    

    return 0;
}
