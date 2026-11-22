#include<stdio.h>
#include<omp.h>

void blur(){
    printf("Thread %d: Blurring the image..\n",omp_get_thread_num());
}
void sharpen(){
    printf("Thread %d: Sharpening the image..\n",omp_get_thread_num());
}
void contrast(){
    printf("Thread %d: Contrasting the image..\n",omp_get_thread_num());
}
void resize(){
    printf("Thread %d: Resizing the image..\n",omp_get_thread_num());
}

int main(){
    printf("OpenMP Task Parallelism- Image Processing\nNumber of Task: 4\n");
    double start= omp_get_wtime();

    #pragma omp parallel
    #pragma omp single
    {
        printf("Tasks are being created by Thread %d\n\n", omp_get_thread_num());

        #pragma omp task
        blur();

        #pragma omp task
        sharpen();

        #pragma omp task
        contrast();

        #pragma omp task
        resize();

        #pragma omp taskwait
        printf("\nAll image processing tasks completed\n");
    }
    printf("Execution time: %f seconds\n", omp_get_wtime()-start);
    return 0;
}