#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (a > b ? b : a)

typedef struct BSTree {
    char str[50];
    struct BSTree* left, *right;
} Node;

// auxiliar na ordenação lexicográfica
int maior(const char a[50], const char b[50]) {
    int i;
    int len_a = strlen(a);
    int len_b = strlen(b);

    for(i = 0; i < min(len_a, len_b); i++) {
        if(a[i] > b[i]) {
            return 1;
        } else if(a[i] < b[i]) {
            return 0;
        }
    }

    return len_a > len_b;
}

Node* criar_node(char str[50]) {
    Node* no = (Node*)malloc(sizeof(Node));
    strcpy(no->str, str);
    no->left   = NULL;
    no->right  = NULL;
}

int inserir(Node** no, char str[50]) {
    if((*no) == NULL) {
        (*no) = criar_node(str);
        return 1;
    } else {
        if(maior(str, (*no)->str)) {
            return inserir(&(*no)->right, str);
        } else if(maior((*no)->str, str)) {
            return inserir(&(*no)->left, str);
        } else {
            return 0;
        }
    }
}

int buscar(Node* no, char str[50]) {
    if(no == NULL)
        return -1;

    if(strcmp(no->str, str) == 0)
        return 1;
    
    if(maior(str, no->str))
        return buscar(no->right, str);
    else
        return buscar(no->left, str);
}

void percorrer(Node* node) {
    if(node == NULL)
		return;
	percorrer(node->left);
	printf("%s\n", node->str);
	percorrer(node->right);
}