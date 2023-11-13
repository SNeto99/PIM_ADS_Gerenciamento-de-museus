//para rodar o código:
// gcc -o meu_programa v3.c funcs.c

//!Fazer:
// comentar o código
// tratamento de erros
// help()


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <time.h>
#include <dirent.h>


#define T_PONT 5 
#define T_MAX_STR 255
#define NUM_MAX_OP  10
#define N_MAX_TEMAS 10
#define N_MAX_OBRAS 10
#define N_MAX_QUEST 10

#define STR_NORMALIZADA 44

#define CAM_CREDENCIAL "credenciais.txt"
#define CAM_TICKETS    "tickets.csv"
#define PASTA_TEMAS    "Temas/"
#define CAM_TUTORIAL   "TUTORIAL.txt"


#define true 1
#define false 0

#define N_ALTERNATIVAS 4


struct Ingresso {
    char codigo[30];
    char nome[T_MAX_STR];
    char tipo[30];
    char data_hora[50];
};

struct Questao
{
    char pergunta[T_MAX_STR^2];
    char alternativas[10][T_MAX_STR];
    char resposta[10];
};

struct Descricao
{
    char nome[T_MAX_STR];
    char autor[T_MAX_STR];
    char data[T_MAX_STR];
    char tipo[T_MAX_STR];
    char descricao[T_MAX_STR^2];
};

struct Obra
{
    char nome[T_MAX_STR];
    char caminho_pasta_obra[T_MAX_STR];
    char caminho_quest[T_MAX_STR*2];
    char caminho_descr[T_MAX_STR*2];
    int n_questoes;
    struct Questao Questoes[N_MAX_QUEST];
    struct Descricao descricao;
};

struct Tema
{
    char nome[T_MAX_STR];
    char caminho_pasta[T_MAX_STR*2];
    struct Obra obras[N_MAX_OBRAS];
    int n_obras;
};


char*** lerarquivo(const char* filepath, int* numRows, int* numCols);
void printarquivo(char*** matriz, int numRows, int numCols);

void listarNomesArquivos(const char *caminho, const char *tipo, char ***nomesArquivos, int *numArquivos);
void listarNomesPastas(const char *caminho, char ***nomesPastas, int *numPastas);

void telainicial(int escolha, char* alternativas, int orientacao, int num_op);
void telainicial2(int escolha, char *alternativas[], int orientacao, int num_op);
char* opcao(int e, char *ponteiro, int num_op);
int retornar_selecao(int *p_escolha, int num_op);
double codigoID();
char* horaAtual();
void ticket(char nomeobra[50], char char_meiaouinteira, char str_codigo[50], char hora[50]);
int calcularTrimestre(const char *data_hora);
int voltar();
void strNomalize(char *str);
void salvarCompra(int obra, int meiaouinteira);



void administracao();
void venderBilhetes();
void validarBilhetes();
void acessarObras();
void resumoVendas();
void ajuda();

void responderquestionario(int tema, int obra);


struct Tema Temass[N_MAX_TEMAS];
int n_temas=0;
int n_obras_total=0;
int credenciais;


