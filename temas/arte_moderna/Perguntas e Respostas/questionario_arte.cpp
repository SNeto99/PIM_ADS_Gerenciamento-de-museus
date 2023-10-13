#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void responderquestionario() {
    FILE *arquivoPerguntas = fopen("C:\\Users\\victo\\OneDrive\\Documentos\\GitHub\\PIM_ADS_Gerenciamento-de-museus\\temas\\arte_moderna\\Perguntas e Respostas\\questionario arte moderrna.txt", "r");
    FILE *arquivoRespostas = fopen("C:\\Users\\victo\\OneDrive\\Documentos\\GitHub\\PIM_ADS_Gerenciamento-de-museus\\temas\\arte_moderna\\Perguntas e Respostas\\respostas arte moderna.txt", "r");
    
    char linha[300];
    char respostaCorreta[15];  
    int questao = 1;
    int pontuacao = 0;

    if (arquivoPerguntas == NULL || arquivoRespostas == NULL) {
        printf("Erro ao abrir os arquivos de perguntas e respostas\n\n");
        return;
    }
  
    while (fgets(linha, sizeof(linha), arquivoPerguntas) != NULL) {
        printf("Questao %d:\n", questao);
        printf("%s", linha);  

        char opcoes[4][100];  
        for (int i = 0; i < 4; i++) {
            fgets(opcoes[i], sizeof(opcoes[i]), arquivoPerguntas);  
            printf("%s", opcoes[i]);  
        }

        fgets(respostaCorreta, sizeof(respostaCorreta), arquivoRespostas);

        char resposta;
        printf("\nSua resposta a, b, c ou d? ");
        scanf(" %c", &resposta);

        if (resposta == respostaCorreta[0]) {
            pontuacao++;  
        }

        questao++;  
    }

    fclose(arquivoPerguntas);
    fclose(arquivoRespostas);
    
    printf("Voce acertou %d de 15 questoes\n", pontuacao);  
}

int main() {

    responderquestionario();

    return 0;
}