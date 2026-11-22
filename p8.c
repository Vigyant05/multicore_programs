#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define SIZE 1000000
int arr[SIZE];

int main(){
    for(int i=0;i<SIZE;i++) arr[i]= rand()%100;

    int seq_sum=0;
    double start=omp_get_wtime();
    for(int i=0;i<SIZE;i++) seq_sum+= arr[i];
    double seq_time= omp_get_wtime()-start;

    int par_sum=0;
    start= omp_get_wtime();
    for(int i=0;i<SIZE;i++) par_sum+= arr[i];
    double par_time= omp_get_wtime()-start;

    printf("Sequential -> Sum: %d | Time: %f s\n",seq_sum,seq_time);
    printf("Parallel -> Sum: %d | Time: %f s\n", par_sum,par_time);

    #pragma omp parallel
    printf("Hello from thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());

    printf("\n Result: %s\n", (seq_sum==par_sum) ? "Both sums are equal" : "Both sums are different");
    return 0;
}

//gcc -fopenmp p8.c -o p8 && ./p8

//gcc-14 -fopenmp -mmacosx-version-min=15.0 p8.c -o p8 && ./p8