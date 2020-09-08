#include <stdio.h>
#include <stdlib.h>

double * mtxMul(double * c, double * a, double * b, int n){
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			c[((n*i)+j)] == 0.0;
			for(int k = 0; k < n; k++)
				c[((n*i)+j)] = c[((n*i)+j)] + a[((n*i)+k)] * b[((n*k)+j)];
		}
	return c;
}

void printMatrix(double * mat, int num){
    printf("Matriz:\n");
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            printf("%.1f, ", mat[((num*i)+j)]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]){

    int tam = atoi(argv[1]);

    double * a = (double *) malloc((tam * tam) * sizeof(double));
    double * b = (double *) malloc((tam * tam) * sizeof(double));
    double * c = (double *) malloc((tam * tam) * sizeof(double));
    
    
    for (int i = 0; i < (tam * tam); i++)
    {
        a[i] = 1.0;
        b[i] = 1.0;
        c[i] = 0.0;
    }
    
    c = mtxMul(c, a, b, tam);

    // printMatrix(c, tam);

    return 0;
}