#include "funcs.h"

//para rodar o c�digo:
// gcc -o meu_programa v2.c funcs.c


void administracao();
void venderBilhetes();
void validarBilhetes();
void acessarObras();
void resumoVendas();
void responderquestionario(int arquivo);
#define true 1
#define false 0



int main(){
    
    system("chcp 65001 > null");

//  credenciais = lerCredenciais();
    int credenciais = 1;

    int linhas;
    int colunas;
    char ***configs = lerarquivo("Temas\\CONFIGS.csv", &linhas, &colunas);

    // Alocar mem�ria dinamicamente para nomes
    char **nomes = (char **)malloc((linhas - 1) * sizeof(char *));
    if (nomes == NULL) {
        perror("Erro na aloca��o de mem�ria");
        exit(EXIT_FAILURE);
    }

    // Alocar mem�ria dinamicamente para caminhoArquivos
    char **caminhoArquivos = (char **)malloc((linhas - 1) * sizeof(char *));
    if (caminhoArquivos == NULL) {
        perror("Erro na aloca��o de mem�ria");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < linhas; i++) {
        nomes[i - 1] = strdup(configs[i][0]);
        caminhoArquivos[i - 1] = strdup(configs[i][1]);
    }

    // for (int i = 0; i < linhas - 1; i++) {
    //     printf("Nomes: %s\n", nomes[i]);
    //     printf("Caminho: %s\n", caminhoArquivos[i]);
    // }

    // Libere a mem�ria alocada
    for (int i = 0; i < linhas - 1; i++) {
        free(nomes[i]);
        free(caminhoArquivos[i]);
    }

    free(nomes);
    free(caminhoArquivos);

    // Libere a mem�ria alocada para configs
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            free(configs[i][j]);
        }
        free(configs[i]);
    }
    free(configs);

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
            char meiaouinteira[][30] = {"Inteira", "Meia", "Isento", "Voltar"};
            char *moi = &meiaouinteira[0][0];


            while (true)
            {   
                system("cls");
                printf("\n\tSELECIONE QUAL OBRA VOCE DESEJA COMPRAR:\n\n");
                telainicial(escolha, alt , 1, 5);
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
                            telainicial(escolha, alt , 1, 5);
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

    lerarquivoevalidar();

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
        printf("\n\tSELECIONE O TEMA QUE VOCE DESEJA:\n\n");
        telainicial(escolha, alt , 1, 5);  //cria os textos da tela inicial, incluindo aonde esta selecionado
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
                        printf("\n\tQUESTIONARIO: %s", alternativas[escolha]);
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

    // Aqui você pode calcular a somatória a cada 3 meses para cada tipo de ingresso
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