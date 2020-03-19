#include <stdio.h>
#include <stdlib.h>
#include "mtxMul.c"

void printMatrix(double ** mat, int num){
    printf("Matriz:\n");
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            printf("%.1f, ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]){

    int tam = atoi(argv[1]);

    double ** a = (double **) malloc(tam * sizeof(double *));
    double ** b = (double **) malloc(tam * sizeof(double *));
    double ** c = (double **) malloc(tam * sizeof(double *));
    
    
    for (int i = 0; i < tam; i++)
    {
        a[i] = (double*) malloc(tam * sizeof(double));
        b[i] = (double*) malloc(tam * sizeof(double));
        c[i] = (double*) malloc(tam * sizeof(double));
        
        for (int j = 0; j < tam; j++)
        {
            a[i][j] = 1.0;
            b[i][j] = 1.0;
            c[i][j] = 0.0;
        }
    }
    
    c = mtxMul(c, a, b, tam);

    // printMatrix(c, tam);

    return 0;
}