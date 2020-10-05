// Nota 0,3
// Você não precisava substituir o All_to_all, apenas mudar os parâmetros e algumas variáveis.
// Cálculo das Médias
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/*
 * 
 *  Tentei implementar o All_to_all usano o Gather para recuperar os valores
 *  entretanto mesmo para um elemento, acontecia algum bug que eu não consigo explicar
 *  o porque, mas o primeiro "output_array" ficava com os valores certos, entretanto os 
 *  seguintes ficavam pegando um valor de lixo a mais de acordo com o rank e, como não
 *  consegui resolver, acabei não implemenando por completo essa questão. 
 * 
*/
                
int main(int argc, char *argv[]) {
    int i, rank, size;
    int *input_array, *output_array;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    input_array = (int *) malloc(size * sizeof(int));
    output_array = (int *) malloc((size * 2) * sizeof(int));

    for (i = 0; i < size; i++)
        input_array[i] = rank * size + i;

    // printf("Input for process %d\n", rank);
    // for (i = 0; i < size; i++)
    //     printf("%d ", input_array[i]);
    // printf("\n");

    MPI_Alltoall(input_array, 1, MPI_INT, output_array, 1, MPI_INT, MPI_COMM_WORLD);

    // for (int i = 0; i < size; i++){
    //     MPI_Gather(&input_array[i], 1, MPI_INT, &output_array[i], 1, MPI_INT, i, MPI_COMM_WORLD);
    // }
    // printf("%d\n", input_array[2]);
    // MPI_Gather(&input_array[0], 1, MPI_INT, &output_array[0], 1, MPI_INT, 0, MPI_COMM_WORLD);
    // MPI_Gather(&input_array[1], 1, MPI_INT, &output_array[1], 1, MPI_INT, 1, MPI_COMM_WORLD);
    // MPI_Gather(&input_array[2], 1, MPI_INT, &output_array[2], 1, MPI_INT, 2, MPI_COMM_WORLD);

    // printf("\t\t-> %d, %d, %d\nOutput for process %d\n", input_array[0], input_array[1], input_array[2], rank);
    printf("Output for process %d\n", rank);
    for (i = 0; i < size; i++)
        printf("%d ", output_array[i]);
    printf("\n");

    MPI_Barrier(MPI_COMM_WORLD);

    free(input_array);
    free(output_array);
    MPI_Finalize();
    return 0;
}
