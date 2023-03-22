#include <stdio.h>
#include <stdlib.h>

typedef struct nodeT {
    int val;
    struct nodeT* left;
    struct nodeT* right;
} node;

node* create(int key) {
    node* p = (node*) malloc(sizeof(node));
    p->val = key;
    p->left = NULL;
    p->right = NULL;
    return p;
}

node* read(FILE* path) {
    char s[100];
    fscanf(path, "%s", s);
    if (s[0] == '#') return NULL;
    else {
        int x = atoi(s);
        node* q = create(x);
        q->left = read(path);
        q->right = read(path);
        return q;
    }
}

void preorder(node* q) {
    if (q == NULL) return;
    printf("%d ", q->val);
    preorder(q->left);
    preorder(q->right);
}

void inorder(node* q) {
    if (q == NULL) return;
    inorder(q->left);
    printf("%d ", q->val);
    inorder(q->right);
}

void postorder(node* q) {
    if (q == NULL) return;
    postorder(q->left);
    postorder(q->right);
    printf("%d ", q->val);
}

int leafCount(node* q) {
    if (q == NULL) return 0;
    int s = 0;
    if (q->left == NULL && q->right == NULL) {
        printf("%d ", q->val);
        s = 1;
    }
    return s + leafCount(q->left) + leafCount(q->right);
}

int internNodes(node* q) {
    if (q == NULL) return 0;
    int s = 0;
    if (q->left != NULL || q->right != NULL) s = 1;
    return s + internNodes(q->left) + internNodes(q->right);
}

int max(int a, int b) {
    if (a >= b) return a;
    return b;
}

int nodeHeight(node* q) {
    if (q == NULL) return 0;
    if (q->left == NULL && q->right == NULL) return 0;
    return 1 + max(nodeHeight(q->left), nodeHeight(q->right));
}

node* searchNode(node* q, int key) {
    if (q == NULL) return NULL;
    if (q->val == key) return q;
    searchNode(q->left, key);
    searchNode(q->right, key);
}


int diameter(node* q) {
    if (q->left == NULL && q->right == NULL) return 0;
    int c1 = 1;
    int c2 = 1;
    if (q->left == NULL) c1 = 0;
    if (q->right == NULL) c2 = 0;
    return nodeHeight(q->left) + c1 + nodeHeight(q->right) + c2;
}

int main() {
    FILE* path = fopen("binTree.txt", "r");
    if (!path) return -1;

    node* root = read(path);
    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    printf("Leafs: %d ", leafCount(root));
    printf("\n");
    printf("Intern nodes: %d ", internNodes(root));
    printf("\n");
    printf("%d ", nodeHeight(searchNode(root, 7)));
    printf("\n");
    printf("%d ", searchNode(root, 3)->val);
    printf("\n");
    printf("%d ", diameter(root));
    return 0;
}
