#include "funcs.h"

#include <stdio.h>
#include <dirent.h>


#define true 1
#define false 0

char*** lerarquivo(const char* filepath, int* numRows, int* numCols) 
{
    char *separador = ";";

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
            char* token = strtok(buffer, separador);
            while (token != NULL) {
                (*numCols)++;
                token = strtok(NULL, separador);
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
        char* token = strtok(buffer, separador);
        for (int j = 0; j < *numCols; j++) {
            token[strcspn(token, "\n")] = '\0'; // Remove o '\n' se estiver presente
            strcpy(matriz[i][j], token);
            token = strtok(NULL, separador);
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
        printf("\n");
    }
}





void listarNomesArquivos(const char *caminho, const char *tipo, char ***nomesArquivos, int *numArquivos) {
    DIR *dir;
    struct dirent *entrada;
    int numArq = 0;
    char **nomes = NULL;

    dir = opendir(caminho);

    if (dir == NULL) {
        perror("Erro ao abrir a pasta");
        exit(EXIT_FAILURE);
    }

    while ((entrada = readdir(dir)) != NULL) {
        if (strstr(entrada->d_name, tipo)) {
            // Alocar memória para armazenar o nome do arquivo
            nomes = (char **)realloc(nomes, (numArq + 1) * sizeof(char *));
            nomes[numArq] = strdup(entrada->d_name);
            numArq++;
        }
    }

    closedir(dir);

    *nomesArquivos = nomes;
    *numArquivos = numArq;
}

void listarNomesPastas(const char *caminho, char ***nomesPastas, int *numPastas) {
    DIR *dir;
    struct dirent *entrada;
    int numPasta = 0;
    char **nomes = NULL;

    dir = opendir(caminho);

    if (dir == NULL) {
        perror("Erro ao abrir a pasta");
        exit(EXIT_FAILURE);
    }

    while ((entrada = readdir(dir)) != NULL) {
        if (entrada->d_type == DT_DIR) { // Verifica se é um diretório
            // Ignora as entradas '.' e '..'
            if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
                continue;
            }

            // Alocar memória para armazenar o nome da pasta
            nomes = (char **)realloc(nomes, (numPasta + 1) * sizeof(char *));
            nomes[numPasta] = strdup(entrada->d_name);
            numPasta++;
        }
    }

    closedir(dir);

    *nomesPastas = nomes;
    *numPastas = numPasta;
}




void telainicial(int escolha, char *alternativas, int orientacao, int num_op){    
    char opcoes[NUM_OP][T_PONT];
    char *p = &opcoes[0][0]; //aponta para o endereï¿½o de memï¿½ria opcoes[0][0]
    opcao(escolha, &opcoes[0][0], num_op); //cria o vetor de texto do campo de seleï¿½ï¿½o (onde ï¿½ "--->" e onde ï¿½ "    " )
    

        int cont=0;

        for (int i = 0; i < num_op; i++)
        {
            for (int j = 0; j < T_PONT; j++)
            {
                if (j == T_PONT){
                    cont++;
                }
                printf("%c", p[cont]);
                cont++;
            }
        
            while (*alternativas!='\0')
            {
                printf("%c", *alternativas);
                alternativas++;
            }
            while (*alternativas == '\0'){
                // printf("X");
                alternativas++;
            }
            if ( orientacao == 1){
                printf("\n");
            }
                


        }
}

void telainicial2(int escolha, char *alternativas[], int orientacao, int num_op) {
    char opcoes[NUM_OP][T_PONT];
    char *p = &opcoes[0][0];
    opcao(escolha, p, num_op);

    for (int i = 0; i < num_op; i++) {
        printf("%s%s\n", opcoes[i], alternativas[i]);
    }
}


int retornar_selecao(int *p_escolha, int num_op){
    
    char teclapressionada;
    int loop=true;
        while (loop == true){

            if (kbhit()) { // verifica se alguma tecla foi precionada
                teclapressionada = getch(); // Le a tecla pressionada
                if (teclapressionada == -32) {

                    teclapressionada = getch();
                    // printf("%d", teclapressionada);
                    if ((teclapressionada == 72)||(teclapressionada == 75)){ //seta para cima e para a esquerda
                        if (*p_escolha == 0){
                            *p_escolha = num_op-1;
                        }
                        else if ((*p_escolha > 0)&&(*p_escolha <= num_op)){
                            *p_escolha= *p_escolha-1;
                        }
                        loop = false;
                    }
                    if ((teclapressionada == 80)||(teclapressionada == 77)){ //seta para baixo e para a direita
                        if (*p_escolha == num_op-1){
                            *p_escolha = 0;
                        }
                         else if ((*p_escolha >= 0)&&(*p_escolha < num_op)){
                            *p_escolha= *p_escolha+1;
                        }
                        loop = false;
                    }
                }
                else if (teclapressionada  == 13)
                {
                    return 1;
                }
                
            }
        }
    return 0;
}

