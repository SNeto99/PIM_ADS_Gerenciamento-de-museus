#include "funcs.h"

#include <stdio.h>

#define true 1
#define false 0

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

int retornar_selecao(int *p_escolha, int num_op){
    
    char teclapressionada;
    int loop=true;
        while (loop == true){

            if (kbhit()) { // verifica se alguma tecla foi precionada
                teclapressionada = getch(); // Lï¿½ a tecla pressionada
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

void salvarCompra(int obra, int meiaouinteira){

    char nomeobra[50];
    char char_meiaouinteira;
    double codigo = codigoID();

    switch (obra){
        case 0:
            strcpy(nomeobra, OBRA1);
            break;

        case 1:
            strcpy(nomeobra, OBRA2);
            break;
    
        case 2:
            strcpy(nomeobra, OBRA3);
            break;
        
        case 3:
            strcpy(nomeobra, OBRA4);
            break;
    }
    
    switch (meiaouinteira){
        case 0:
            char_meiaouinteira = 'I';
            break;

        case 1:
            char_meiaouinteira = 'M';
            break;

        case 2:
            char_meiaouinteira = 'X';
            break;
    }
        
    
    FILE *arquivo = fopen("tickets.csv", "a");
    

    if (arquivo != NULL)
    {
            char *hora = horaAtual();
            fprintf(arquivo, "%.f;"    , codigo);
            fprintf(arquivo, "%s;" , nomeobra);
            fprintf(arquivo, "%c;" , char_meiaouinteira);
            fprintf(arquivo, "%s\n", hora);
            fclose(arquivo);

            char str_codigo[50];
            sprintf(str_codigo, "%.f", codigo);
            ticket(nomeobra, char_meiaouinteira, str_codigo, hora);
            system("pause");


        }
    else {
        printf("Erro ao abrir o arquivo para salvar os tickets.\n");
        system("pause");
    }
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

// void lerarquivo(){
//     FILE *arquivo;
//     arquivo = fopen(CAM_TICKETS, "r");
//
//     char matriz[100][4][30];
//     int linhas = 0;
//
//     if (arquivo != NULL) 
//     {
//         char *m1;
//         char *m2;
//         char *m3;
//         char *m4;
//
//
//         do
//         {
//             m1=matriz[linhas][0];
//             m2=matriz[linhas][1];
//             m3=matriz[linhas][2];
//             m4=matriz[linhas][3];
//             linhas++;
//
//
//         } while(fscanf(arquivo, "%[^;];%[^;];%[^;];%[^\n]\n", m1, m2, m3, m4) != EOF);
//
//         fclose(arquivo);
//         printf("\n");
//     }
//
//     else{
//         printf("Erro ao abrir o arquivo.\n");
//         system("pause");
//     }
//    
//     for (int i=0; i<linhas-1; i++){
//         printf("%s ; %s ; %s ; %s\n", matriz[i][0], matriz[i][1], matriz[i][2], matriz[i][3]);
//     }
// 
// }

void lerarquivoevalidar() {
    
    char ticket_validar[13];
    printf("Digite o nï¿½ do ticket para validar: ");
    scanf("%s", ticket_validar);
    
    FILE *arquivo;
    arquivo = fopen(CAM_TICKETS, "r");

    char matriz[100][4][30];
    int linhas = 0;

    if (arquivo != NULL) 
    {
        char *m1;
        char *m2;
        char *m3;
        char *m4;


        do
        {
            m1=matriz[linhas][0];
            m2=matriz[linhas][1];
            m3=matriz[linhas][2];
            m4=matriz[linhas][3];
            linhas++;


        } while(fscanf(arquivo, "%[^;];%[^;];%[^;];%[^\n]\n", m1, m2, m3, m4) != EOF);

        fclose(arquivo);
        printf("\n");
    }

    else{
        printf("Erro ao abrir o arquivo.\n");
        system("pause");
    }


    for (int i=0; i<linhas-1; i++){
        if (strcmp(matriz[i][0], ticket_validar) == 0)
        {
            printf("\nTicket validado:\n\n");
            ticket(matriz[i][1], *matriz[i][2], matriz[i][0], matriz[i][3]);
            break;
        }
        
    }
   
}

void ticket(char nomeobra[50], char char_meiaouinteira, char str_codigo[50], char hora[50]){

    char str_meiaouinteira[50];

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
    printf("\t\t\t|                %s          |\n"              , nomeobra);
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

void responderquestionario(int arquivo) {
    FILE *arquivoPerguntas;
    FILE *arquivoRespostas;

    switch (arquivo)
    {
        case 0:
            arquivoPerguntas = fopen(CP_OBRA1, "r");
            arquivoRespostas = fopen(CR_OBRA1, "r");
            break;
        case 1:
            arquivoPerguntas = fopen(CP_OBRA2, "r");
            arquivoRespostas = fopen(CR_OBRA2, "r");
            break;
        case 2:
            arquivoPerguntas = fopen(CP_OBRA3, "r");
            arquivoRespostas = fopen(CR_OBRA3, "r");
            break;
        case 3:
            arquivoPerguntas = fopen(CP_OBRA4, "r");
            arquivoRespostas = fopen(CR_OBRA4, "r");
            break;
    }
    

    char linha[300];
    char respostaCorreta[15];  
    int questao = 1;
    int pontuacao = 0;

    if (arquivoPerguntas == NULL || arquivoRespostas == NULL) {
        printf("Erro ao abrir os arquivos de perguntas e respostas\n\n");
        system("pause");
        return;
    }
  
    while (fgets(linha, sizeof(linha), arquivoPerguntas) != NULL) {
        system("cls");
        printf("Questao %d:\n", questao);
        printf("%s", linha);  

        char opcoes[4][100];  
        for (int i = 0; i < 4; i++) {
            fgets(opcoes[i], sizeof(opcoes[i]), arquivoPerguntas);  
            printf("%s", opcoes[i]);  
        }

        fgets(respostaCorreta, sizeof(respostaCorreta), arquivoRespostas);

        char resposta;
        printf("\nDigite sua resposta: ");
        scanf(" %c", &resposta);

        if (resposta == respostaCorreta[0]) {
            pontuacao++;  
        }

        questao++;  
    }

    fclose(arquivoPerguntas);
    fclose(arquivoRespostas);
    
    system("cls");

    printf("\n\n");
    printf("\t ________________________________________ \n");
    printf("\t|                                        |\n");
    printf("\t|     Voce acertou %02d de 15 questoes    |\n", pontuacao);
    printf("\t|________________________________________|\n");
    printf("\n\n\n");
    system("pause");
}








//