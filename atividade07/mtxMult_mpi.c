#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

/*
 *
 * Estava tentando usar o chunk sendo a quantidade de elementos correspondentes a uma linha
 * da matriz, pois a partir da transposta já calculada, poderia fazer as operações sem me
 * preocupar tanto com os, entretando acabei me atrapalhando com as funções. A ideia era passar
 * com o scatter os chunks de a e b para serem computador e após isso recuperar o valor no 
 * vetor c com um reduce com a operação de soma que me daria o valor de um elemento da matriz
 * resultante. Infelizmente das formas que acabei colocando não obtive o resultado esperado a tempo.  
 * 
*/

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

    int rank, size;
    int root = 0;

    double *a, *b, *c;
    double *a_out, *b_out, *c_out;
    double valor, soma_total;

    double start, finish;
    start = MPI_Wtime();

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int partial = (tam*tam)/size;
    
    if (rank == root){
        a = (double *) malloc((tam * tam) * sizeof(double));
        b = (double *) malloc((tam * tam) * sizeof(double));
        c = (double *) malloc((tam * tam) * sizeof(double));
        for (int i = 0; i < (tam * tam); i++)
        {
            a[i] = 1.0;
            b[i] = 1.0;
            c[i] = 0.0;
        }
        for (int i = 0; i < tam; i++)
            for (int j = 0; j < tam; j++)
                b[((tam*i)+j)] = a[((tam*j)+i)];
        
    }

    a_out = (double *) malloc(size * sizeof(double));
    b_out = (double *) malloc(size * sizeof(double));
    c_out = (double *) malloc(size * sizeof(double));
    
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            MPI_Scatter(a, size, MPI_DOUBLE, a_out, size, MPI_DOUBLE, root, MPI_COMM_WORLD);
            MPI_Scatter(b, size, MPI_DOUBLE, b_out, size, MPI_DOUBLE, root, MPI_COMM_WORLD);
            valor = 0.0;
            for (int k = 0; k < size; k++){
                c_out[k] = a_out[k] * b_out[k]; 
                valor = valor + c_out[k];
            }
            MPI_Reduce(&valor, &soma_total, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);
            if (rank == root) {printf("%f ", soma_total);}
            
        }
    }
    







    
    
    
    // c = mtxMul(c, a, b, tam);

    // printMatrix(c, tam);
    MPI_Finalize();
    return 0;
}