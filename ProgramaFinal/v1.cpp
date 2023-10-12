#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <time.h>

#define NUM_OP 5
#define TAM_SETA 5 



void telainicial(int escolha, char* alternativas, int orientacao);
char* opcao(int e, char *ponteiro);
int retornar_selecao(int *p_escolha);
void administracao();
void venderBilhetes();
void validarBilhetes();
void acessarObras();
void resumoVendas();
void responderquestionario(int obra);


int main(){
    administracao();
    return 0;
}

void telainicial(int escolha, char *alternativas, int orientacao){

    
    char opcoes[NUM_OP][TAM_SETA];
    char *p = &opcoes[0][0]; //aponta para o endereço de memória opcoes[0][0]
    opcao(escolha, &opcoes[0][0]); //cria o vetor de texto do campo de seleção (onde é "--->" e onde é "    " )


        int cont=0;

        for (int i = 0; i < NUM_OP; i++)
        {
            for (int j = 0; j < TAM_SETA; j++)
            {
                if (j == TAM_SETA){
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

int retornar_selecao(int *p_escolha){
    
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
                            *p_escolha = NUM_OP-1;
                        }
                        else if ((*p_escolha > 0)&&(*p_escolha <= NUM_OP)){
                            *p_escolha= *p_escolha-1;
                        }
                    loop = false;
                    }
                    if ((teclapressionada == 80)||(teclapressionada == 77)){ //seta para baixo e para a direita
                        if (*p_escolha == NUM_OP-1){
                            *p_escolha = 0;
                        }
                         else if ((*p_escolha >= 0)&&(*p_escolha < NUM_OP)){
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
}

char* opcao(int e, char *ponteiro){
    char *p0 = ponteiro;
    for (int i = 0; i < NUM_OP; i++)
    {   
        for (int j = 0; j < TAM_SETA-1; j++)
        {
            *ponteiro = ' ';
            ponteiro++;
        }
        *ponteiro = '\0';
        ponteiro++;

        
    }
    ponteiro = p0;
    ponteiro = ponteiro + (e*TAM_SETA);
    for (int i = 0; i < TAM_SETA-2; i++)
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

void lerplanilha(){

}




void administracao(){
    int escolha = 0;
    int *p_escolha = &escolha;
    char alternativas[][30] = {"VenderBilhetes", "ValidarBilhetes", "AcessarObras", "ResumoVendas","Sair"};
    char *alt = &alternativas[0][0];
    
    while (true)
    {   
        system("cls");
        printf("Bem vindo ao Programa de Administracao de Museus\nO que voce deseja fazer?\n\n");
        telainicial(escolha, alt , 1);  //cria os textos da tela inicial, incluindo aonde esta selecionado
       
        int isenter = retornar_selecao(p_escolha);
        if ((isenter == 1) && (escolha == 0)){
            venderBilhetes();
        }
        if ((isenter == 1) && (escolha == 1)){
            validarBilhetes();
        }
        if ((isenter == 1) && (escolha == 2)){
            responderquestionario();
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
    system("cls");
    printf("MENU DE VENDA DE BILHETES:\n\n\n");
    system("pause");
}

void validarBilhetes(){
    system("cls");
    printf("MENU DE VALIDACAO DE BILHETES:\n\n\n");
    system("pause");
}

void acessarObras(){
    system("cls");
    printf("ACESSO AS OBRAS:\n\n\n");
    system("pause");
}

void resumoVendas(){
    system("cls");
    printf("RESUMO DE VENDAS:\n\n\n");
    system("pause");
}

void responderquestionario(int obra) {
    if (obra == 1){
    FILE *arquivoPerguntas = fopen("C:\\Users\\netos\\Documents\\Programacao\\C\\PIM_ADS_Gerenciamento-de-museus\\temas\\santos_dumont\\PIM - Questionario\\perguntas.txt", "r");
    FILE *arquivoRespostas = fopen("C:\\Users\\netos\\Documents\\Programacao\\C\\PIM_ADS_Gerenciamento-de-museus\\temas\\santos_dumont\\PIM - Questionario\\respostas.txt", "r");
    }

    char linha[300];
    char respostaCorreta[15];  
    int questao = 1;
    int pontuacao = 0;

    if (arquivoPerguntas == NULL || arquivoRespostas == NULL) {
        printf("Erro ao abrir os arquivos de perguntas e respostas\n\n");
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
    
    printf("\n\nVoce acertou %d de 15 questoes\n\n\n", pontuacao);  
    system("pause");
}