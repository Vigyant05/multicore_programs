#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define T 4

int queues[T][10]={{1,2,3,4,5,6,7},{8},{9},{10}};
int size[T]={7,1,1,1};
pthread_mutex_t locks[T]={
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER
};
int pop_task(int q){
    pthread_mutex_lock(&locks[q]);
    int task= (size[q]>0) ? queues[q][--size[q]]: -1;
    pthread_mutex_unlock(&locks[q]);
    return task;
}
void* worker(void* arg){
    int id=*(int*) arg;
    while(1){
        int task=pop_task(id);
        for(int i=0; task==-1 && i<T;i++){
            if((task==pop_task(i)) != -1)
                printf("Thread %d stole task %d from Thread %d\n",id,task,i);
        }
        if(task==-1) break;
        printf("Thread %d processing task %d\n", id, task);
        sleep(1);
    }
    return NULL;
}
int main(){
    pthread_t th[T];
    int ids[T]={0,1,2,3};

    for(int i=0;i<T;i++) pthread_create(&th[i], NULL, worker, &ids[i]);
    for(int i=0;i<T;i++) pthread_join(th[i],NULL);

    printf("All tasks completed\n");
    return 0;
}