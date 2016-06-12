#include <stdio.h>

void swap(int* arr, int a, int b){
  int temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

int quicksortPartition(int* arr, int a, int b){
  int x = arr[b];
  int i = a-1;
  int j = a;
  for (j; j < b; ++j){
    if (arr[j] <= x){
      ++i;
      swap(arr, i, j);
    }
  }
  swap(arr, i+1, b);
  return i+1;
}

void quicksort(int* arr, int a, int b) {
  if (a<b){
    int j = quicksortPartition(arr, a, b);
    quicksort(arr, a, j-1);
    quicksort(arr, j+1, b);
  }
}

int select(int* arr, int a, int b, int i) {
  if (a == b) return arr[a];
  int j = quicksortPartition(arr, a, b);
  // printf("%d\n", i);
  int k = j-a+1;

  if (i == k) return arr[j];

  if (i < k){
    return select(arr, a, j-1, i);
  }
  return select(arr, j+1, b, i-k);
}

int selectNLowest(int* arr, size_t size, int i){
  return select(arr, 0, size-1, i);
}


void printArray(int *arr, int size){
  int i;
  for (i=0; i < size; ++i){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main(){
  int data[] = {1,5,6,3,2};
  size_t size = sizeof(data)/sizeof(int);

  //select the 2nd lowest (2)
  printf("%d\n", selectNLowest(data, size, 2));
  //select the 4th lowest(5)
  printf("%d\n", selectNLowest(data, size, 4));

}
