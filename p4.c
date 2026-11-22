#include<stdio.h>
#include<pthread.h>

#define T 4
int balance=10000;
pthread_mutex_t lock= PTHREAD_MUTEX_INITIALIZER;

void* transaction(void* arg){
    int id= *(int*) arg, amt=1000;
    pthread_mutex_lock(&lock);
    printf("Thread %d started transaction. \n Thread%d: Balance before transaction= %d\n", id,id,balance);
    if(balance>=amt){
        balance-=amt;
        printf("Thread %d: Withdrawn= %d\n Thread %d: Balance after transaction= %d\n", id,amt,id,balance);
    }else{
        printf("Thread %d: Insufficient Balance\n\n",id);
    }

    pthread_mutex_unlock(&lock);
    return NULL;
}
int main(){
    pthread_t th[T];
    int ids[T]={1,2,3,4};

    printf("Initial Bank Balance= %d\n\n",balance);
    for(int i=0;i<T;i++) pthread_create(&th[i], NULL, transaction, &ids[i]);
    for(int i=0;i<T;i++) pthread_join(th[i],NULL);

    printf("Final Bank Balance= %d\n",balance);
    return 0;
}