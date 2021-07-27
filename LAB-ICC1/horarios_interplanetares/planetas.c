/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>


typedef unsigned long long int quantidade_t;


#define segundosDiaTerra 86400
#define segundosHora 3600
#define segundosMinuto 60


void funcaoTerra(quantidade_t *dias, quantidade_t *horas, quantidade_t *minutos, quantidade_t *segundos);
void funcaoVenus(quantidade_t *dias, quantidade_t *horas, quantidade_t *minutos, quantidade_t *segundos);
void funcaoMercurio(quantidade_t *dias, quantidade_t *horas, quantidade_t *minutos, quantidade_t *segundos);
void funcaoJupiter(quantidade_t *dias, quantidade_t *horas, quantidade_t *minutos, quantidade_t *segundos);


int main() {
    quantidade_t segundosInicial;
    char planeta[10];

    scanf("%llu %s", &segundosInicial, planeta);

    quantidade_t segundos = segundosInicial;

    quantidade_t dias, horas, minutos;

    if (strcmp(planeta, "Terra") == 0)
        funcaoTerra(&dias, &horas, &minutos, &segundosInicial);
    else if (strcmp(planeta, "Venus") == 0)
        funcaoVenus(&dias, &horas, &minutos, &segundosInicial);
    else if (strcmp(planeta, "Mercurio") == 0)
        funcaoMercurio(&dias, &horas, &minutos, &segundosInicial);
    else
        funcaoJupiter(&dias, &horas, &minutos, &segundosInicial);

    printf("%llu segundos no planeta %s equivalem a:\n", segundos, planeta);
    printf("%llu dias, %llu horas, %llu minutos e %llu segundos\n", dias, horas, minutos, segundosInicial);

    return 0;
}

void funcaoTerra(quantidade_t *dias, quantidade_t *horas, quantidade_t *minutos, quantidade_t *segundos) {
    *dias = *segundos / segundosDiaTerra;
    *segundos = *segundos - segundosDiaTerra * *dias;
    *horas = *segundos / segundosHora;
    *segundos = *segundos - segundosHora * *horas;
    *minutos = *segundos / segundosMinuto;
    *segundos = *segundos - segundosMinuto * *minutos;
}

void funcaoVenus(quantidade_t *dias, quantidade_t *horas, quantidade_t *minutos, quantidade_t *segundos) {
    quantidade_t segundoDia = 243 * segundosDiaTerra;

    *dias = *segundos / segundoDia;
    *segundos = *segundos - segundoDia * *dias;
    *horas = *segundos / segundosHora;
    *segundos = *segundos - segundosHora * *horas;
    *minutos = *segundos /segundosMinuto;
    *segundos = *segundos - segundosMinuto * *minutos;
}

void funcaoMercurio(quantidade_t *dias, quantidade_t *horas, quantidade_t *minutos, quantidade_t *segundos) {
    quantidade_t segundoDia = 58 * segundosDiaTerra + 16 * segundosHora;

    *dias = *segundos / segundoDia;
    *segundos = *segundos - segundoDia * *dias;
    *horas = *segundos / segundosHora;
    *segundos = *segundos - segundosHora * *horas;
    *minutos = *segundos /segundosMinuto;
    *segundos = *segundos - segundosMinuto * *minutos;
}

void funcaoJupiter(quantidade_t *dias, quantidade_t *horas, quantidade_t *minutos, quantidade_t *segundos) {
    quantidade_t segundoDia = 9 * segundosHora + 56 * segundosMinuto;

    *dias = *segundos / segundoDia;
    *segundos = *segundos - segundoDia * *dias;
    *horas = *segundos / segundosHora;
    *segundos = *segundos - segundosHora * *horas;
    *minutos = *segundos /segundosMinuto;
    *segundos = *segundos - segundosMinuto * *minutos;
}
