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


#define OBRA1 "Santos Dumont       "
#define CP_OBRA1 "Questionarios\\questionario_Santos-Dumont.txt"
#define CR_OBRA1 "Questionarios\\respostas_Santos-Dumont.txt"

#define OBRA2 "Arte Moderna        "
#define CP_OBRA2 "Questionarios\\questionario_Arte-Moderna.txt"
#define CR_OBRA2 "Questionarios\\respostas_Arte-Moderna.txt"

#define OBRA3 "Exploracao Espacial "
#define CP_OBRA3 "Questionarios\\questionario_Espacial.txt"
#define CR_OBRA3 "Questionarios\\respostas_Espacial.txt"

#define OBRA4 "Jogos Olimpicos     "
#define CP_OBRA4 "Questionarios\\questionario_Jogos-Olimpicos.txt"
#define CR_OBRA4 "Questionarios\\respostas_Jogos-Olimpicos.txt"

#define CAM_TICKETS "tickets.csv"











char*** lerarquivo(const char* filepath, int* numRows, int* numCols);
void printarquivo(char*** matriz, int numRows, int numCols);


void telainicial(int escolha, char* alternativas, int orientacao, int num_op);
void telainicial2(int escolha, char *alternativas[], int orientacao, int num_op);
char* opcao(int e, char *ponteiro, int num_op);
int retornar_selecao(int *p_escolha, int num_op);
void salvarCompra(int obra, int meiaouinteira);
double codigoID();
char* horaAtual();
// void lerarquivo();
void lerarquivoevalidar();
void ticket(char nomeobra[50], char char_meiaouinteira, char str_codigo[50], char hora[50]);
int calcularTrimestre(const char *data_hora);
void responderquestionario(int arquivo);
void menuCredencial(int credenciais);

#endif