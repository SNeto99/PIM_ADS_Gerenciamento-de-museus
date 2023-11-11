#include <stdio.h>

// Defina uma estrutura para representar uma data
struct Date {
    int year;
    int month;
    int day;
};

// Função para verificar se um ano é bissexto
int ehBissexto(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// Função para calcular a diferença em dias entre duas datas
int diferencaDias(struct Date date1, struct Date date2) {
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int totalDias1 = date1.day;
    int totalDias2 = date2.day;

    for (int i = 1; i < date1.month; i++) {
        totalDias1 += diasPorMes[i];
        if (i == 2 && ehBissexto(date1.year)) {
            totalDias1++; // Fevereiro tem um dia a mais em anos bissextos
        }
    }

    for (int i = 1; i < date2.month; i++) {
        totalDias2 += diasPorMes[i];
        if (i == 2 && ehBissexto(date2.year)) {
            totalDias2++; // Fevereiro tem um dia a mais em anos bissextos
        }
    }

    totalDias1 += date1.year * 365 + (date1.year - 1) / 4 - (date1.year - 1) / 100 + (date1.year - 1) / 400;
    totalDias2 += date2.year * 365 + (date2.year - 1) / 4 - (date2.year - 1) / 100 + (date2.year - 1) / 400;

    return (totalDias2 - totalDias1);
}

int main() {
    // struct Date date1 = {2022, 11, 9};
    // struct Date date2 = {2023, 11, 20};


    double codigo = 231111013159;
    struct Date datecodigo = {abs(codigo / 10^10), (abs(codigo / 10^8)%100), (abs(codigo/10^6)%100)};

    
    struct Date datehoje = {2023, 11, 11};



    int diff = diferencaDias(datecodigo, datehoje);

    printf("Diferenca em dias: %d\n", diff);

    return 0;
}

