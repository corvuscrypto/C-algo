#include <stdlib.h>
#include <stdio.h>

int partition(int *arr, int a, int b){
  int tempI;
  int x = arr[a];
  int i = a-1;
  int j = b;
  while(1) {
    do --j; while (arr[j] > x);
    do ++i; while (arr[i] < x);
    if (i < j){
      tempI = arr[i];
      arr[i] = arr[j];
      arr[j] = tempI;
    } else {
      return j+1;
    }
  }
}

void quicksort(int *arr, int a, int b){
  if (b - a < 2) {
    return;
  }
  int q = partition(arr, a, b);
  quicksort(arr, a, q);
  quicksort(arr, q, b);
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
  quicksort(data, 0, size);
  printArray(data, size);
}
