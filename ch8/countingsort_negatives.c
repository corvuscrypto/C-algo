#include <stdlib.h>
#include <stdio.h>

void countingSort(int *A, int sizeA, int *B, int low, int high){
  int i, offset;
  if (low < 0){
    offset = -low;
  } else {
    offset = 0;
  }
  int *c = calloc(high-low+1, sizeof(int));
  for (i=0; i < sizeA; ++i){
    ++c[A[i]+offset];
  }
  for (i=1; i < high+offset+1; ++i){
    c[i] += c[i-1];
  }
  c[0] = 1;
  for (i = sizeA-1; i >= 0; --i){
    int num = A[i]+offset;
    //handle duplicates by shifting them
    int j = c[num]-1;
    while(B[j] == num-offset && j > 0){
      --j;
    }
    B[j] = num-offset;
  }

}

int getHighest(int *arr, int size){
  int i, largest;
  largest = 1<<((sizeof(int)*8)-1);
  for (i=0; i < size; ++i){
    if (arr[i] > largest){
      largest = arr[i];
    }
  }
  return largest;
}

int getLowest(int *arr, int size){
  int i, smallest;
  smallest = ~(1<<((sizeof(int)*8)-1)^1);
  for (i=0; i < size; ++i){
    if (arr[i] < smallest){
      smallest = arr[i];
    }
  }
  return smallest;
}

void printArray(int *arr, int size){
  int i;
  for (i=0; i < size; ++i){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main(){
  int data[] = {1,-1,-20,34,34,2,1,3,4,5,34,0,2,0,0,0,0};
  int size = sizeof(data)/sizeof(int);
  int *nArray = calloc(size, sizeof(int));
  printArray(data, size);
  countingSort(data, size, nArray, getLowest(data, size), getHighest(data, size));
  printArray(nArray, size);
  return 0;
}
