#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#define MAX_TICKETS 10000

typedef struct {
    int id;
    int tema;
    int validacao;
} Ticket;

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    
	float precos[4] = {10.0, 15.0, 20.0, 25.0};
    int opcao, meiaEntrada, codigo;
    
	char temas[4][43];

    strcpy(temas[0], "100 ANOS SEMANA DE ARTE MODERNA");
    strcpy(temas[1], "150 ANOS DE SANTOS DUMONT");
    strcpy(temas[2], "JOGOS OLIMPICOS DE PARIS 2024");
    strcpy(temas[3], "EXPLORA��O ESPACIAL E FUTURO DA HUMANIDADE");
    
	srand(time(NULL));
    
	Ticket tickets[MAX_TICKETS];
    
	int num_tickets_emitidos = 0;
    
	do {
        int entradas[4] = {0};

        printf("Se��es dispon�veis:\n");
        for (int i = 0; i < 4; i++) {
            printf("Se��o %d %s - Pre�o: R$ %.2f\n", i + 1, temas[i], precos[i]);
        }
        do {
            printf("\nEscolha uma op��o (1-4) ou 0 para finalizar a compra: \n");

            printf("\n(� RECOMENDADO FAZER A COMPRA DE UMA PESSOA POR VEZ !!! )");
            scanf("%d", &opcao);
            if (opcao >= 1 && opcao <= 4) {
                entradas[opcao - 1]++;
                printf("Voc� comprou uma entrada para a Se��o %d.\n", opcao);
                if (num_tickets_emitidos < MAX_TICKETS) {
                    tickets[num_tickets_emitidos].id = rand() % 10000;
                    tickets[num_tickets_emitidos].tema = opcao;
                    tickets[num_tickets_emitidos].validacao = 1;
                    num_tickets_emitidos++;
                } else {
                    printf("Capacidade m�xima de tickets atingida. N�o � poss�vel emitir mais tickets.\n");
                }
            } else {
                printf("Op��o inv�lida. Escolha uma op��o de 1 a 4 ou 0 para finalizar a compra.\n");
            }
        } while (opcao != 0);

        float total = 0.0;
        float valorTotal = 0.0;
        printf("\nResumo da compra:\n");
        for (int i = 0; i < 4; i++) {
            if (entradas[i] > 0) {
                                printf("Meia entrada? Se sim, digite 1, se n�o digite outro n�mero.\n");
                scanf("%i", &meiaEntrada);
                if (meiaEntrada == 1) {
                    total += (entradas[i] * precos[i]) / 2;
                } else {
                    total += entradas[i] * precos[i];
                }
                valorTotal = total;
				printf("Se��o %d - Subtotal: R$ %.2f\n", i + 1, valorTotal);
				// total = 0.0;
        		// valorTotal = 0.0;
            }
        }

        printf("\nTickets emitidos e sua validade:\n");
        for (int i = 0; i < num_tickets_emitidos; i++) {
            printf("Ticket %d - Se��o %d - %s\n", tickets[i].id, tickets[i].tema,
                   (tickets[i].validacao ? "V�lido" : "Inv�lido"));
        }

        printf("\nValor valorTotal da compra: R$ %.2f\n", valorTotal);
        printf("\nDigite 000 se deseja encerrar o programa ou digite qualquer outro n�mero para continuar:\n");
        scanf("%i", &codigo);
    } while (codigo != 000);
    
    FILE *arquivo = fopen("tickets.csv", "w");
    
    if (arquivo != NULL) {
        for (int i = 0; i < num_tickets_emitidos; i++) {
            fprintf(arquivo, "%d", tickets[i].id);
            fprintf(arquivo, "%s", temas[i]);
            fprintf(arquivo, "%d\n", tickets[i].validacao);
        }
        fclose(arquivo);
        printf("Tickets salvos em 'tickets.csv'.\n");
    } else {
        printf("Erro ao abrir o arquivo para salvar os tickets.\n");
    }

    return 0;
}