char* opcao(int e, char *ponteiro, int num_op){
    char *p0 = ponteiro;
    for (int i = 0; i < num_op; i++)
    {   
        for (int j = 0; j < T_PONT-1; j++)
        {
            *ponteiro = ' ';
            ponteiro++;
        }
        *ponteiro = '\0';
        ponteiro++;

        
    }
    ponteiro = p0;
    ponteiro = ponteiro + (e*T_PONT);
    for (int i = 0; i < T_PONT-2; i++)
    {
    *ponteiro = '-';
    ponteiro++;
    }
    *ponteiro = '>';
    ponteiro++;
    *ponteiro = '\0';

    ponteiro=p0;
    return 0;
}

char* horaAtual() {
    time_t tempo_atual;
    struct tm *info_tempo;
    static char buffer[80]; // static para garantir que o buffer seja preservado

    // Obter o tempo atual
    time(&tempo_atual);

    // Converter o tempo atual em uma estrutura de tm
    info_tempo = localtime(&tempo_atual);

    // Formatando a hora atual como string
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", info_tempo);

    return buffer;
}

double codigoID() {
    time_t hora_atual;
    struct tm *info_tempo;

    // Obter o tempo atual
    time(&hora_atual);

    // Converter o tempo atual em uma estrutura de tm
    info_tempo = localtime(&hora_atual);

    // Calcular o nï¿½mero inteiro no formato "%y%m%d%H%M%S"
    double codigo = ((info_tempo->tm_year % 100) * 10000000000) +
                            ((info_tempo->tm_mon + 1)    * 100000000) +
                            (info_tempo->tm_mday         * 1000000) +
                            (info_tempo->tm_hour         * 10000) +
                            (info_tempo->tm_min          * 100) +
                            info_tempo->tm_sec;

    
    return codigo;
}

    

void ticket(char nomeobra[50], char char_meiaouinteira, char str_codigo[50], char hora[50]){

    char str_meiaouinteira[50];
    strNomalize(nomeobra);

    switch (char_meiaouinteira){
        case 'I':
            strcpy(str_meiaouinteira, "Inteira");
            break;

        case 'M':
            strcpy(str_meiaouinteira, "Meia   ");
            break;

        case 'X':
            strcpy(str_meiaouinteira, "Isento ");
            break;
    }

      printf("\t\t\t ______________________________________________ \n");
      printf("\t\t\t|                                              |\n");
      printf("\t\t\t|             1 TICKET PARA A OBRA:            |\n");
      printf("\t\t\t|                                              |");fflush(stdout);
    printf("\r\t\t\t| %s \n"                                        , nomeobra);
      printf("\t\t\t|                   %s                    |\n" , str_meiaouinteira);
      printf("\t\t\t|                                              |\n");
      printf("\t\t\t|                                              |\n");
      printf("\t\t\t|  id: %s                            |\n"      , str_codigo);
      printf("\t\t\t|                                              |\n");
      printf("\t\t\t|           hora da compra:%s |\n"             , hora);
      printf("\t\t\t|______________________________________________|\n");
      printf("\n\n\n");
}

int calcularTrimestre(const char *data_hora) {
    int dia, mes, ano, hora, minuto, segundo;
    if (sscanf(data_hora, "%d/%d/%d %d:%d:%d", &dia, &mes, &ano, &hora, &minuto, &segundo) == 6) {
        // Calcula o trimestre do ano
        int trimestre = (mes - 1) / 3 + 1;
        return trimestre;
    }
    
    // Se a anÃ¡lise da data falhar, retorne -1 para indicar um erro
    return -1;
}


int voltar(){
       printf("\t\t--->Voltar");
   int tecla;
   while((tecla!=13) && (tecla!=27)){
    tecla=getch();
    // printf("\n%d", tecla);
   }
   return 1;
}

void strNomalize(char *str) {
    int tamanhoDesejado = STR_NORMALIZADA;
    int tamanhoAtual = strlen(str);

    if (tamanhoAtual >= tamanhoDesejado) {
        // A string já tem o tamanho desejado ou é maior, não é necessário preencher.
        return;
    }

    int espacosFaltantes = tamanhoDesejado - tamanhoAtual;
    for (int i = 0; i < espacosFaltantes; i++) {
        strcat(str, " "); // Adiciona um espaço em branco no final da string.
    }
}


//