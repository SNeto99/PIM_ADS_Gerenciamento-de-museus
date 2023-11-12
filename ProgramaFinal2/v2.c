#include "funcs.h"

//para rodar o código:
// gcc -o meu_programa v2.c funcs.c


void administracao();
void venderBilhetes();
void validarBilhetes();
void acessarObras();
void resumoVendas();
void responderquestionario(int tema, int obra);

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
    char descricao[T_MAX_STR^3];

};

struct Obra
{
    char nome[T_MAX_STR];
    struct Descricao descricao;
    struct Questao Questoes[N_MAX_QUEST];
    char caminho_quest[T_MAX_STR*2];
    int n_questoes;
};

struct Tema
{
    char nome[T_MAX_STR];
    char caminho_defs[T_MAX_STR*2];
    struct Obra obras[N_MAX_OBRAS];
    int n_obras;
};



struct Tema Temass[N_MAX_TEMAS];



char Temas[N_MAX_TEMAS][2][T_MAX_STR];
char Obras[N_MAX_TEMAS][2][T_MAX_STR];

int n_temas=0;
int n_obras_total=0;

// char Obras[N_MAX_TEMAS][N_MAX_OBRAS][][T_MAX_STR];
// int n_obras[N_MAX_TEMAS][N_MAX_OBRAS];



int main(){
    
    system("chcp 65001 > null");

//  credenciais = lerCredenciais();
    int credenciais = 1;

    int linhas=0;
    int colunas=0;
printf("debug");
    char ***configs = lerarquivo("Temas\\CONFIGS.csv", &linhas, &colunas);
    n_temas=linhas-1;

    printf("\n\n\n");
    for (int i = 1; i < linhas; i++) {
        strcpy(Temass[i - 1].nome, configs[i][0]);
        strcpy(Temass[i - 1].caminho_defs, configs[i][1]);
        strcat(Temass[i - 1].caminho_defs, "\\CONFIGS.csv");
        // printf("caminho das definicoes dos Temas=%s\n", Temass[i-1].caminho_defs);
    }
    // printf("numero de temas: %d\n\n\n\n", n_temas);

    // system("pause");


    
    for (int i=0;i<n_temas;i++)
    {
        linhas=0;
        colunas=0;
        // printf("\n\ncaminho das definicoes das Obras=%s\n\n", Temass[i].caminho_defs);
    printf("debug2");
        char ***def_obras = lerarquivo(Temass[i].caminho_defs, &linhas, &colunas);
        int n_obras_tema=linhas-1;

        for (int j = 1; j < linhas; j++) {
            strcpy(Temass[i].obras[j - 1].nome         , def_obras[j][0]);
            strcpy(Temass[i].obras[j - 1].caminho_quest, def_obras[j][1]);
        }

        // for (int j = 0; j < n_obras_tema; j++) {
        //     printf("Nomes: %s\n"  , Temass[i].obras[j].nome);
        //     printf("Caminho: %s\n", Temass[i].obras[j].caminho_quest);
        // }

        n_obras_total=n_obras_total + n_obras_tema;
        Temass[i].n_obras=n_obras_tema;
    }
        // printf("\n\nn_obras_total=%d\n\n\n", n_obras_total);


    // system("pause");
    
    
    menuCredencial(credenciais);





return 0;
}



