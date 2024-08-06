#include "rbtree.h"
#include "rbtree.c"
#include "stdio.h"

void test_insert_single(const key_t key) {
  rbtree *t = new_rbtree();
  node_t *p = rbtree_insert(t, key);
  node_t *z = rbtree_insert(t, key+1);
  node_t *x = rbtree_insert(t, key+2);
  printf("%d\n", t->root->key);
  printf("%d\n", t->root->left->key);
  printf("%d\n", t->root->right->key);

  delete_rbtree(t);
}

int main(){
    test_insert_single(20);
    printf("SUCCESS");
}
