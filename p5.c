#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>

#define N 100
#define T 4
int arr[N], temp[N];

void merge(int l, int m, int r){
    int i=l,j=m+1,k=l;
    while(i<=m && j<=r){
        if(arr[i]<=arr[j]){
            temp[k]=arr[i];
            i++;
        }else{
            temp[k]=arr[j];
            j++;
        }
        k++;
    }
    while(i<=m){
        temp[k]=arr[i];
        i++;
        k++;
    }
    while(j<=r){
        temp[k]=arr[j];
        j++;
        k++;
    }
    for(int idx=l;idx<=r;idx++){
        arr[idx]=temp[idx];
    }
}
void merge_sort(int l, int r){
    if(l>=r) return;
    int mid= (l+r)/2;

    merge_sort(l,mid);
    merge_sort(mid+1,r);
    merge(l,mid,r);
}

void* worker(void* arg){
    int id= *(int*) arg;
    int chunk=N/T;
    int l=id*chunk, r=l+chunk-1;
    printf("Thread %d sorting elements %d to %d\n",id,l,r);
    merge_sort(l,r);
    return NULL;
}
void print_arr(const char* label){
    printf("%s:\n",label);
    for(int i=0;i<N;i++) printf("%d ", arr[i]);
    printf("\n\n");
}
int main(){
    pthread_t th[T];
    int ids[T]={0,1,2,3};
    for(int i=0;i<N;i++) arr[i]=rand()%1000;
    print_arr("Original Array");

    for(int i=0;i<T;i++) pthread_create(&th[i],NULL, worker, &ids[i]);
    for(int i=0;i<T;i++) pthread_join(th[i],NULL);

    merge(0,24,49);
    merge(50,74,99);
    merge(0,49,99);
    print_arr("Sorted Array");
    return 0;
}