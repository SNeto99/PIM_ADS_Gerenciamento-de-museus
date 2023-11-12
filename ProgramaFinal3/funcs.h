#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <time.h>

#define NUM_OP 6
#define T_PONT 5 
#define T_MAX_STR 255
#define N_MAX_TEMAS 10
#define N_MAX_OBRAS 10
#define N_MAX_QUEST 10

#define CAM_CREDENCIAL "credenciais.txt"
#define CAM_TICKETS "tickets.csv"
#define PASTA_TEMAS "Temas/"


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




char*** lerarquivo(const char* filepath, int* numRows, int* numCols);
void printarquivo(char*** matriz, int numRows, int numCols);


void telainicial(int escolha, char* alternativas, int orientacao, int num_op);
void telainicial2(int escolha, char *alternativas[], int orientacao, int num_op);
char* opcao(int e, char *ponteiro, int num_op);
int retornar_selecao(int *p_escolha, int num_op);
double codigoID();
char* horaAtual();
void ticket(char nomeobra[50], char char_meiaouinteira, char str_codigo[50], char hora[50]);
int calcularTrimestre(const char *data_hora);
void menuCredencial(int credenciais);

#endif