#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void printTree(rbtree *t, node_t *cur, int level, int isLeft)
{
  if (cur == t->nil)
  {
    return;
  }

  // 오른쪽 자식 노드 출력
  printTree(t, cur->right, level + 1, 0);

  // 현재 노드 출력
  for (int i = 0; i < level - 1; i++)
  {
    printf("    ");
  }
  if (level > 0)
  {
    printf(isLeft ? " \\_ " : " /⎺ "); // 왼쪽 자식일 경우 "\\" 출력, 오른쪽 자식일 경우 "/" 출력
  }
  if (cur->color == RBTREE_RED)
  {
    printf("\x1b[31m%d\x1b[0m\n", cur->key);
  }
  else
  {
    printf("%d\n", cur->key);
  }

  // 왼쪽 자식 노드 출력
  printTree(t, cur->left, level + 1, 1);
}

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *t = (node_t *)calloc(1, sizeof(node_t));
  t->color = RBTREE_BLACK;
  p->nil = t;
  p->root = p->nil;
  return p;
}

void postOrder_delete(node_t *root, node_t *nil)
{
  if (nil == root)
    return;
  postOrder_delete(root->left, nil);
  postOrder_delete(root->right, nil);
  free(root);
}
void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  postOrder_delete(t->root, t->nil);
  free(t->nil);
  free(t);
}

void left_rotate(rbtree *t, node_t *node)
{
  node_t *child = node->right;
  node->right = child->left;

  if (child->left != t->nil)
  {
    child->left->parent = node;
  }

  child->parent = node->parent;

  if (node->parent == t->nil)
  {
    t->root = child;
  }
  else if (node == node->parent->left)
  {
    node->parent->left = child;
  }
  else
  {
    node->parent->right = child;
  }

  child->left = node;
  node->parent = child;
}

void right_rotate(rbtree *t, node_t *node)
{
  node_t *child = node->left;
  node->left = child->right;

  if (child->right != t->nil)
  {
    child->right->parent = node;
  }

  child->parent = node->parent;

  if (node->parent == t->nil)
  {
    t->root = child;
  }
  else if (node == node->parent->right)
  {
    node->parent->right = child;
  }
  else
  {
    node->parent->left = child;
  }

  child->right = node;
  node->parent = child;
}

void rbtree_insert_fixup(rbtree *t, node_t *new_node)
{
  while (new_node->parent->color == RBTREE_RED)
  {
    if (new_node->parent == new_node->parent->parent->left)
    {
      node_t *uncle = new_node->parent->parent->right;
      if (uncle->color == RBTREE_RED)
      {
        new_node->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        new_node = new_node->parent->parent;
      }
      else
      {
        if (new_node == new_node->parent->right)
        {
          new_node = new_node->parent;
          left_rotate(t, new_node);
        }
        new_node->parent->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        right_rotate(t, new_node->parent->parent);
      }
    }
    else
    {
      node_t *uncle = new_node->parent->parent->left;
      if (uncle->color == RBTREE_RED)
      {
        new_node->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        new_node = new_node->parent->parent;
      }
      else
      {
        if (new_node == new_node->parent->left)
        {
          new_node = new_node->parent;
          right_rotate(t, new_node);
        }
        new_node->parent->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        left_rotate(t, new_node->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const int key)
{
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->key = key;

  node_t *y = t->nil;
  node_t *x = t->root;

  while (x != t->nil)
  {
    y = x;
    if (new_node->key < x->key)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }

  new_node->parent = y;

  if (y == t->nil)
  {
    t->root = new_node;
  }
  else if (new_node->key < y->key)
  {
    y->left = new_node;
  }
  else
  {
    y->right = new_node;
  }

  new_node->color = RBTREE_RED;
  new_node->left = t->nil;
  new_node->right = t->nil;
  rbtree_insert_fixup(t, new_node);
  // printTree(t, t->root, 0, 0);
  return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  node_t *temp = t->root;
  // temp가 nil이 되거나 , key값이 같은게 있을 때까지
  while (temp != t->nil && temp->key != key)
  {
    if (temp->key > key)
    {
      temp = temp->left;
    }
    else
    {
      temp = temp->right;
    }
  }

  if (temp == t->nil)
  {
    return NULL;
  }

  return temp;
}

node_t *find_max(const rbtree *t, node_t *sub_root)
{ // 가장 왼쪽
  node_t *cur = sub_root;
  while (cur->right != t->nil)
  {
    cur = cur->right;
  }
  return cur;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  return find_max(t, t->root);
}

node_t *find_min(const rbtree *t, node_t *sub_root)
{ // 가장 왼쪽
  node_t *cur = sub_root;
  while (cur->left != t->nil)
  {
    cur = cur->left;
  }
  return cur;
}

node_t *rbtree_min(const rbtree *t)
{
  // RB tree 중 최소 값을 가진 node pointer 반환

  return find_min(t, t->root);
}

void rb_transplant(rbtree *t, node_t *u, node_t *v)
{
  if (u->parent == t->nil)
  {
    t->root = v;
  }
  else if (u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void rbtree_delete_fixup(rbtree *t, node_t *x)
{
  while (x != t->root && x->color == RBTREE_BLACK)
  {
    if (x == x->parent->left)
    {
      node_t *w = x->parent->right;
      if (w->color == RBTREE_RED)
      {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }

      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
      {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else
      {
        if (w->right->color == RBTREE_BLACK)
        {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
      }
    }
    else
    {
      node_t *w = x->parent->left;
      if (w->color == RBTREE_RED)
      {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK)
      {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else
      {
        if (w->left->color == RBTREE_BLACK)
        {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *z)
{
  // TODO: implement erase
  node_t *y = z;
  color_t y_original_color = y->color;
  node_t *x = NULL;

  if (z->left == t->nil)
  {
    x = z->right;
    rb_transplant(t, z, z->right);
  }
  else if (z->right == t->nil)
  {
    x = z->left;
    rb_transplant(t, z, z->left);
  }
  else
  {
    y = find_min(t, z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z)
    {
      x->parent = y;
    }
    else
    {
      rb_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rb_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if (y_original_color == RBTREE_BLACK)
  {
    rbtree_delete_fixup(t, x);
  }
  t->nil->parent = NULL;
  t->nil->right = NULL;
  t->nil->left = NULL;
  t->nil->color = RBTREE_BLACK;
  free(z);
  return 0;
}

// 전위순회 하면서 arr에 값 집어넣기
void preOrder(node_t *root, node_t *nil, key_t *arr, int *index)
{
  // 현재 노드가 빈 노드(nil)이면 함수 종료
  if (root == nil)
  {
    return;
  }
  preOrder(root->left, nil, arr, index);
  
  // 현재 노드의 키 값을 배열에 넣고, 인덱스 증가
  arr[(*index)++] = root->key;

  // 위의 코드는 값을 할당한 후 인덱스를 증가시키지만, 아래의 코드는 현재 인덱스 다음 위치에 할당을 함
  // arr[(*index) + 1] = root->key;
  preOrder(root->right, nil, arr, index);
}

// 레드-블랙 트리의 모든 노드를 배열에 넣는 함수
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // 배열에 넣을 인덱스를 가리키는 포인터 동적 할당
  int *index = calloc(1, sizeof(*index));
  // 레드-블랙 트리의 루트에서부터 전위순회하여 배열에 값 넣기
  preOrder(t->root, t->nil, arr, index);
  free(index);
  return 0;
}
