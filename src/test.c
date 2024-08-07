#include "rbtree.h"
#include "rbtree.c"
#include "stdio.h"



void test_minmax_suite() {
  key_t entries[] = {10, 5, 8, 34, 67, 23, 156, 24, 2, 12};
  const size_t n = sizeof(entries) / sizeof(entries[0]);
  test_minmax(entries, n);
}

int main(){
    node_t* ans = test_minmax_suite();
    printf("SUCCESS SUCCESS SUCCESS SUCCESS SUCCESS SUCCESS SUCCESS");
}
