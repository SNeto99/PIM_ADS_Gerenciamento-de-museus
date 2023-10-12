#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#define MAX_TICKETS 100000

typedef struct {
    int numero;
    int secao;
    int valido;
} Ticket;

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    
	float precos[4] = {10.0, 15.0, 20.0, 25.0};
    int opcao, meiaEntrada, codigo;
    int entradas[4] = {0};
    
	srand(time(NULL));
    
	Ticket tickets[MAX_TICKETS];
    
	int num_tickets_emitidos = 0;
    
	do {
        printf("Seções disponíveis:\n");
        for (int i = 0; i < 4; i++) {
            printf("%d. Seção %d - Preço: R$ %.2f\n", i + 1, i + 1, precos[i]);
        }
        do {
            printf("\nEscolha uma opção (1-4) ou 0 para finalizar a compra: \n");
            printf("(É RECOMENDADO FAZER A COMPRA DE UMA PESSOA POR VEZ !!! )");
            scanf("%d", &opcao);
            if (opcao >= 1 && opcao <= 4) {
                entradas[opcao - 1]++;
                printf("Você comprou uma entrada para a Seção %d.\n", opcao);
                if (num_tickets_emitidos < MAX_TICKETS) {
                    tickets[num_tickets_emitidos].numero = rand() % 100000;
                    tickets[num_tickets_emitidos].secao = opcao;
                    tickets[num_tickets_emitidos].valido = 1;
                    num_tickets_emitidos++;
                } else {
                    printf("Capacidade máxima de tickets atingida. Não é possível emitir mais tickets.\n");
                }
            } else if (opcao != 0) {
                printf("Opção inválida. Escolha uma opção de 1 a 4 ou 0 para finalizar a compra.\n");
            }
        } while (opcao != 0);

        float total = 0.0;
        printf("\nResumo da compra:\n");
        for (int i = 0; i < 4; i++) {
            if (entradas[i] > 0) {
                printf("Seção %d - Subtotal: R$ %.2f\n", i + 1, entradas[i] * precos[i]);
                printf("Meia entrada? Se sim, digite 1, senão digite outro número.\n");
                scanf("%i", &meiaEntrada);
                if (meiaEntrada == 1) {
                    total += (entradas[i] * precos[i]) / 2;
                } else {
                    total += entradas[i] * precos[i];
                }
            }
        }

        printf("\nTickets emitidos e sua validade:\n");
        for (int i = 0; i < num_tickets_emitidos; i++) {
            printf("Ticket %d - Seção %d - %s\n", tickets[i].numero, tickets[i].secao,
                   (tickets[i].valido ? "Válido" : "Inválido"));
        }

        printf("\nValor total da compra: R$ %.2f\n", total);
        printf("\nDigite 0000 se deseja encerrar o programa ou digite qualquer outro número para continuar:\n");
        scanf("%i", &codigo);
    } while (codigo != 0000);

    return 0;
}
