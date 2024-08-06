#include "rbtree.h"
#include "rbtree.c"
#include "stdio.h"

void test_find_single(rbtree *t, const key_t key) {
  node_t *q = rbtree_find(t, key);
  if (q != NULL){
    printf("GOOOOOOOOD\n");
  }else{
    printf("BBBBAAAADDDD\n");
  }
}

void test_insert_single(rbtree *t, const key_t key) {
  
  node_t *p = rbtree_insert(t, key);
}


int main(){
    rbtree *t = new_rbtree();
    test_insert_single(t,20);
    test_insert_single(t,20+1);
    test_insert_single(t, 20+2);
    test_insert_single(t, 1);
    print_tree(t, t->root); 
    test_find_single(t,1);
    printf("SUCCESS SUCCESS SUCCESS SUCCESS SUCCESS SUCCESS SUCCESS");
}
