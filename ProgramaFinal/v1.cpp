#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <time.h>

#define NUM_OP 5
#define T_PONT 5 


#define OBRA1 "Santos Dumont       "
#define CP_OBRA1 "..\\Questionarios\\questionario_Santos-Dumont.txt"
#define CR_OBRA1 "..\\Questionarios\\respostas_Santos-Dumont.txt"

#define OBRA2 "Arte Moderna        "
#define CP_OBRA2 "..\\Questionarios\\questionario_Arte-Moderna.txt"
#define CR_OBRA2 "..\\Questionarios\\respostas_Arte-Moderna.txt"

#define OBRA3 "Exploracao Espacial "
#define CP_OBRA3 "..\\Questionarios\\questionario_Espacial.txt"
#define CR_OBRA3 "..\\Questionarios\\respostas_Espacial.txt"

#define OBRA4 "Jogos Olimpicos     "
#define CP_OBRA4 "..\\Questionarios\\questionario_Jogos-Olimpicos.txt"
#define CR_OBRA4 "..\\Questionarios\\respostas_Jogos-Olimpicos.txt"




void telainicial(int escolha, char* alternativas, int orientacao, int num_op);
char* opcao(int e, char *ponteiro, int num_op);
int retornar_selecao(int *p_escolha, int num_op);
void administracao();
void venderBilhetes();
void validarBilhetes();
void acessarObras();
void resumoVendas();
void responderquestionario(int arquivo);
void salvarCompra(int obra, int meiaouinteira);
double codigoID();
void ticket(int obra, int codigo);
void horaAtual();


int main(){
    int credenciais = 1;

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
    case 5:
        resumoVendas();
        break;
    }

return 0;
}



void telainicial(int escolha, char *alternativas, int orientacao, int num_op){

    
    char opcoes[NUM_OP][T_PONT];
    char *p = &opcoes[0][0]; //aponta para o endereço de memória opcoes[0][0]
    opcao(escolha, &opcoes[0][0], num_op); //cria o vetor de texto do campo de seleção (onde é "--->" e onde é "    " )
    

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
                teclapressionada = getch(); // Lê a tecla pressionada
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

void horaAtual(){
    time_t tempo_atual;
    struct tm *info_tempo;
    char buffer[80];

    // Obter o tempo atual
    time(&tempo_atual);

    // Converter o tempo atual em uma estrutura de tm
    info_tempo = localtime(&tempo_atual);

    // Formatando a hora atual como string
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", info_tempo);

    // Imprimir a hora atual
    printf("%s", buffer);
}

void salvarCompra(int obra, int meiaouinteira){

    char nomeobra[50];
    char c_meiaouinteira;
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
            c_meiaouinteira = 'I';
            break;

        case 1:
            c_meiaouinteira = 'M';
            break;
    }
    
    FILE *arquivo = fopen("tickets.csv", "a");
    

    if (arquivo != NULL) {
            fprintf(arquivo, "\'%.f\';", codigo);
            fprintf(arquivo, "\'%s\';", nomeobra);
            fprintf(arquivo, "\'%c\'\n", c_meiaouinteira);
            fclose(arquivo);

            
            printf("\t\t\t ______________________________________________ \n");
            printf("\t\t\t|                                              |\n");
            printf("\t\t\t|             1 TICKET PARA A OBRA:            |\n");
            printf("\t\t\t|                %s          |\n"              , nomeobra);
            printf("\t\t\t|                                              |\n");
            printf("\t\t\t|                                              |\n");
            printf("\t\t\t|  id: %.f                            |\n"     , codigo);
            printf("\t\t\t|                                              |\n");
            printf("\t\t\t|           hora da compra:");horaAtual()      ;printf(" |\n");
            printf("\t\t\t|______________________________________________|\n");
            printf("\n\n\n");
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

    // Calcular o número inteiro no formato "%y%m%d%H%M%S"
    double codigo = ((info_tempo->tm_year % 100) * 10000000000) +
                            ((info_tempo->tm_mon + 1)    * 100000000) +
                            (info_tempo->tm_mday         * 1000000) +
                            (info_tempo->tm_hour         * 10000) +
                            (info_tempo->tm_min          * 100) +
                            info_tempo->tm_sec;

    
    return codigo;
}

void lerplanilha(){//Fazer

}




void administracao(){
    int escolha = 0;
    int *p_escolha = &escolha;
    char alternativas[][30] = {"Vender Bilhetes", "Validar Bilhetes", "Acessar Questionarios", "Resumo Vendas","Sair"};
    char *alt = &alternativas[0][0];
    int num_op = NUM_OP;
    
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
            printf("\n\n");
            break;
        }
    }
}

