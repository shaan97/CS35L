#include <stdio.h>
#include <pthread.h>

#define ARRAY_SIZE 10000
#define NUM_THREADS 32
int sum[NUM_THREADS];
int arr[ARRAY_SIZE];

void* p_sum(void* id){
  int tid = (int) id;
  int start = (tid * ARRAY_SIZE) / NUM_THREADS;
  int end = ((tid + 1)*ARRAY_SIZE) / NUM_THREADS;
  sum[tid] = 0;
  for(; start < end; start++){
    sum[tid] += arr[start];
  }
  
  return NULL;

}
int main(){
  // Sum up the elements of an array in parallel
  pthread_t threads[NUM_THREADS];
  int i;
  for(i = 0; i < ARRAY_SIZE; i++)
    arr[i] = i;
  
  for(i = 0; i < NUM_THREADS; i++){
    pthread_create(&threads[i], NULL, p_sum, (void*)i);
  }

  for(i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
  }
  int final_sum = 0;
  for(i = 0; i < NUM_THREADS; i++){
    final_sum += sum[i];
  }

  printf("Sum is %d\nWe expect %d\n", final_sum, ((unsigned long) (ARRAY_SIZE) - 1)* ((unsigned long)(ARRAY_SIZE)) / 2);
  return 0;
}
