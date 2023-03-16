#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree{
    int field;
    struct tree *left;
    struct tree *right;
} tree;

struct tree *treecreation(struct tree *tr, int n) {
    if (tr == NULL) {
        tr = (struct tree*)malloc(sizeof(struct tree));
        tr->field = n;
        tr->left =  NULL;
        tr->right = NULL;
    }
    else  if (n < tr->field){
        tr->left = treecreation(tr->left, n);
    }
    else{
        tr->right = treecreation(tr->right, n);
    }
    return tr;
}
int check = 0;
int treesearch(struct tree *tr, int n, int leng){
    if (tr != NULL) {
        if (n < tr->field && check == 0){
            leng = treesearch(tr->left, n, leng);
            leng+=1;
        }
        if (n > tr->field && check == 0){
            leng = treesearch(tr->right, n, leng);
            leng+=1;
        }
        if (n == tr->field){
            check = 1;
        }
    }
    if (check == 0){
        leng = -1;
    }
    return leng;
}

void treeprint(struct tree *tr) {
    //printf("%d\n",count);
    printf("%d ", tr->field);
    if (tr->left!=NULL){
        treeprint(tr->left);
    }
    if (tr->right!=NULL){
        treeprint(tr->right);
    }
}

void deltree(struct tree* tr) {
  if (tr != NULL) {
    deltree(tr->left);
    deltree(tr->right);
    free(tr);
  }
}

int main(){
    struct tree *tr;
    int limit, elem;
    printf("Enter the number of tree's elements: \n");
    scanf("%d", &limit);
    tr = (struct tree*)malloc(sizeof(struct tree));
    printf("Enter your tree\n");
    tr = NULL;
    while (limit!=0){
        scanf("%d", &elem);
        tr = treecreation(tr, elem);
        limit-=1;
    }
    printf("Tree: \n");
    treeprint(tr);
    int elch, leng = 0;
    printf("\nEnter the element you want to check: \n");
    scanf("%d", &elch);
    leng = treesearch(tr, elch, leng);
    if (leng!=-1){
        printf("Distance to your element is: \n");
        printf("%d\n", leng);
    }
    else{
        printf("Element is not in the tree");
    }
    deltree(tr);

}
