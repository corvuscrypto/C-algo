#include <stdlib.h>
#include <stdio.h>

void countingSort(int *A, int sizeA, int *B, int k){
  int i;
  int *c = calloc(k+1, sizeof(int));
  for (i=0; i < sizeA; ++i){
    ++c[A[i]];
  }
  for (i=1; i < k+1; ++i){
    c[i] += c[i-1];
  }
  c[0] = 1;
  for (i = sizeA-1; i >= 0; --i){
    int num = A[i];
    //handle duplicates by shifting them
    int j = c[num];
    while(B[j] == num && j > 0){
      --j;
    }
    B[j] = num;
  }

}

int getK(int *arr, int size){
  int i, largest;
  largest = 0;
  for (i=0; i < size; ++i){
    if (arr[i] > largest){
      largest = arr[i];
    }
  }
  return largest;
}

void printArray(int *arr, int size){
  int i;
  for (i=0; i < size; ++i){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main(){
  int data[] = {1,0,0,34,34,2,1,3,4,5,34,0,2,0,0,0,0};
  int size = sizeof(data)/sizeof(int);
  int *nArray = calloc(size, sizeof(int));
  printArray(data, size);
  countingSort(data, size, nArray, getK(data, size));
  printArray(nArray, size);
  return 0;
}