int main(int argc, char *argv[]){
    
    system("chcp 65001 > null");

    //Ler credenciais
    credenciais = atoi(argv[1]);
    if (!credenciais){
        int linhas=0, colunas=0;
        char ***arquivo_credenciais = lerarquivo(CAM_CREDENCIAL, &linhas, &colunas);
        credenciais=atoi(arquivo_credenciais[0][1]);
    }
    //Listar o nome e o caminho das pastas na pasta PASTA_TEMAS
    char **nomesPastas;
    int numPastas;
    listarNomesPastas(PASTA_TEMAS, &nomesPastas, &numPastas);
    n_temas=numPastas;
    for (int i = 0; i < numPastas; i++) {
        strcpy(Temass[i].nome, nomesPastas[i]);

        strcpy(Temass[i].caminho_pasta, PASTA_TEMAS);  
        strcat(Temass[i].caminho_pasta, nomesPastas[i]);
        strcat(Temass[i].caminho_pasta, "/");  

        free(nomesPastas[i]);
    }
    free(nomesPastas);
    //Listar os nomes e os caminhos dentro da pasta dentro da PASTA_TEMAS
    for (int i=0;i<n_temas;i++)
    {
        char **nomesPastas2;
        int numPastas2=0;

        listarNomesPastas(Temass[i].caminho_pasta, &nomesPastas2, &numPastas2);
        Temass[i].n_obras=numPastas2;
      
        for (int j = 0; j < numPastas2; j++) {
            strcpy(Temass[i].obras[j].nome, nomesPastas2[j]);
            strcpy(Temass[i].obras[j].caminho_pasta_obra, Temass[i].caminho_pasta);
            strcat(Temass[i].obras[j].caminho_pasta_obra, nomesPastas2[j]);
            strcat(Temass[i].obras[j].caminho_pasta_obra, "/");  
            strcpy(Temass[i].obras[j].caminho_quest, Temass[i].obras[j].caminho_pasta_obra);  
            free(nomesPastas2[j]);
        }

        for (int j=0;j<Temass[i].n_obras;j++)
            {
                char **nomesArquivosTXT;
                int numArquivosTXT;

                listarNomesArquivos(Temass[i].obras[j].caminho_quest, ".txt", &nomesArquivosTXT, &numArquivosTXT);
                for (int k = 0; k < numArquivosTXT; k++) {
                    strcat(Temass[i].obras[j].caminho_quest, nomesArquivosTXT[k]);
                    free(nomesArquivosTXT[k]);
                }
                free(nomesArquivosTXT);
            }

        for (int j=0;j<Temass[i].n_obras;j++)
            {
                char **nomesArquivosCSV;
                int numArquivosCSV=0;
                listarNomesArquivos(Temass[i].obras[j].caminho_pasta_obra, ".csv", &nomesArquivosCSV, &numArquivosCSV);
                char caminhodescricao[T_MAX_STR*2];
                for (int k = 0; k < numArquivosCSV; k++) {
                    strcpy(caminhodescricao, Temass[i].obras[j].caminho_pasta_obra);
                    strcat(caminhodescricao, nomesArquivosCSV[k]);
                    free(nomesArquivosCSV[k]);
                    strcpy(Temass[i].obras[j].caminho_descr, caminhodescricao);
                }
                free(nomesArquivosCSV);
            }


        free(nomesPastas2);
    }
   
    switch (credenciais)
    {
    case 1:
        administracao();
        break;
    case 2:
        venderBilhetes();
        break;
    case 3:
        validarBilhetes();
        break;
    case 4:
        acessarObras();
        break;
    }

return 0;
}



void administracao()
{
    int escolha = 0;
    int *p_escolha = &escolha;
    char alternativas[][30] = {"Vender Bilhetes", "Validar Bilhetes", "Acessar Temas", "Resumo Vendas","Ajuda","Sair"};
    char *alt = &alternativas[0][0];
    int num_op = 6;
    
    while (true)
    {   
        system("cls");
        printf("\nBem vindo ao Programa de Administracao de Museus\nO que voce deseja fazer?\n\n");
        telainicial(escolha, alt , 1, num_op);  //cria os textos da tela inicial, incluindo aonde esta selecionado
    
        int isenter = retornar_selecao(p_escolha, num_op);
        if ((isenter == 1) && (escolha == 0)){
            venderBilhetes();
        }
        if ((isenter == 1) && (escolha == 1)){
            validarBilhetes();
        }
        if ((isenter == 1) && (escolha == 2)){
            acessarObras();
        }
        if ((isenter == 1) && (escolha == 3)){
            resumoVendas();
        }
        if ((isenter == 1) && (escolha == 4)){
            ajuda();
        }
        if ((isenter == 1) && (escolha == 5)){
            printf("\n\n");
            break;
        }
    }
}

