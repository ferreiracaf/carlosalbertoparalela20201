__kernel void leibdnizPi(__global float* c, int iNumElements) {
	
	// Achar o índice global
	int iGID = get_global_id(0);

	if (iGID < iNumElements) {
		c[iGID] = (float) 4 * (iGID%2 == 0 ? 1 : -1)/(2*iGID+1);
	}
}