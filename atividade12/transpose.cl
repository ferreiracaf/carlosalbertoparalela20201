__kernel void transpose(__global float* matrixA, __global float* matrixC, int N) {
	
	// Achar os índices globais
	int xGID = get_global_id(0); // coluna  
	int yGID = get_global_id(1); // linha 

    matrixC[yGID*N + xGID] = matrixA[xGID*N + yGID];
    
}