void venderBilhetes()
{
    int escolha = 0;
    int *p_escolha = &escolha;

    char *alt[N_MAX_TEMAS];
    for (int i=0; i<n_temas; i++){
        alt[i]= Temass[i].nome;
    }
    alt[n_temas] = "Voltar";

    int numop;
    if (credenciais == 1)
    {
        numop=n_temas+1;
    } 
    else {
        numop=n_temas;
    }
        
    while (true)
    {   
        system("cls");
        printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
        telainicial2(escolha, alt , 1, numop);
    
        int isenter = retornar_selecao(p_escolha, numop);
        if (isenter == 1){
            int escolhatipo = 0;
            int *p_escolhatipo = &escolhatipo;
            char meiaouinteira[][30] = {"Inteira", "Meia", "Isento", "Voltar"};
            char *moi = &meiaouinteira[0][0];

            while (true)
            {   
                system("cls");
                printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
                telainicial2(escolha, alt , 1, numop);
                if (escolha !=n_temas){
                    printf("\nSELECIONE O TIPO DE INGRESSO:\n\n");
                    telainicial(escolhatipo, moi , 0, 4);
                    int isinteira = retornar_selecao(p_escolhatipo, 4);
                    if ((isinteira == 1)&&(escolhatipo != 3)){

                        int confirmar = 0;
                        int *p_confirmar = &confirmar;
                        char escolha_conf[][15] = {"CONFIRMAR", "CANCELAR"};
                        char *p_escolha_conf = &escolha_conf[0][0]; 
                        int comprado = 0; 

                        while (true)
                        {
                            system("cls");
                            printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
                            telainicial2(escolha, alt , 1, n_temas+1);
                            printf("\nSELECIONE O TIPO DE INGRESSO:\n\n");
                            telainicial(escolhatipo, moi , 0, 4);

                            printf("\n\n\n");
                            telainicial(confirmar, p_escolha_conf, 1, 2);
                            comprado = retornar_selecao(p_confirmar, 2);

                            if ((comprado == 1)&&(confirmar==0))
                            {
                                salvarCompra(escolha, escolhatipo);
                                break;   
                            }
                            else if ((comprado == 1)&&(confirmar==1)){
                                break;
                            }
                        }
                        if (comprado == 1){
                            break;
                        }
                    }
                    if ((isinteira == 1)&&(escolhatipo == 3)){
                        break;
                    }
                }
                else{
                    break;
                }
            }
        }
        if ((isenter == 1) && (escolha == n_temas)){
            printf("\n\n");
            break;
        }
    }
}

void validarBilhetes()
{
    while (true)
    {
        system("cls");
        printf("MENU DE VALIDACAO DE BILHETES:\n\n\n");
    
        char ticket_validar[13];
        printf("Digite o nº do ticket para validar ");
        if (credenciais == 1){
            printf("(ou \"sair\" para sair)");
        }
        printf("\n\n\t\t\tno do ticket: ");
        scanf("%s", ticket_validar);
    
        if (strcmp(ticket_validar, "sair")&strcmp(ticket_validar, "SAIR"))
        {
            int nlinhas, ncolunas;
            char ***tickets = lerarquivo(CAM_TICKETS,&nlinhas, &ncolunas); 
            int buscaFinalizada = false;
            int i=0;
            while (!buscaFinalizada && i < nlinhas-1)
            {
                if (strcmp(tickets[i][0], ticket_validar) == 0)
                {
                    printf("\nTicket validado:\n\n");
                    ticket(tickets[i][1], *tickets[i][2], tickets[i][0], tickets[i][3]);
                    buscaFinalizada = true;
                    system("pause");
                }
                i++;
                if (i==nlinhas-1){
                    printf("\n\tTicket nao encontrado.\n\t\t\t");
                    system("pause");
                    break;
                }
            }    
        }
        else{
            break;
        }   
    }
}

