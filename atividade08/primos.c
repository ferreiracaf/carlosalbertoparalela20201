#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int primo (int n) {
    int resultado = 0;
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
        resultado++;
        break;
        }
    }
 return resultado;
}
                
int main(int argc, char *argv[]) {
    int rank, size, n;
    int root = 0;
    int max = 1000;
    double start, finish;
    start = MPI_Wtime();
    int count = 100;
    int chunk[count];
    int target = 1;
    int tag = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == root){
        for (int i = 0; i < max; i++){
            chunk[i % (count-1)] = i;
            if (i % (count-1) == 0){
                MPI_Request request;
                MPI_Issend(chunk, count, MPI_INT, target, tag, MPI_COMM_WORLD, &request);
                target = target + 1;
                if(target >= size) target = 1;
                tag++;
            }
        }

    }
    else {
        MPI_Status status;
        MPI_Recv(chunk, count, MPI_INT, root, tag, MPI_COMM_WORLD, &status);
        for (int i = 0; i < count; i++){
            printf("%d ", chunk[i]);
        }
        printf("\n");
    }
    

    

    MPI_Finalize();
    return 0;
}