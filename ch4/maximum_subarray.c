#include <stdio.h>
#include <stdlib.h>

struct SubarrayTuple {
  int maxLeft;
  int maxRight;
  int sum;
};

struct SubarrayTuple *tuple(int a, int b, int c){
  struct SubarrayTuple *ret = calloc(1, sizeof(struct SubarrayTuple));
  ret->maxLeft = a;
  ret->maxRight = b;
  ret->sum = c;
}

struct SubarrayTuple *findMaxCross(int *arr, int l, int m, int h){
  int maxRight,maxLeft;

  //really low number
  int leftSum = -10000000;
  int rightSum = -10000000;

  int sum = 0;

  int i;
  for(i=m;i>=l; --i){
    sum = sum+arr[i];
    if (sum > leftSum){
      leftSum = sum;
      maxLeft = i;
    }
  }
  sum = 0;
  for (i=m+1;i<=h;++i){
    sum = sum+arr[i];
    if (sum > rightSum){
      rightSum = sum;
      maxRight = i;
    }
  }
  return tuple(maxLeft, maxRight, leftSum+rightSum);
}

struct SubarrayTuple *findMaxSub(int *arr, int l, int h){
  if (h == l){
    return tuple(l, h, arr[l]);
  }
  //get mid point
  int m = (l+h)/2;
  struct SubarrayTuple *left = findMaxSub(arr, l, m);
  struct SubarrayTuple *right = findMaxSub(arr, m+1, h);
  struct SubarrayTuple *cross = findMaxCross(arr, l, m, h);

  if (left->sum >= right->sum && left->sum >= cross->sum){
    return left;
  } else if (right->sum >= left->sum && right->sum >= cross->sum){
    return right;
  }
  return cross;
}

int main(){
  // test array
  int changes[] = {-13,-3,-25, -20, -3};
  struct SubarrayTuple *max = findMaxSub(changes, 0, (sizeof(changes)/sizeof(int))-1);
  printf("l index: %d, r index: %d, sum: %d\n", max->maxLeft+1, max->maxRight+1, max->sum);
  return 0;
}
