#include <stdio.h>
#include <stdlib.h>

#define PARTITION_SIZE 40

typedef struct node node;
struct node {
  node *parent;
  node *left;
  node *right;
  int value;
};

node *Node(int val){
  node *ret = calloc(1, sizeof(node));
  ret->value=val;
  return ret;
}

typedef struct queue queue;
struct queue {
  int size;
  int topIndex;
  int nextIndex;
  int num;
  node **_data;
};

//Queue for BFS
queue *Queue(){
  queue* ret = calloc(1, sizeof(queue));
  ret->size = PARTITION_SIZE;
  ret->nextIndex = -1;
  ret->_data = calloc(PARTITION_SIZE, sizeof(node *));
}

void enqueue(queue *q, node *x){
  //circular queue implementation with limit
  if (q->topIndex == q->nextIndex && q->num) return;
  if (q->nextIndex < 0) q->nextIndex = 0;
  q->_data[q->topIndex] = x;
  q->topIndex++;

  if (q->topIndex >= q->size){
    q->topIndex = 0;
  }
  q->num++;
}

node *dequeue(queue *q){
  node *ret = q->_data[q->nextIndex];
  q->nextIndex++;
  if (q->nextIndex >= q->size){
    q->nextIndex = 0;
  }
  q->num--;
  return ret;
}

typedef struct tree tree;
struct tree {
  node *root;
};

tree *Tree(int rootVal){
  node *root = Node(rootVal);
  tree *ret = calloc(1, sizeof(tree));
  ret->root = root;
  return ret;
}

//balancing insert
_Bool _insert(node *n, node *newNode, queue *q){
  if (!n) {
    puts("shit it's null");
    return 1;
  }
  if (!n->left){
    n->left = newNode;
    return 1;
  } else if (!n->right){
    n->right = newNode;
    return 1;
  }
  enqueue(q, n->left);
  enqueue(q, n->right);
  return 0;
}

void insert(tree *t, int value){
  //make a queue
  queue *q = Queue();
  node *n = Node(value);
  enqueue(q, t->root);
  while(!_insert(dequeue(q), n, q));
  free(q);
}

node *_search(node *n, int val){
  if(!n) return NULL;
  if (n->value == val) return n;
  node *left = _search(n->left, val);
  if(left->value == val) return left;
  node *right = _search(n->right, val);
  if(right->value == val) return right;
  return NULL;
}

node *search(tree *t, int val){
  //do depth first search
  return _search(t->root, val);
}

void _print(node *n, const char *qualifier){
  if(!n) return;
  printf("%s:%d,", qualifier, n->value);
  _print(n->left, "left");
  _print(n->right, "right");
}

//depth first print
void printTree(tree *t){
  _print(t->root, "root");
  puts(";");
}

int main(){
  //make the tree and insert some node
  tree *T = Tree(5);
  insert(T, 2);
  insert(T, 6);
  insert(T, 8);
  puts("done");
  insert(T, 1);
  insert(T, 3);
  //print it out
  printTree(T);
}