void acessarObras()
{
 
    int escolha = 0;
    int *p_escolha = &escolha;
    char *alt[N_MAX_TEMAS];
    for (int i=0; i<n_temas; i++){
        alt[i]= Temass[i].nome;
    }
    alt[n_temas] = "Voltar";

    int numop;
    if (credenciais == 1)
    {
        numop=n_temas+1;
    } 
    else {
        numop=n_temas;
    }


    while (true)
    {   
        system("cls");
        printf("\n\tSELECIONE O TEMA QUE VOCE DESEJA:\n\n");
        telainicial2(escolha, alt , 1, numop);  //cria os textos da tela inicial, incluindo aonde esta selecionado
        int isenter = 0;
        isenter= retornar_selecao(p_escolha, numop);
        
        if ((isenter)&&(escolha != n_temas))
        {
            int escolha_obra = 0;
            int *p_escolha_obra = &escolha_obra;
            int num_op_obras = Temass[escolha].n_obras+1;

            char *alt_2[N_MAX_OBRAS];
            for (int i=0; i<Temass[escolha].n_obras; i++){
                alt_2[i]= Temass[escolha].obras[i].nome;
            }
            alt_2[Temass[escolha].n_obras] = "Voltar";


            while (true)
            {
                system("cls");
                printf("\n\tSELECIONE A OBRA QUE VOCE DESEJA:\n\n");
                //cria os textos da tela inicial, incluindo aonde esta selecionado
                telainicial2(escolha_obra, alt_2 , 1, num_op_obras);  
                int isenter_2 = 0;
                isenter_2= retornar_selecao(p_escolha_obra, num_op_obras);

                if ((isenter_2) && (escolha_obra != num_op_obras-1))
                {
                    int linhas=0, colunas=0;
                    char ***descricao = lerarquivo(Temass[escolha].obras[escolha_obra].caminho_descr, &linhas, &colunas);

                    int confirmar = 0;
                    int *p_confirmar = &confirmar;
                    char alternativas_3[][30] = {"Iniciar", "Voltar"};
                    char *alt_3 = &alternativas_3[0][0];

                    while (true)
                    {
                        system("cls");
                        printf("\n");
                        printarquivo(descricao, linhas, colunas);
                        printf("\n\n\nQUESTIONARIO:\n");
                        //cria os textos da tela inicial, incluindo aonde esta selecionado
                        telainicial(confirmar, alt_3 , 1, 2);  
                        int isenter_3 = 0;
                        isenter_3= retornar_selecao(p_confirmar, 2);
                        if ((isenter_3 == 1) && (confirmar == 0))
                        {
                            responderquestionario(escolha, escolha_obra);
                        }
                        if ((isenter_3 == 1) && (confirmar == 1)){
                            break;
                        }
                    }
                }

                if ((isenter_2 == 1) && (escolha_obra == num_op_obras-1)){
                    break;
                }
            }
        }

        if ((isenter) && (escolha == n_temas)){
            printf("\n\n");
            break;
        }
    }
}

void resumoVendas() 
{
    system("cls");

    int linhas=0;
    int colunas=0;
    char ***tickets = lerarquivo(CAM_TICKETS, &linhas, &colunas);
    
    struct Ingresso ingressos[linhas];
    
    for (int i = 0; i < linhas; i++) {
        strcpy(ingressos[i].codigo   , tickets[i][0]);
        strcpy(ingressos[i].nome     , tickets[i][1]);
        strcpy(ingressos[i].tipo     , tickets[i][2]);
        strcpy(ingressos[i].data_hora, tickets[i][3]);
    }


    // Calcula a somatória a cada 3 meses para cada tipo de ingresso sendo I (inteira), 
    // M (Meia) e X (isento) separando por trimestre.
    int somatoria_trimestre_I[4] = {0, 0, 0, 0}; 
    int somatoria_trimestre_X[4] = {0, 0, 0, 0};
    int somatoria_trimestre_M[4] = {0, 0, 0, 0};

    for (int i = 0; i < linhas; i++) {
        char *data_hora = ingressos[i].data_hora;
        int trimestre = calcularTrimestre(data_hora);

        if (trimestre != -1) 
        {
            if (strcmp(ingressos[i].tipo, "I") == 0) {
                somatoria_trimestre_I[trimestre - 1] += 1;
            } 
            else if (strcmp(ingressos[i].tipo, "X") == 0) {
                somatoria_trimestre_X[trimestre - 1] += 1;
            } 
            else if (strcmp(ingressos[i].tipo, "M") == 0) {
                somatoria_trimestre_M[trimestre - 1] += 1;
            }
        }
    }

    printf(" 10 ultimas vendas:\n\n");
    printf(" Codigo       Tema\t\t\t\t\t  Tipo     Data       Hora\n");

    for (int i = linhas - 1; (i>linhas-11) && (i>=0) ; i --){
       printf(" %s %s %s\t   %s\n", ingressos[i].codigo, ingressos[i].nome, ingressos[i].tipo, ingressos[i].data_hora);
    }
    // 

    printf("\n\n\nSomatoria por trimestre: \n");
                        printf("\t ______________________________________ \n");
                        printf("\t|            |Inteira |Meia    |Isento |\n");
    for (int t = 0; t < 4; t++) {
                        printf("\t|            |        |        |       |\n");
          printf("\t|%do Trimestre| % 4d   | % 4d   | % 4d  |\n", t + 1, somatoria_trimestre_I[t], somatoria_trimestre_M[t], somatoria_trimestre_X[t]);}
                        printf("\t|____________|________|________|_______|");

    voltar();
    

   }

