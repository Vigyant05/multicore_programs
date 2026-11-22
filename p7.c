#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define MAX 10
int bread=0;
pthread_mutex_t lock= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond= PTHREAD_COND_INITIALIZER;

void* producer(void* arg){
    while(1){
        pthread_mutex_lock(&lock);
        while(bread>=MAX) pthread_cond_wait(&cond, &lock);
        printf("Produced Bread. Total: %d\n",++bread);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}
void* consumer(void* arg){
    while(1){
        pthread_mutex_lock(&lock);
        while(bread<=0) pthread_cond_wait(&cond, &lock);
        printf("Consumed Bread. Remaining: %d\n",--bread);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}
int main(){
    pthread_t prod,cons;

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod,NULL);
    pthread_join(cons,NULL);

    return 0;
}
