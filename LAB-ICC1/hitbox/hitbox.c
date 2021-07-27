#include <stdio.h>
#include <stdlib.h>

int main() {

    long int xInicial1, yInicial1, larguraInicial1, alturaInicial1;
    long int xInicial2, yInicial2, larguraInicial2, alturaInicial2;
    scanf ("%ld %ld %ld %ld", &xInicial1, &yInicial1, &larguraInicial1, &alturaInicial1);
    scanf ("%ld %ld %ld %ld", &xInicial2, &yInicial2, &larguraInicial2, &alturaInicial2);

    // Saber quem é maior e quem é menor em X.
    long int xMaior, larguraMaior, xMenor, larguraMenor;
    if (larguraInicial1 > larguraInicial2) {
        
        xMaior = xInicial1;
        larguraMaior = larguraInicial1;
        xMenor = xInicial2;
        larguraMenor = larguraInicial2;
    }
    else {
        xMaior = xInicial2;
        larguraMaior = larguraInicial2;
        xMenor = xInicial1;
        larguraMenor = larguraInicial1;
    }
    // Situações em que eles não se chocam em X.
    // Primeiro caso.
    long int xInter, larguraInter;
    if (larguraMaior + xMaior < xMenor || xMaior > xMenor + larguraMenor) {
        printf("MISS\n");
        exit(1);
    } // Segundo Caso
    else if (xMaior <= xMenor && xMaior + larguraMaior <= xMenor + larguraMenor && xMenor <= xMaior + larguraMaior) {
        xInter = xMenor;
        larguraInter = larguraMenor - ((xMenor + larguraMenor) - (xMaior + larguraMaior));
    } // Terceiro Caso
    else if (xMaior >= xMenor && xMaior <= xMenor + larguraMenor && xMaior + larguraMaior >= xMenor + larguraMenor) {
        xInter = xMaior;
        larguraInter = larguraMaior - ((xMaior + larguraMaior) - (xMenor + larguraMenor));
    } // Quarto Caso
    else if (xMaior < xMenor && xMaior + larguraMaior > xMenor + larguraMenor) {
        xInter = xMenor;
        larguraInter = larguraMenor;
    }

    // Saber quem é maior e quem e menor em Y.
    long int yMaior, alturaMaior, yMenor, alturaMenor;
    if (alturaInicial1 > alturaInicial2) {
        
        yMaior = yInicial1;
        alturaMaior = alturaInicial1;
        yMenor = yInicial2;
        alturaMenor = alturaInicial2;
    }
    else {
        yMaior = yInicial2;
        alturaMaior = alturaInicial2;
        yMenor = yInicial1;
        alturaMenor = alturaInicial1;
    }
    // Situações em que eles não se chocam em Y.
    // Primeiro caso.
    long int yInter, alturaInter;
    if (alturaMaior + yMaior < yMenor || yMaior > yMenor + alturaMenor) {
        printf("MISS\n");
        exit(1);
    } // Segundo Caso
    else if (yMaior <= yMenor && yMaior + alturaMaior <= yMenor + alturaMenor && yMenor <= yMaior + alturaMaior) {
        yInter = yMenor;
        alturaInter = alturaMenor - ((yMenor + alturaMenor) - (yMaior + alturaMaior));
    } // Terceiro Caso
    else if (yMaior >= yMenor && yMaior <= yMenor + alturaMenor && yMaior + alturaMaior >= yMenor + alturaMenor) {
        yInter = yMaior;
        alturaInter = alturaMaior - ((yMaior + alturaMaior) - (yMenor + alturaMenor));
    } // Quarto Caso
    else if (yMaior < yMenor && yMaior + alturaMaior > yMenor + alturaMenor) {
        yInter = yMenor;
        alturaInter = alturaMenor;
    }
    printf("HIT: %ld %ld %ld %ld\n", xInter, yInter, larguraInter, alturaInter);

    return 0;
}