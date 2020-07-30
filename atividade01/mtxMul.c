#include <omp.h>

double ** mtxMul(double ** c, double ** a, double ** b, int n){
	// For serial version comment all '#pragma' lines 
	// For parallel for with no collapse comment with '//' before 'colapse(2)'
	// For parallel for with 2 collapse use as it is
	#pragma omp parallel for collapse(2)
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			c[i][j] == 0.0;
			for(int k = 0; k < n; k++)
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
		}
	return c;
}
