#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printarquivo(char*** matriz, int numRows, int numCols);
char*** lerarquivo(const char* filepath, int* numRows, int* numCols);


#endif