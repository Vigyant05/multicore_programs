#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define SIZE 5
#define N 10

int buffer[SIZE];
int in=0,out=0,count=0;

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full= PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty= PTHREAD_COND_INITIALIZER;

void* producer(void* arg){
    for(int task=1;task<=N;task++){
        pthread_mutex_lock(&mutex);
        while(count==SIZE){
            printf("Producer: Buffer full, waiting...\n");
            pthread_cond_wait(&not_full,&mutex);
        }
        buffer[in]=task;
        in=(in+1)%SIZE;
        count++;
        printf("Producer: Produced task %d\n", task);

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}
void* consumer(void* arg){
    for(int task=1;task<=N;task++){
        pthread_mutex_lock(&mutex);
        while(count==0){
            printf("Consumer: Buffer empty, waiting...\n");
            pthread_cond_wait(&not_empty,&mutex);
        }
        int task= buffer[out];
        out=(out+1)%SIZE;
        count--;
        printf("Consumer: Consumed task %d\n", task);

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    return NULL;
}
int main(){
    pthread_t prod,cons;
    pthread_create(&prod,NULL, producer,NULL);
    pthread_create(&cons,NULL, consumer,NULL);

    pthread_join(prod,NULL);
    pthread_join(cons,NULL);

    printf("\nAll Tasks Completed\n");
    return 0;
}