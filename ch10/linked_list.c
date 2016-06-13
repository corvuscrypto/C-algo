#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
  Node *next;
  Node *prev;
  int value;
};

Node *newNode(int val){
  Node *ret = calloc(1, sizeof(Node));
  ret->next = NULL;
  ret->prev = NULL;
  ret->value = val;
  return ret;
}

typedef struct List List;
struct List {
  Node *head;
  Node *tail;
  int length;
};

List *newList(){
  List *ret = calloc(1, sizeof(List));
  ret->head = NULL;
  ret->tail = NULL;
  return ret;
}

void append(List *L, int val){
  //make a new node with value 'val'
  Node *n = newNode(val);
  //If the list is empty, then set node as both head and tail
  if (!L->tail){
    L->tail = n;
    L->head = n;
    L->length = 1;
    return;
  }
  //append it to the tail, always
  //first get the tail node
  Node *tail = L->tail;
  //set the tail node's next attribute to the new node and the new node's prev as the tail node
  n->prev = tail;
  tail->next = n;

  //set the new tail on the list
  L->tail = n;
  //increase length
  L->length++;
}

Node *search(List *L, int val){
  //if list is empty return
  if (!L->head) return NULL;

  //start at the head
  Node *x = L->head;
  while(x->value != val){
    x = x->next;
    if (!x) break;
  }
  return x;
}

void destroy(List *L){
  Node *x = L->head;
  while(x!=NULL){
    Node *t = x->next;
    free(x);
    x = t;
  }
  free(L);
}

void delete(List *L, int val){
  Node *toDelete = search(L, val);
  if (!toDelete) {
    puts("couldn't find any node to delete!");
    return;
  }
  //splice it out
  toDelete->next->prev = toDelete->prev;
  toDelete->prev->next = toDelete->next;
  //if the next node was Nil, set the new tail
  if (!toDelete->next) {
    L->tail = toDelete->prev;
  }
  //if the prev node was Nil, set the new head
  if (!toDelete->prev) {
    L->head = toDelete->next;
  }
  //free the node (be freeeeee)
  free(toDelete);
  //decrease L length
  L->length--;
}

int main(){
  //create a List
  List *L = newList();
  //append some nodes
  append(L, 1);
  append(L, 2);
  append(L, 3);
  //delete the middle node
  delete(L, 2);
  //test to ensure no node 2 exists
  if (search(L, 2)){
    puts("No node with value 2 exists!");
  }
  //try to delete a value of 2 again
  delete(L, 2);
  //print length of List
  printf("list length: %d\n", L->length);

  //do proper destroy
  destroy(L);
}
