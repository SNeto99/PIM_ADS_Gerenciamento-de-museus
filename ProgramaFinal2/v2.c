#include "funcs.h"

//para rodar o código:
// gcc -o meu_programa v2.c funcs.c


void administracao();
void venderBilhetes();
void validarBilhetes();
void acessarObras();
void resumoVendas();
#define true 1
#define false 0


struct Questao
{
    char pergunta[T_MAX_STR];
    char alternativas[10][T_MAX_STR];
    char resposta;
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
    struct Descricao descricao;
    struct Questao Questoes[N_MAX_QUEST];
};

struct Tema
{
    char nome[T_MAX_STR];
    char caminho[T_MAX_STR];
    struct Obra obras[N_MAX_OBRAS];
};



struct Tema Temass[N_MAX_TEMAS];



char Temas[N_MAX_TEMAS][2][T_MAX_STR];
char Obras[N_MAX_TEMAS][2][T_MAX_STR];

int n_temas=0;

// char Obras[N_MAX_TEMAS][N_MAX_OBRAS][][T_MAX_STR];
int n_obras[N_MAX_TEMAS][N_MAX_OBRAS];



int main(){
    
    system("chcp 65001 > null");

//  credenciais = lerCredenciais();
    int credenciais = 1;

    int linhas=0;
    int colunas=0;
    char ***configs = lerarquivo("Temas\\CONFIGS.csv", &linhas, &colunas);
    n_temas=linhas-1;

    for (int i = 1; i <= n_temas; i++) {
        strcpy(Temass[i - 1].nome, configs[i][0]);
        strcpy(Temass[i - 1].caminho, configs[i][1]);
    }

    char caminho[T_MAX_STR];
    strcpy(caminho, Temass[0].caminho);
    strcat(caminho, "\\DEFINICOES.csv");
    printf("\n\ncaminho defs obra=%s\n\n\n", caminho);


    



    system("pause");




    linhas=0;
    colunas=0;
    char ***obras = lerarquivo(caminho, &linhas, &colunas);
    int n_obras=linhas-1;

    for (int i = 1; i <= n_obras; i++) {
        strcpy(Obras[i - 1][0], obras[i][0]);
        strcpy(Obras[i - 1][1], obras[i][1]);
    }

    for (int i = 0; i <= n_obras - 1; i++) {
        printf("Nomes: %s\n"  , Obras[i][0]);
        printf("Caminho: %s\n", Obras[i][1]);
    }
    printf("\n\nn_obras=%d\n\n\n",n_obras);

    system("pause");


    
    
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
    
    int num_op = 5;
    
    while (true)
    {   
        system("cls");
        printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
        telainicial2(escolha, alt , 1, 5);
    
        int isenter = retornar_selecao(p_escolha, num_op);
        if (isenter == 1){
            int escolhatipo = 0;
            int *p_escolhatipo = &escolhatipo;
            char meiaouinteira[][30] = {"Inteira", "Meia", "Isento", "Voltar"};
            char *moi = &meiaouinteira[0][0];


            while (true)
            {   
                system("cls");
                printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
                telainicial2(escolha, alt , 1, 5);
                if (escolha !=4){
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
                            telainicial2(escolha, alt , 1, 5);
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
        if ((isenter == 1) && (escolha == 4)){
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
    int num_op = 5;
    char *alt[N_MAX_TEMAS];
    for (int i=0; i<n_temas; i++){
        alt[i]= Temass[i].nome;
    }
    alt[n_temas] = "Voltar";



    
    
    while (true)
    {   
        system("cls");
        printf("\n\tSELECIONE O TEMA QUE VOCE DESEJA:\n\n");
        telainicial2(escolha, alt , 1, 5);  //cria os textos da tela inicial, incluindo aonde esta selecionado
        int isenter = 0;
        isenter= retornar_selecao(p_escolha, num_op);
        
        if ((isenter)&&(escolha != 4))
        {
            int escolha_obra = 0;
            int *p_escolha_obra = &escolha_obra;
            char alternativas_2[][30] = {"obra 1", "obra 2", "obra 3", "obra 4", "obra 5", "Voltar"};
            int num_op_obras = 6;
            char *alt_2 = &alternativas_2[0][0];






            while (true)
            {
                system("cls");
                printf("\n\tSELECIONE A OBRA QUE VOCE DESEJA:\n\n");
                telainicial(escolha_obra, alt_2 , 1, num_op_obras);  //cria os textos da tela inicial, incluindo aonde esta selecionado
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
                            responderquestionario(escolha);
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
        
        if ((isenter) && (escolha == 4)){
            printf("\n\n");
            break;
        }
    }
}

void resumoVendas() {
    system("cls");
    printf("RESUMO DE VENDAS:\n\n\n");
    
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
            m1 = matriz[linhas][0];
            m2 = matriz[linhas][1];
            m3 = matriz[linhas][2];
            m4 = matriz[linhas][3];
            linhas++;

        } while(fscanf(arquivo, "%[^;];%[^;];%[^;];%[^\n]\n", m1, m2, m3, m4) != EOF);

        fclose(arquivo);
        printf("\n");
    }
    else{
        printf("Erro ao abrir o arquivo.\n");
        system("pause");
        return;
    }

    struct Ingresso {
        char codigo[30];
        char tipo[30];
        char data_hora[30];
    };

    // Converta a matriz de strings para uma matriz de ingressos
    struct Ingresso ingressos[linhas];
    for (int i = 0; i < linhas; i++) {
        strcpy(ingressos[i].codigo, matriz[i][0]);
        strcpy(ingressos[i].tipo, matriz[i][2]);
        strcpy(ingressos[i].data_hora, matriz[i][3]);
    }

    // Aqui vocÃª pode calcular a somatÃ³ria a cada 3 meses para cada tipo de ingresso
    int somatoria_trimestre_I[4] = {0, 0, 0, 0}; // Para cada trimestre do ano (4 trimestres)
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

    printf("Somatoria a cada 3 meses:\n");
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
