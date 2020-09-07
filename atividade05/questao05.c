#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;    
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int destination, source;
    int msg = atoi(argv[1]);

    if (msg < 0){
        printf("A mensagem não pode ser negativa.\n");
        MPI_Finalize();
        return 0;
    }

    destination = (rank + 1) % size;
    source = (rank + size - 1) % size;

    if (rank == 0){
        if (msg > 0){
            MPI_Send(&msg, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);
        }
        while (msg > 0){
            MPI_Status status;
            MPI_Recv(&msg, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
            printf("%d - 1\n", msg);
            msg = msg - 1;
            MPI_Send(&msg, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);
        }
        printf("Final %d\n", msg);
    }
    else {
        while (msg > 0){
            MPI_Status status;
            MPI_Recv(&msg, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
            MPI_Send(&msg, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);
        }
        if (msg = 0){
            MPI_Status status;
            MPI_Recv(&msg, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
            MPI_Send(&msg, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}