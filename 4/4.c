#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define b 50
struct list{
    char *field;
    struct list *next;
} list;

struct word{
    char field;
    struct word *next;
}word;

int eofcheck = 0;
int lword = 0;
struct word *readword(){
    int i = 0;
    struct word *w, *root;
    w = (struct word*)malloc(sizeof(word));
    root = w;
    char sym;
    sym = getchar();
    while (sym  == ' ') {
        sym = getchar();
    }
    if (sym == '\n' || sym == EOF){
        eofcheck = 1;
        return NULL;
    }
    w->field = sym;
    w->next = NULL;
    lword +=1;
    struct word *save, *p;
    root = w;
    while ((sym!='\0') && (sym!= ' ') && (sym!='\n')){
        p = (struct word*)malloc(sizeof(struct word));
        if (i==0){
            w->field = sym;
            w->next = NULL;
            i+=1;
        }
        else{
            save = w -> next;
            w -> next = p;
            p -> field = sym;
            p -> next = save;
            w = w->next;
        }
        lword+=1;
        sym = getchar();
    }
    if (sym == '\n' || sym == EOF){
        eofcheck = 1;
    }
    return root;
}

struct list *enterlist(char *a){
    struct list *l;
    l = (struct list*)malloc(sizeof(list));
    l->field = a;
    l->next = NULL;
    return l;
}

struct list *addelem(struct list *l, char *a){
    struct list *save, *p;
    p = (struct list*)malloc(sizeof(struct list));
    save = l -> next;
    l -> next = p;
    p -> field = a;
    p -> next = save;
    return p;
}
void listprint(struct list *root){
    struct list *p;
    p = root;
    while (p!=NULL){
        printf("%s ", p->field);
        p = p->next;
    }
}
void wordprint(struct word *root){
    struct word *p;
    p = root;
    while (p!=NULL){
        printf("%c", p->field);
        p = p->next;
    }
}
int ind = 0;
int igl = 0;
struct list *converting(struct list *l, struct word *w){
    struct word *p;
    p = w;
    int i=0;
    char *str = (char*)malloc(lword+4);
    while (p!=NULL){
        *(str+i) = p->field;
        i+=1;
        p = p->next;
    }
    *(str+i) = '\0';
    ind += 1;
    if (ind==1){
        l = enterlist(str);
    }
    else{
        l = addelem(l, str);
    }
    return l;
}
int counter = 0;

void printreverse(struct list *l)
{
    int i = 0;
    char *newstr;
    if (l == NULL){         //terminate if it's the end
        return;
    }
    printreverse(l->next); // go to next one
    printf("%s ", l->field);
}

int length(struct word *l) {
    int count = 0;
    while ((l -> next != NULL) && (l -> field != ' ')) {
        count++;
        l = l -> next;
    }
    if (l -> next == NULL) {
        count++;
    }
    return count;
}
int percheck = 0;
int ii = 0;
int check(struct list *s1, struct list *s2) {
    char *c1 = s1->field;
    char *c2 = s2->field;
    int i = 0, ch = 0;
    while ((*(c1+i) != '\0') && (*(c2+i) != '\0') && (ch == 0) && *(c1+i)!='\n' && *(c2+i) != '\n') {
        if (*(c1+i) == *(c2+i)) {
            i++;
        }
        else if (*(c1+i) < *(c2+i)) {
            return ch;
        }
        else if (*(c1+i) > *(c2+i)) {
            ch = 1;
        }
    }
    return ch;
}

void alphabet(struct list *l, int leng){
    struct list *p, *s, *root;
    int ch;
    root = l;
    s = l;
    char *c;
    for(int i = 0; i<leng-1; i++) {
        p = l;
        s = p -> next;
        for(int j = 0; j<leng-i-1; j++) {
            ch = check(p, s);
            if (ch == 1){
                c = p->field;
                p->field = s->field;
                s->field = c;
            }
            if (s->next != NULL) {
                s = s->next;
                }
        }
        l = p->next;
    }
    printf("\nAlphabetical order: \n");
    listprint(root);
}
struct list *deleteheadlist(struct list *root){
  struct list *l;
  l = root->next;
  free(root -> field);
  free(root); // освобождение памяти текущего корня
  return l; // новый корень
}

struct word *deleteheadword(struct word *root){
  struct word *l;
  l = root->next;
  free(root);
  return l;
}

int main(){
    struct word *w, *wroot;
    struct list *l, *root; // list of words
    l = (struct list*)malloc(sizeof(list));
    int leng = 0;
    printf("Enter your string: \n");
    while (eofcheck == 0){
        w = readword();
        l = converting(l, w);
        if (ind == 1){
            root = l;
        }
        leng +=1;
       // while ((w -> next) != NULL) {
        //    w = deleteheadword(w);
        //}

    }
    l = root;
    printf("List of words: \n");
    listprint(root);
    printf("\n");
    printf("Reversed list: \n");
    printreverse(root);
    alphabet(l, leng);
    //while ((l) != NULL) {
    //        l = deleteheadlist(l);
    //}
    //while ((w) != NULL) {
    //        w = deleteheadword(w);
    //}
    //free(l);
    //free(root);
    //free(w);
}



