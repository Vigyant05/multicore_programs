#include<stdio.h>
#include<pthread.h>

#define N 3
int A[N][N]={{1,2,3},{4,5,6},{7,8,9}}, B[N][N]={{9,8,7},{6,5,4},{3,2,1}};
int C[N][N];

void* add(void* arg){
    int i=*(int*) arg;
    for(int j=0;j<N;j++) C[i][j]= A[i][j]+B[i][j];
    return NULL;
}
int main(){
    pthread_t t[N];
    int row[N]={0,1,2};
    
    for(int i=0;i<N;i++) pthread_create(&t[i], NULL, add, &row[i]);
    for(int i=0;i<N;i++) pthread_join(t[i],NULL);

    printf("Resultant Matrix: \n");
    for(int i=0;i<N;i++){
        printf("%d %d %d\n", C[i][0],C[i][1],C[i][2]);
    }
    return 0;
}