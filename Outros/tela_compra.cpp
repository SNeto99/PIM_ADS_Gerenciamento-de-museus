#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#define NUMSES  4

typedef struct {
    int numero;
    int secao;
    int valido;
} Ticket;

typedef struct {
    char nome[255];
    float preco;
} Sessao;



void sla(){
    Sessao ses[NUMSES];

    strcpy(ses[0].nome, "sessao de arte moderna        ");
    ses[0].preco = 10;
    strcpy(ses[2].nome, "sessao de arte espacial       ");
    ses[1].preco = 15;
    strcpy(ses[1].nome, "sessao de inovacoes espaciais ");
    ses[2].preco = 20;
    strcpy(ses[3].nome, "sessao de inovacoes modernas  ");
    ses[3].preco = 25;



    int n_sessoes = sizeof(ses) / sizeof(ses[0]);

    printf("Sessoes disponiveis:\n\n");
    for (int i=0; i < n_sessoes; i++){
    printf("        %d - %s- R$%.2f \n", i+1, ses[i].nome, ses[i].preco);
    }
}


int main(){
    int v[50],q=0,e;
    char entrada[50];
    
    while (entrada != "000"){
        system("cls");
        sla();
        printf("\n\n\n\t\t\t\texposicao 1: %d", q);
        // printf("%d", q);
        // for (int i = 0; i<q ; i++)
        // {
        // }
        printf("\n\n\n\t\tQuantos ingressos voce deseja?\n");
        scanf("%d", &e);
        q=q+e;
        
    }

    return 0;
}


