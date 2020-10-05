// Nota 0,5
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
                
int main(int argc, char *argv[]) {
    int rank, size, n;
    int root = 0;
    double resultado;
    double *vect_a_root, *vect_b_root, *vect_c_root;

    double start, finish;
    start = MPI_Wtime();

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == root){
        double a = atof(argv[1]);
        double b = atof(argv[2]);
        n = atoi(argv[3]);
        vect_a_root = (double *) malloc(n * sizeof(double));
        vect_b_root = (double *) malloc(n * sizeof(double));
        vect_c_root = (double *) malloc(n * sizeof(double));
        for (int i = 0; i < n; i++){
            vect_a_root[i] = a;
            vect_b_root[i] = b;
        }
    }
    
    MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);

    int partial = n/size;

    double *vect_a = (double *) malloc(partial * sizeof(double));
    double *vect_b = (double *) malloc(partial * sizeof(double));
    double *vect_c = (double *) malloc(partial * sizeof(double));

    MPI_Scatter(vect_a_root, partial, MPI_DOUBLE, vect_a, partial, MPI_DOUBLE, root, MPI_COMM_WORLD);
    MPI_Scatter(vect_b_root, partial, MPI_DOUBLE, vect_b, partial, MPI_DOUBLE, root, MPI_COMM_WORLD);

    for (int i = 0; i < partial; i++){
        vect_c[i] = vect_a[i] * vect_b[i];
    }

    MPI_Gather(vect_c, partial, MPI_DOUBLE, vect_c_root, partial, MPI_DOUBLE, root, MPI_COMM_WORLD);

    finish = MPI_Wtime();
    
    if(rank == root){
        printf("Produto escalar no processo root %d: \n", rank);
        for (int i = 0; i < n; i++) {
            resultado += vect_c_root[i];
        }
        printf("Resultado: %.2f\n", resultado);
        printf("Tempo gasto: %f\n", finish - start);
        free(vect_a_root);
        free(vect_b_root);
        free(vect_c_root);
    }
    free(vect_a);
    free(vect_b);
    free(vect_c);

    MPI_Finalize();
    return 0;
}
