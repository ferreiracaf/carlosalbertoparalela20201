// Nota 0,5
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include <unistd.h>
                        
#define MAX 100
                        
int main(int argc, char *argv[]) {

    int rank, size, total_num, tag = 0;
    int destination = 0, numbers[MAX];
                        
    MPI_Status status;
                         
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
                        
    if (rank == destination) {
        for (int i = 1; i < size; i++){
            MPI_Recv(numbers, MAX, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_INT, &total_num);
            printf("Process %d received %d numbers. Source = %d, tag = %d\n", destination, total_num, status.MPI_SOURCE, status.MPI_TAG);
        }
    } 
    else {
        // sleep(rank);
        srand(time(0));
        total_num = (rand() / (float) RAND_MAX) * MAX;
        printf("%d\n", total_num);
        MPI_Send(numbers, total_num, MPI_INT, destination, tag, MPI_COMM_WORLD);
        printf("Process %d sent %d numbers to 0\n", rank, total_num);
    }

    MPI_Finalize();                  
    return 0;
}
