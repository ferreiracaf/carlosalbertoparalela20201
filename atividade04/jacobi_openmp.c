// Correção: Veja observação abaixo. 2,0 Pontos.
/*
    Loop unrolling. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "jacobi.h"

#define ECHO 0

int main(int argc, char *argv[]){
    int n;
    int iters = 0;
    double epsilon = 0.0;

    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &iters);
    
    double **grid = allocate2dMatrix(n+2,n+2);
    double **new = allocate2dMatrix(n+2,n+2);
    stableValues2dMatrix(grid, n+2, n+2);
    
    // omp_set_nested(1);
    // Estou achando que este for mais interno prejudica sua solução. As iterações do laço em k serão executadas em paralelo. Só que K é
    // "tempo" da simulação. Então, por exemplo, a iteração com k = 200, pode ser executado antes da iteração com k = 20. A solução correta seria
    // inverter seus comentários: comentar a parallel for externa e descomentar a externa. Como parece que você ficou em dúvida nesta situação, irei considerar. 
    #pragma omp parallel for
    for (int k = 0; k < iters; k = k + 2) {
        // #pragma omp parallel for
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) 
                new[i][j] = (grid[i-1][j] + grid[i+1][j] + grid[i][j-1] + grid[i][j+1]) * 0.25;
        // #pragma omp parallel for
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) 
                grid[i][j] = (new[i-1][j] + new[i+1][j] + new[i][j-1] + new[i][j+1]) * 0.25;
    }

    double maxdiff = 0.0;
    #pragma omp parallel for collapse(2)
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            maxdiff = fmax(maxdiff, fabs(new[i][j]-grid[i][j]));
        }
        
    printf("Diferença: %.5f\n", maxdiff);

    free2dMatrix(grid, n+1);
    free2dMatrix(new, n+1);
    return 0;
}
