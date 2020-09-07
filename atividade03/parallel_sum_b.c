// Correção: OK. 1,0 ponto pela imprecisão nos valores grandes.
#include <stdio.h>
#include <omp.h>

int main (int argc , char *argv[]) {
    int max, chunk; 
    sscanf (argv[1], "%d", &max);
    sscanf (argv[2], "%d", &chunk);
    int ts = omp_get_max_threads();
    int rest = max % ts;
    int sums[ts];


    #pragma omp parallel
    {
        int t = omp_get_thread_num();

        int partial_sum = 0;
        for(int i = 0; i < chunk; i++){
            int lo = (ts * i * chunk) + (t*chunk) + 1;
            int hi = lo + chunk - 1;
            if (lo > max) break;
            else if (hi > max) hi = max;

            for(int j = lo; j <= hi; j++)
                partial_sum = partial_sum + j;
            
           printf("%d: %d -> %d (%d) \n", t, lo, hi, hi - lo);
           printf("partial: %d\n", partial_sum);

        }
        sums[t] = partial_sum;
    }
   
    int sum = 0;
    for (int t = 0; t < ts; t++) sum = sum + sums[t];
    printf ("%d\n", sum);
    return 0;
}
