#include<stdio.h>
#include<pthread.h>

int arr[]= {1,2,3,4,5,6,7,8};

void* sum_half(void* arg){
    int start= *(int*)arg, sum=0;
    for(int i=start;i<start+4;i++){
        sum+=arr[i];
    }
    *(int*) arg=sum;
    return NULL;
}
int main(){
    pthread_t t[2];
    int data[2]={0,4};
    for(int i=0;i<2;i++) pthread_create(&t[i], NULL, sum_half, &data[i]);
    for(int i=0;i<2;i++) pthread_join(t[i],NULL);

    printf("Total Sum: %d\n", data[0]+data[1]);
    return 0;
}