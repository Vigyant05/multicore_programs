#include<stdio.h>
#include<pthread.h>

#define N 100
#define T 4

int data[N], target,found=-1;
pthread_mutex_t lock= PTHREAD_MUTEX_INITIALIZER;

void* search(void* arg){
    int id= *(int*) arg;
    int start= id*(N/T), end= start+(N/T);
    printf("Thread %d searching from index %d to %d \n", id, start, end-1);

    for(int i=start;i<end;i++){
        if(data[i]==target){
            pthread_mutex_lock(&lock);
            if(found==-1) found=i;
            pthread_mutex_unlock(&lock);
            break;
        }
    }
    return NULL;
}
int main(){
    pthread_t th[T];
    int ids[T]={0,1,2,3};

    for(int i=0;i<N;i++) data[i]=i+1;
    printf("Enter the number to search (1-100): ");
    scanf("%d", &target);

    for(int i=0;i<T;i++) pthread_create(&th[i],NULL,search, &ids[i]);
    for(int i=0;i<T;i++) pthread_join(th[i],NULL);

    if(found!=-1) printf("\nNumber %d found at index: %d\n", target, found);
    else printf("Number %d not found", target);

    return 0;
}