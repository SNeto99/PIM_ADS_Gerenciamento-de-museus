#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void responderquestionario(const char *perguntas, const char *respostas) {
    FILE *arquivoPerguntas = fopen("perguntas.txt", "r");
    FILE *arquivoRespostas = fopen("respostas.txt", "r");
    
    char linha[300];
    char respostaCorreta[15];  
    int questao = 1;
    float pontuacao = 0.0;

    if (arquivoPerguntas == NULL || arquivoRespostas == NULL) {
        printf("Erro ao abrir os arquivos de perguntas e respostas\n");
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
    
    printf("Voce acertou %.2f de 15 questoes\n", pontuacao);  
}

int main() {
    const char *perguntas = "perguntas.txt";
    const char *respostas = "respostas.txt";
    responderquestionario(perguntas, respostas);

    return 0;
}