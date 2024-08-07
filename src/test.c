#include "rbtree.h"
#include "rbtree.c"
#include "stdio.h"
#include <assert.h>

#define SENTINEL


void test_insert_single(rbtree* t, const key_t key) {
  
  node_t *p = rbtree_insert(t, key);
  }

int main(){
  rbtree *t = new_rbtree();
  test_insert_single(t,5);
  test_insert_single(t,3);
  test_insert_single(t,7);
  test_insert_single(t,8);
  test_insert_single(t,10);
  print_tree(t,t->root);
  printf("SUCCESS SUCCESS SUCCESS SUCCESS SUCCESS SUCCESS SUCCESS");
  delete_rbtree(t);
}