void ajuda(){
    system("cls");

    int linhas, colunas;
    char ***tutorial = lerarquivo(CAM_TUTORIAL, &linhas, &colunas);
    printarquivo(tutorial, linhas, colunas);

    printf("\n\n\t\t");
    voltar();
}


void responderquestionario(int tema, int obra) {


        int linhas=0;
        int colunas=0;
        char ***questionario = lerarquivo(Temass[tema].obras[obra].caminho_quest, &linhas, &colunas);
        int n_questoes = linhas/(2+N_ALTERNATIVAS);

        for (int i = 0; i < n_questoes; i++) 
        {
            int rowIndex = i * (N_ALTERNATIVAS + 2);  // Calcula o índice da linha para a pergunta atual

            strcpy(Temass[tema].obras[obra].Questoes[i].pergunta               , questionario[rowIndex][0]);

            for (int j = 1; j <= N_ALTERNATIVAS; j++) 
            {
                strcpy(Temass[tema].obras[obra].Questoes[i].alternativas[j - 1], questionario[rowIndex + j][0]);
            }

            strcpy(Temass[tema].obras[obra].Questoes[i].resposta               , questionario[rowIndex + N_ALTERNATIVAS + 1][0]);
        }

    char resposta;
    int pontuacao = 0;

    for (int i=0; i<3; i++) 
    {
        char respostacorreta = Temass[tema].obras[obra].Questoes[i].resposta[0];

        system("cls");
        printf("Questao %d:\n", i+1);
        printf("%s\n", Temass[tema].obras[obra].Questoes[i].pergunta);  

        for (int j = 0; j < N_ALTERNATIVAS; j++) {
            printf("%s\n", Temass[tema].obras[obra].Questoes[i].alternativas[j]);  
        }

        printf("\nResposta: ");
        scanf(" %c", &resposta);

        if (resposta == respostacorreta) {
            pontuacao++;  
        }
    }

    
    system("cls");

    printf("\n\n");
    printf("\t ________________________________________ \n");
    printf("\t|                                        |\n");
    printf("\t|     Voce acertou %02d de %02d questoes     |\n", pontuacao, n_questoes);
    printf("\t|________________________________________|\n");
    printf("\n\n\n");
    system("pause");
}




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
    char opcoes[NUM_MAX_OP][T_PONT];
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
    char opcoes[NUM_MAX_OP][T_PONT];
    char *p = &opcoes[0][0];
    opcao(escolha, p, num_op);

    for (int i = 0; i < num_op; i++) {
        printf("%s%s", opcoes[i], alternativas[i]);
        if (orientacao == 1){
            printf("\n");
        }
    }
}


void salvarCompra(int tema, int meiaouinteira){

    char char_meiaouinteira;
    double codigo = codigoID();

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
        
    
    FILE *arquivo = fopen(CAM_TICKETS, "a");
    

    if (arquivo != NULL)
    {
            char nome[T_MAX_STR];
            strcpy(nome, Temass[tema].nome);
            strNomalize(nome);

            char *hora = horaAtual();
            fprintf(arquivo, "%.f;", codigo);
            fprintf(arquivo, "%s;" , nome);
            fprintf(arquivo, "%c;" , char_meiaouinteira);
            fprintf(arquivo, "%s\n", hora);
            fclose(arquivo);

            char str_codigo[50];
            sprintf(str_codigo, "%.f", codigo);
            ticket(Temass[tema].nome, char_meiaouinteira, str_codigo, hora);
            system("pause");


        }
    else {
        printf("Erro ao abrir o arquivo para salvar os tickets.\n");
        system("pause");
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