void administracao(){
    int escolha = 0;
    int *p_escolha = &escolha;
    char alternativas[][30] = {"Vender Bilhetes", "Validar Bilhetes", "Acessar Temas", "Resumo Vendas","Sair"};
    char *alt = &alternativas[0][0];
    int num_op = 5;
    
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
    // char alternativas[N_MAX_TEMAS][T_MAX_STR];// = {OBRA1, OBRA2, OBRA3, OBRA4,"Voltar"};

    char *alt[N_MAX_TEMAS];
    for (int i=0; i<n_temas; i++){
        alt[i]= Temass[i].nome;
    }
    alt[n_temas] = "Voltar";
    
    // int num_op = 5;
    
    while (true)
    {   
        system("cls");
        printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
        telainicial2(escolha, alt , 1, n_temas+1);
    
        int isenter = retornar_selecao(p_escolha, n_temas+1);
        if (isenter == 1){
            int escolhatipo = 0;
            int *p_escolhatipo = &escolhatipo;
            char meiaouinteira[][30] = {"Inteira", "Meia", "Isento", "Voltar"};
            char *moi = &meiaouinteira[0][0];


            while (true)
            {   
                system("cls");
                printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
                telainicial2(escolha, alt , 1, n_temas+1);
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

void validarBilhetes(){
    system("cls");
    printf("MENU DE VALIDACAO DE BILHETES:\n\n\n");

    char ticket_validar[13];
    printf("Digite o nº do ticket para validar: ");
    scanf("%s", ticket_validar);
    
    int nlinhas, ncolunas;
    char ***tickets = lerarquivo("tickets.csv",&nlinhas, &ncolunas); 

    for (int i=0; i<nlinhas-1; i++){
        if (strcmp(tickets[i][0], ticket_validar) == 0)
        {
            printf("\nTicket validado:\n\n");
            ticket(tickets[i][1], *tickets[i][2], tickets[i][0], tickets[i][3]);
            break;
        }
        
    }
   


    system("pause");
}

void acessarObras(){
    int escolha = 0;
    int *p_escolha = &escolha;
    char *alt[N_MAX_TEMAS];
    for (int i=0; i<n_temas; i++){
        alt[i]= Temass[i].nome;
    }
    alt[n_temas] = "Voltar";

    
    while (true)
    {   
        system("cls");
        printf("\n\tSELECIONE O TEMA QUE VOCE DESEJA:\n\n");
        telainicial2(escolha, alt , 1, n_temas+1);  //cria os textos da tela inicial, incluindo aonde esta selecionado
        int isenter = 0;
        isenter= retornar_selecao(p_escolha, n_temas+1);
        
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
                telainicial2(escolha_obra, alt_2 , 1, num_op_obras);  //cria os textos da tela inicial, incluindo aonde esta selecionado
                int isenter_2 = 0;
                isenter_2= retornar_selecao(p_escolha_obra, num_op_obras);

                if ((isenter_2) && (escolha_obra != num_op_obras-1))
                {
                    int confirmar = 0;
                    int *p_confirmar = &confirmar;
                    char alternativas_3[][30] = {"Iniciar", "Voltar"};
                    char *alt_3 = &alternativas_3[0][0];
                    while (true)
                    {
                        system("cls");
                        printf("\n\tQUESTIONARIO: %s", alt[escolha]);
                        printf("\n\n\t");
                        telainicial(confirmar, alt_3 , 0, 2);  //cria os textos da tela inicial, incluindo aonde esta selecionado
                        int isenter_3 = 0;
                        isenter_3= retornar_selecao(p_confirmar, 2);
                        if ((isenter_3 == 1) && (confirmar == 0)){
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

void resumoVendas() {
    system("cls");

    int linhas=0;
    int colunas=0;
    char ***configs = lerarquivo("tickets.csv", &linhas, &colunas);
    
    struct Ingresso ingressos[linhas];
    

    for (int i = 0; i < linhas; i++) {
        strcpy(ingressos[i].codigo, configs[i][0]);
        strcpy(ingressos[i].nome, configs[i][1]);
        strcpy(ingressos[i].tipo, configs[i][2]);
        strcpy(ingressos[i].data_hora, configs[i][3]);
    }


    // Calcula a somatória a cada 3 meses para cada tipo de ingresso sendo I (inteira), M (Meia) e X (isento) separando por trimestre.
    int somatoria_trimestre_I[4] = {0, 0, 0, 0}; 
    int somatoria_trimestre_X[4] = {0, 0, 0, 0};
    int somatoria_trimestre_M[4] = {0, 0, 0, 0};

    for (int i = 0; i < linhas; i++) {
        char *data_hora = ingressos[i].data_hora;
        int trimestre = calcularTrimestre(data_hora);

        if (trimestre != -1) {
            if (strcmp(ingressos[i].tipo, "I") == 0) {
                somatoria_trimestre_I[trimestre - 1] += 1;
            } else if (strcmp(ingressos[i].tipo, "X") == 0) {
                somatoria_trimestre_X[trimestre - 1] += 1;
            } else if (strcmp(ingressos[i].tipo, "M") == 0) {
                somatoria_trimestre_M[trimestre - 1] += 1;
            }
        }
    }
    printf(" 10 ultimas vendas:\n\n");
    printf(" Codigo       Tema\t\t Tipo\t Data       Hora\n");


    for (int i = linhas - 1; i > linhas - 11; i --){
       printf(" %s %s %s\t %s\n", ingressos[i].codigo, ingressos[i].nome, ingressos[i].tipo, ingressos[i].data_hora);

    }
    // double ticket

    printf("\n\n\nSomatoria a cada 3 meses: \n");
    for (int t = 0; t < 4; t++) {
        printf("Trimestre %d - Tipo I: %d, Tipo X: %d, Tipo M: %d\n", t + 1, somatoria_trimestre_I[t], somatoria_trimestre_X[t], somatoria_trimestre_M[t]);
    }

   printf("\n\n\t\t\t--->Voltar");
   getch();
    

   }

void menuCredencial(int credenciais){
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
        printf("foi salvo");
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