void venderBilhetes(){
    int escolha = 0;
    int *p_escolha = &escolha;
    char alternativas[][30] = {OBRA1, OBRA2, OBRA3, OBRA4,"Voltar"};
    char *alt = &alternativas[0][0];
    int num_op = 5;
    
    while (true)
    {   
        system("cls");
        printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
        telainicial(escolha, alt , 1, 5);
       
        int isenter = retornar_selecao(p_escolha, num_op);
        if (isenter == 1){
            int escolhatipo = 0;
            int *p_escolhatipo = &escolhatipo;
            char meiaouinteira[][30] = {"Inteira", "Meia", "Voltar"};
            char *moi = &meiaouinteira[0][0];


            while (true)
            {   
                system("cls");
                printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
                telainicial(escolha, alt , 1, 5);
                if (escolha !=4){
                    printf("\nSELECIONE O TIPO DE INGRESSO:\n\n");
                    telainicial(escolhatipo, moi , 0, 3);
                    int isinteira = retornar_selecao(p_escolhatipo, 3);
                    if ((isinteira == 1)&&(escolhatipo != 2)){

                        int confirmar = 0;
                        int *p_confirmar = &confirmar;
                        char escolha_conf[][15] = {"CONFIRMAR", "CANCELAR"};
                        char *p_escolha_conf = &escolha_conf[0][0]; 
                        int comprado = 0;
                        

                        while (true)
                        {
                            system("cls");
                            printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
                            telainicial(escolha, alt , 1, 5);
                            printf("\nSELECIONE O TIPO DE INGRESSO:\n\n");
                            telainicial(escolhatipo, moi , 0, 3);

             
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
                    if ((isinteira == 1)&&(escolhatipo == 2)){
                        break;
                    }
                }
                else{
                    break;
                }
            }
            
        }
        if ((isenter == 1) && (escolha == 4)){
            printf("\n\n");
            break;
        }
    }
}

void validarBilhetes(){
    system("cls");
    printf("MENU DE VALIDACAO DE BILHETES:\n\n\n");
    system("pause");
}

void acessarObras(){
    int escolha = 0;
    int *p_escolha = &escolha;
    char alternativas[][30] = {OBRA1, OBRA2, OBRA3, OBRA4, "Sair"};
    int num_op = 5;
    char *alt = &alternativas[0][0];
    
    while (true)
    {   
        system("cls");
        printf("\n\tSELECIONE O QUESTIONARIO QUE VOCE DESEJA INICIAR:\n\n");
        telainicial(escolha, alt , 1, 5);  //cria os textos da tela inicial, incluindo aonde esta selecionado
       
        int isenter = 0;
        isenter= retornar_selecao(p_escolha, num_op);
        if ((isenter == 1) && (escolha == 0)){
            responderquestionario(0);
        }
        if ((isenter == 1) && (escolha == 1)){
            responderquestionario(1);

        }
        if ((isenter == 1) && (escolha == 2)){
            responderquestionario(2);

        }
        if ((isenter == 1) && (escolha == 3)){
            responderquestionario(3);

        }
        if ((isenter == 1) && (escolha == 4)){
            printf("\n\n");
            break;
        }
    }
}

void resumoVendas(){//Fazer
    system("cls");
    printf("RESUMO DE VENDAS:\n\n\n");
    system("pause");
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
    printf("\n\n\t Voce acertou %d de 15 questoes\n\n\n", pontuacao);  
    system("pause");
}