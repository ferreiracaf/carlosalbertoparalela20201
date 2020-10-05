// Nota 1,2. Programa perigoso pela ausência de mallocs. Também poderia ter feito o
// processo 0 trabalhar. 
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

/*********************************************
 *
 *  De acordo com a minha implementação entende-se 
 *  como quantidade de núcleos a quantide de núcleos
 *  que avaliam a primalidade do número.
 *  Portanto, para a implementação e testes foram
 *  utilizaods os seguintes valores de np: 3, 5, 9;
 *  os quais representam as divisões feitas para
 *  computação de primelidade em 2, 4 e 8 núcleos. 
 *   
 ********************************************/
                
int main(int argc, char *argv[]) {
    int rank, size, n;
    int root = 0;
    int max = 1024000;
    int max_print = 1000000;
    // Este é o tamanho do chunk?	    
    int count = 128;
    // Isto aqui é instável em C. Tem que usar malloc.
    int chunk[count];
    int aux[count];
    int target = 1;
    int tag = 0;

    double start, finish;
    start = MPI_Wtime();

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == root){
	// malloc?    
        int total[max];
        for (int i = 1; i <= max; i++){
            int posicao = ((i % count) - 1) >= 0 ? ((i % count) - 1) : count - 1; 
            chunk[posicao] = i;
	    // Acho que esta condição tenta garantir que chunk já estará preenchido.
            if (i != 0 && i % (count) == 0){
                MPI_Request sendRequest, recvRequest;
                MPI_Status sendStatus, recvStatus;
		// chunk já todo preenchido? Acho que sim.
                MPI_Issend(chunk, count, MPI_INT, target, tag, MPI_COMM_WORLD, &sendRequest);
		// O processo 0 fica ocioso então...
                MPI_Irecv(aux, count, MPI_INT, target, MPI_ANY_TAG, MPI_COMM_WORLD, &recvRequest);
                MPI_Wait(&recvRequest, &recvStatus);
                for(int j = 0; j < count; j++){
                    total[j + (recvStatus.MPI_TAG * count)] = aux[j];
                }
                target = target + 1;
                if(target >= size) target = 1;
                tag++;
                MPI_Wait(&sendRequest, &sendStatus);
            }
        }
        int soma_primos = 0;
        printf("Primos:\n");
        for (int i = 0; i < max_print; i++) if (!total[i]){ printf("%d ", i+1); soma_primos++; }
        printf("\nSoma = %d\n", soma_primos); 
    }
    else {
        for (int j = 0; j < ((max/count)/(size-1)); j++){
            MPI_Request sendRequest, recvRequest;
            MPI_Status sendStatus, recvStatus;
            MPI_Irecv(chunk, count, MPI_INT, root, MPI_ANY_TAG, MPI_COMM_WORLD, &recvRequest);
            MPI_Wait(&recvRequest, &recvStatus);
            for (int i = 0; i < count; i++){
		// Aqui é como se o chunk estivesse preenchido com os números para analisar.    
                aux[i] = primo(chunk[i]);
            }
            MPI_Issend(aux, count, MPI_INT, root, recvStatus.MPI_TAG, MPI_COMM_WORLD, &sendRequest);
            MPI_Wait(&sendRequest, &sendStatus);
        }
    }
   
    MPI_Finalize();
    return 0;
}
