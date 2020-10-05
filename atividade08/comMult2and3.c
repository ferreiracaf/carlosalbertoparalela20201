// Nota 0,8. Acho que a divisão está correta, mas a saída no terminal está confusa
#include <stdio.h>
#include <mpi.h>

int main(int argc,char* argv[]){
    int numtasks, rank, len, rc;
    int rank_comm_2, rank_comm_3, rank_comm_2_3, size_comm_2, size_comm_3, size_comm_2_3;

    MPI_Init(&argc,&argv); 
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    MPI_Comm mult2_comm;
    MPI_Comm mult3_comm;
    MPI_Comm mult2_3_comm;

    MPI_Comm_split(MPI_COMM_WORLD, rank % 2, 0, &mult2_comm);
    MPI_Comm_split(MPI_COMM_WORLD, rank % 3, 0, &mult3_comm);
    MPI_Comm_split(MPI_COMM_WORLD, rank % 6, 0, &mult2_3_comm);

    MPI_Comm_size(mult2_comm, &size_comm_2);
    MPI_Comm_rank(mult2_comm, &rank_comm_2);

    printf("comm_2 : %d \n", rank_comm_2);

    MPI_Comm_size(mult3_comm, &size_comm_3);
    MPI_Comm_rank(mult3_comm, &rank_comm_3);

    printf("comm_3 : %d \n", rank_comm_3);
    
    MPI_Comm_size(mult2_3_comm, &size_comm_2_3);
    MPI_Comm_rank(mult2_3_comm, &rank_comm_2_3);

    printf("comm_2_3 : %d \n", rank_comm_2_3);
    printf("\n");

    MPI_Comm_free(&mult2_comm);
    MPI_Comm_free(&mult3_comm);
    MPI_Comm_free(&mult2_3_comm);

    MPI_Finalize();
    return 0;
}
