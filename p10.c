#define _POSIX_C_SOURCE 200809L
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include<errno.h>

pthread_mutex_t lock1= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2= PTHREAD_MUTEX_INITIALIZER;

void* worker(void* arg){
    int id= *(int*)arg;

    pthread_mutex_t* first=(id==0)? &lock1: &lock2;
    pthread_mutex_t* second= (id==0)? &lock2: &lock1;
    int first_num=id+1,second_num=2-id;
    pthread_mutex_lock(first);
    sleep(1);
    printf("Thread %d, Waiting for lock %d...\n",id,second_num);
    
    struct timespec deadline;
    clock_gettime(CLOCK_REALTIME, &deadline);
    deadline.tv_sec+=2;

    if(pthread_mutex_timedlock(second, &deadline) ==0){
        printf("Thread %d: Acquired lock %d\n",id,second_num);
        pthread_mutex_unlock(second);
    }else{
        printf("Thread %d: Timeout! Releasing lock %d\n", id,first_num);
    }
    pthread_mutex_unlock(first);
}

int main(){
    pthread_t th[2];
    int ids[2]={0,1};
    for(int i=0;i<2;i++) pthread_create(&th[i], NULL, worker, &ids[i]);
    for(int i=0;i<2;i++) pthread_join(th[i],NULL);

    return 0;
}

/*
(base) vigyantnayak@Vigyants-MacBook-Air multicore_programs % gcc p10.c -pthread -include <(echo '
#include <pthread.h>
#include <time.h>
static int pthread_mutex_timedlock(pthread_mutex_t *m, const struct timespec *t) {
    struct timespec now, s = {0, 10000000};
    while (pthread_mutex_trylock(m) != 0) {
        clock_gettime(CLOCK_REALTIME, &now);
        if (now.tv_sec > t->tv_sec || (now.tv_sec == t->tv_sec && now.tv_nsec >= t->tv_nsec)) return 1;
        nanosleep(&s, NULL);
    }
    return 0;
}') -o p10 && ./p10
*/