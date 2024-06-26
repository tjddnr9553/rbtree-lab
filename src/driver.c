#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

// void postOrder(rbtree *t, node_t *cur)
// {
//     if (cur == t->nil)
//     {
//         // printf("nil ");
//         return;
//     }

//     postOrder(t, cur->left);
//     postOrder(t, cur->right);
//     printf("%d ", cur->key);
// }

// int main(int argc, char *argv[])
// {
//     rbtree *t = new_rbtree();
//     for (int i = 1; i <= 15; i++)
//     {
//         rbtree_insert(t, i);
//         postOrder(t, t->root);
//         printf("\n");
//     }
//     return 0;
// }

// void printTree(rbtree *t, node_t *node){
//     if(node== NULL || node == t->nil) return;
//     char *color_str;
//     if (node->color == RBTREE_RED) {
//         color_str = "R";
//     } else {
//         color_str = "B";
//     }
//     printf("%d(%s) ", node->key, color_str);
//     printTree(t,node->left);
//     printTree(t,node->right);
// }

// int main(int argc, char *argv[])
// {
//     int choice, value;
//     char e;
//     node_t *res;
//     rbtree *t;
//     t = new_rbtree();
//     choice = 1;

//     while(choice != 0){
//         printf("-------------------------------------\n");
//         printf("Please input your choice(1/2/3/4/5/0)\n");
//         printf("-------------------------------------\n");
//         printf("1: rbtree insert\n");
//         printf("2: rbtree find\n");
//         printf("3: rbtree_erase\n");
//         printf("4: rbtree min\n");
//         printf("5: rbtree max\n");
//         printf("0: Quit;\n");
//         printf(": ");
//         if(scanf("%d", &choice) > 0)
//         {
//             switch(choice)
//             {
//             case 1:
//                 printf("값을 입력하세요:\n");
//                 if(scanf("%d", &value)==1){
//                     rbtree_insert(t, value);
//                     printf("The resulting tree is: ");
//                     printTree(t,t->root);
//                     printf("\n");
//                 } else {
//                     printf("다시 입력하세요");
//                 }
//                 break;
//             case 2:
//                 printf("찾을 값을 입력하세요:\n");
//                 if(scanf("%d", &value)==1){
//                     res = rbtree_find(t, (key_t)value);
//                     if (res != NULL) { // 찾음
//                         printf("The resulting node is: ");
//                         printf("%d", res->key);
//                         if (res->color == RBTREE_RED) {
//                             printf("(RED)");
//                         } else {
//                             printf("(BLACK)");
//                         }
//                         printf("\n");
//                     }
//                     else { // 못찾음
//                         printf("찾을 수 없습니다.\n");
//                     }
//                 } else {
//                     printf("다시 입력하세요");
//                 }
//                 break;
//             case 3:
//                 printf("지울 값을 입력하세요:\n");
//                 if(scanf("%d", &value)==1){
//                     res = rbtree_find(t, (key_t)value);
//                     printf("The erased node is: ");
//                     printf("%d", res->key);
//                     if (res->color == RBTREE_RED) {
//                         printf("(R)");
//                     } else {
//                         printf("(B)");
//                     }
//                     printf("\n");
//                     rbtree_erase(t,res);
//                     printf("The resulting tree is: ");
//                     printTree(t,t->root);
//                     printf("\n");
//                 } else {
//                     printf("다시 입력하세요");
//                 }
//                 break;
//             case 4:
//                 res = rbtree_min(t);
//                 if (res != NULL) {
//                     printf("Minimum is %d\n", res->key);
//                 }
//                 else {
//                     printf("최소값을 찾을 수 없습니다.\n");
//                 }
//                 break;
//             case 5:
//                 res = rbtree_max(t);
//                 if (res != NULL) {
//                     printf("Maximum is %d\n", res->key);
//                 }
//                 else {
//                     printf("최대값을 찾을 수 없습니다.\n");
//                 }
//                 break;
//             case 0:
//                 break;
//             default:
//                 printf("Choice unknown;\n");
//                 break;
//             }
//         }
//         else
//         {
//             scanf("%c",&e);
//         }
//     }
//     return 0;
// }