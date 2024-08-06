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

//Rotate function
void left_rotate(rbtree *t, node_t * parent) {
  node_t* child = parent->right;
  //logic for turn toward left
  parent->right = child->left;
  //debug
  printf("%d, %d", parent->parent->key, child->parent->key);
    
  if (child->right != t->nil) {
    child->left->parent = parent;
  }
  child->parent = parent->parent;
  if (parent->parent == t->nil) {
    t->root = child;
  } else if (parent == parent->parent->left) {
    parent->parent->left = child;
  } else {
    parent->parent->right = child;
    child->left = parent;
    parent->parent = child;
  } 
}

void right_rotate(rbtree *t, node_t * parent) {
  node_t* child = parent->left;
  //logic for turn toward left
  parent->left = child->right;
    
  if (child->left != t->nil) {
    child->right->parent = parent;
  }
  child->parent = parent->parent;
  if (parent->parent == t->nil) {
    t->root = child;
  } else if (parent == parent->parent->left) {
    parent->parent->right = child;
  } else {
    parent->parent->left = child;
    child->right = parent;
    parent->parent = child;
  } 
}

void insert_fixup(rbtree* t, node_t* node) {
  node_t* uncle;
  printf("AAAAAA");
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
        node = node->parent;
        left_rotate(t, node);
      }
      node->parent->color = RBTREE_BLACK;
      node->parent->parent->color = RBTREE_RED;
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
        node = node->parent;
        right_rotate(t, node);
      }
      node->parent->color = RBTREE_BLACK;
      node->parent->parent->color = RBTREE_RED;
      left_rotate(t, node);
      }
    }
  }
}

void del_recur(node_t* node, rbtree* t) {
  if (node->left == t->nil && node->right == t->nil) {
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
    newNode->parent = cur;
    newNode->color = RBTREE_RED;
    newNode->key = key;
    newNode->left = t->nil;
    newNode->right = t->nil;
    // Decide right or left
    if (key > cur->key) {
      cur->right = newNode;
    } else {
      cur->left = newNode;
    }
  }
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
