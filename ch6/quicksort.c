#include <stdlib.h>
#include <stdio.h>

int partition(int *arr, int a, int b){
  int tempI;
  int x = arr[b];
  int i = a-1;
  int j = a;
  for (j; j < b; ++j){
    if (arr[j] <= x){
      ++i;
      tempI = arr[i];
      arr[i] = arr[j];
      arr[j] = tempI;
    }
  }
  tempI = arr[i+1];
  arr[i+1] = arr[b];
  arr[b] = tempI;
  return i+1;
}

void quicksort(int *arr, int a, int b){
  if (a >= b) {
    return;
  }
  int q = partition(arr, a, b);
  quicksort(arr, a, q-1);
  quicksort(arr, q+1, b);
}

void printArray(int *arr, int size){
  int i;
  for (i=0; i < size; ++i){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main(){
  int data[] = {1,4,5,1,2,4,5,6,7,4,3,2,1,2,3,4,5};
  int size = sizeof(data)/sizeof(int);
  printArray(data, size);
  quicksort(data, 0, size-1);
  printArray(data, size);
}
