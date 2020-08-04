#include <stdio.h>
#include <omp.h>

int main (int argc , char *argv[]) {
    int max; 
    sscanf (argv[1], "%d", &max);
    int ts = omp_get_max_threads ();
    int rest = max % ts;
    int sums[ts];
    if (rest != 0){
        
        #pragma omp parallel
        {
            int t = omp_get_thread_num();
            int lo, hi;
            if (t >= rest){
                lo = (max / ts) * (t + 0) + 1 + rest;
                hi = (max / ts) * (t + 1) + rest;
            }
            else {
                lo = (max / ts) * (t + 0) + (t + 1);
                hi = (max / ts) * (t + 1) + (t + 1);
            }
            sums[t] = 0;
            // printf("%d: %d -> %d\n", t, lo, hi);
            for (int i = lo; i <= hi; i++)
                sums[t] = sums[t] + i;
        }
    }
    else {
        
        #pragma omp parallel
        {
            int t = omp_get_thread_num();
            int lo , hi;
            if (t >= rest){
                lo = (max / ts) * (t + 0) + 1;
                hi = (max / ts) * (t + 1) + 0;
            }
            sums[t] = 0;
            // printf("%d: %d -> %d\n", t, lo, hi);
            for (int i = lo; i <= hi; i++)
                sums[t] = sums[t] + i;
        }
    }
    int sum = 0;
    for (int t = 0; t < ts; t++) sum = sum + sums[t];
    printf ("%d\n", sum);
    return 0;
}