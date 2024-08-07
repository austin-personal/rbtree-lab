#include "rbtree.h"

#include <stdlib.h>
#include "stdio.h"

void left_rotate(rbtree *t, node_t * child);
void right_rotate(rbtree *t, node_t * child);

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  if (p == NULL) {
    // Handle allocation failure if needed
    return NULL;
  }
  // init rbtree
  p->nil = nil;
  p->root = nil;

  nil->left = NULL;
  nil->right = NULL;
  nil->parent = NULL;
  nil->color = RBTREE_BLACK;
  return p;
}
void print_tree(rbtree* t, node_t* node){
  if (node == t->nil){
    return;
  }
  print_tree(t, node->left);
  printf("%d\n",node->key);
  print_tree(t, node->right);
  
}
//Rotate function
void left_rotate(rbtree *t, node_t * cur) {
  node_t* parent = cur->parent;
  //logic for turn toward left
  parent->right = cur->left;
  // cur->right = child->left;
  if (parent->right != t->nil){
    cur->left->parent = parent;
  }
  cur->parent = parent->parent;
  parent->parent = cur;
  cur->left = parent;
  // child->parent = cur->parent;
  if (cur->parent == t->nil){
    t->root = cur;
  }else if(parent == cur->parent->left){ // cur이 왼쪽 자식일때
    cur->parent->left = cur;
  }else{
    cur->parent->right = cur;
  }
}

void right_rotate(rbtree *t, node_t * cur) {
  node_t* parent = cur->parent;
  //logic for turn toward left
  parent->left = cur->right;
  // cur->right = child->left;
  if (parent->left != t->nil){
    cur->right->parent = parent;
  }
  cur->parent = parent->parent;
  parent->parent = cur;
  cur->right = parent;
  // child->parent = cur->parent;
  if (cur->parent == t->nil){
    t->root = cur;
  }else if(parent == cur->parent->right){ // cur이 왼쪽 자식일때
    cur->parent->right = cur;
  }else{
    cur->parent->left = cur;
  }
}

void insert_fixup(rbtree* t, node_t* node) {
  node_t* uncle;
  while (node->parent->color == RBTREE_RED) {
    if (node->parent == node->parent->parent->left) {
      uncle = node->parent->parent->right;
      if (uncle->color == RBTREE_RED) {
        node->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        node->parent->parent->color = RBTREE_RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          left_rotate(t, node);
      }
      node->color = RBTREE_BLACK;
      node->parent->color = RBTREE_RED;
      right_rotate(t, node);
      }
    } else {
      uncle = node->parent->parent->left;
      if (uncle->color == RBTREE_RED) {
        node->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        node->parent->parent->color = RBTREE_RED;
        node = node->parent->parent;
      } else {
      if (node == node->parent->left) {
        right_rotate(t, node);
      }
      node->color = RBTREE_BLACK;
      node->parent->color = RBTREE_RED;
      
      left_rotate(t, node);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

void del_recur(node_t* node, rbtree* t) {
  if (node == t->nil) {
    return;
  }
  del_recur(node->left, t);
  del_recur(node->right,t );
  free(node);
}
  
void delete_rbtree(rbtree *t) {
  del_recur(t->root, t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  //Insert Root
  node_t* parent;
  if (t->root == t->nil) {
    node_t* rootVal = (node_t *)calloc(1, sizeof(node_t)); // allocate memory for the root node
    rootVal->parent = t->nil;
    rootVal->color = RBTREE_BLACK;
    rootVal->left = t->nil;
    rootVal->right = t->nil;
    rootVal->key = key; // initialize key for the root node

    t->root = rootVal;
  } else { // When it is not root
    node_t* cur = t->root;
    //Find the place to insert(find the parent node)
    while (cur != t->nil) {
      parent = cur;
      if (key < cur->key) {
        cur = cur->left;
      } else {
        cur = cur->right;
      }
  }
    // Build insert node
    node_t* newNode = (node_t *)calloc(1, sizeof(node_t)); // allocate memory for the new node
    newNode->parent = parent;
    newNode->color = RBTREE_RED;
    newNode->key = key;
    newNode->left = t->nil;
    newNode->right = t->nil;
    // Decide right or left
    if (key > parent->key) {
      parent->right = newNode;
    } else {
      parent->left = newNode;
    }
    if (newNode->parent->color == RBTREE_RED){
      insert_fixup(t, newNode);
    }
  }
  return t->root;
}
node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t* cur = t->root;
  while (cur != t->nil)
  {
    if (cur->key == key)
    {
      return cur;
    }
    if (cur->key > key){
      cur = cur->left;
    } else{
      cur = cur->right;
    }
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  node_t* cur = t->root;
  while (cur != t->nil)
  {
    if (cur->left !=t->nil){
      cur = cur->left;
    }
  }
  
  return cur;
}

node_t *rbtree_max(const rbtree *t) {
  node_t* cur = t->root;
  while (cur != t->nil)
  {
    if (cur->right !=t->nil){
      cur = cur->right;
    }
  }
  
  return cur;
}










int rbtree_erase(rbtree *t, node_t *p) {
  node_t* succ = NULL;
  node_t* cur = NULL;
  color_t color = NULL;
  color_t delColor = NULL;
  key_t k = NULL;
  //1. 자녀가 2개일때
  if (p->left != t->nil && p->right != t->nil){

    cur = p->right; // 자녀가 두개면 Succ은 오른쪽 subtree안에

    //2. 삭제노드의 자녀가 succ일때 (오른쪽자녀의 왼쪽자녀가 없는 경우)
    if (p->right->left == t->nil){
      succ = p->right;
      p->key = succ -> key;
      p->left = succ -> right;
      delColor = succ -> color;

    //2. 삭제 노드가 손자 이하라면 (오른쪽 자녀의 왼쪽자녀가 있는 경우)
    }else{ 
      //3. succ의 노드 찾기
      cur = cur->left;
      while (cur != t->nil)
      {
        succ = cur;
        cur = cur->left;
      }
      //4. succ의 key값을 p에 넣어주고, succ의 color를 삭제 컬러로 등록
      p->key = succ.key;
      delColor = succ.color;
    }


  //1. 자녀노드가 하나 이하일때
  }else{ 
    // 2. 자녀노드가 없을때
    if (p->left == t->nil && p->right == t->nil){
      // 3. 오른쪽에서 왔을때
      if (p == p->parent->left){
        p->parent->left = t->nil;
        delColor = p->color;

      // 3. 왼쪽에서 왔을때
      }else{ 
        p->parent->right = t->nil;
        delColor = p->color;
      }


    // 2. 자녀 노드가 하나일때
    } else{ 
      // 3. 왼쪽에만 있을때
      if (p->left != t->nil){
        p->key = p->left->key; //key
        delColor = p->left->color;//delete color
        p->left = p->right->left;//자식
        p->right = p->right->right;//자식
      // 3. 오른쪽에만 있을때
      }else{ 
        p->key = p->right->key; //key
        delColor = p->right->color;//delete color
        p->left = p->left->left;//자식
        p->right = p->left->right;//자식
      } 
    }
  }
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
