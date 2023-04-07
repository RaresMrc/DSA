#include <stdio.h>
#include <stdlib.h>

typedef struct nod {
    int key;
    struct nod* next;
    struct nod* previous;
} node;

typedef struct hash_tableT {
    int n;
    struct nod** first;
} hash_table;

int hash(int key, int n) {
    return abs(key) % n;
}

node* createNode(int key) {
    node* p = (node*) malloc(sizeof(node));
    p->next = NULL;
    p->previous = NULL;
    p->key = key;
    return p;
}

void insert(hash_table hashTable, int key) {
    node* p = createNode(key);
    int hashNr = hash(key, hashTable.n);
    if ((hashTable).first[hashNr] == NULL) {
        (hashTable).first[hashNr] = p;
        return;
    }
    hashTable.first[hashNr]->previous = p;
    p->next= hashTable.first[hashNr];
    hashTable.first[hashNr] = p;
}

node* searchNode(hash_table hashTable, int key) {
    int hashNr = hash(key, hashTable.n);
    node* first = hashTable.first[hashNr];
    if (first == NULL) return NULL;
    while (first->next != NULL && first->key != key) {
        first = first->next;
    }
    if (first->key == key) return first;
    return NULL;
}

void deleteNode(hash_table hashTable, int key) {
    node* p = searchNode(hashTable, key);
    int hashNr = hash(key, hashTable.n);
    if (p == NULL) return;
    if (p->next == NULL && p->previous == NULL) {
        free(p);
        hashTable.first[hashNr] = NULL;
        return;
    }
    if (p->next == NULL || p->previous == NULL) {
        if (p->next == NULL) {
            p->previous->next = NULL;
            free(p);
            return;
        }
        p->next->previous = NULL;
        hashTable.first[hashNr] = p->next;
        free(p);
        return;
    }
    p->previous->next = p->next;
    p->next->previous = p->previous;
    free(p);
}


int main() {
    int n;
    printf("n: ");
    scanf("%d", &n);

    hash_table hashTable;
    hashTable.n = n;
    hashTable.first = calloc(n, sizeof(node*));

    insert(hashTable, 36);
    insert(hashTable, 14);
    insert(hashTable, 26);
    insert(hashTable, 21);
    insert(hashTable, 5);
    insert(hashTable, 19);
    insert(hashTable, 4);

    for (unsigned int i = 0; i < n; i++) {
        node* p = hashTable.first[i];
        while (p != NULL) {
            printf("%d ", p->key);
            p = p->next;
        }
        printf("\n");
    }

    printf("Nod care exista: %d\n", searchNode(hashTable, 5)->key);
    printf("Nod care nu exista: %p\n", searchNode(hashTable, 3));

    deleteNode(hashTable, 21);
    for (unsigned int i = 0; i < n; i++) {
        node *p = hashTable.first[i];
        while (p != NULL) {
            printf("%d ", p->key);
            p = p->next;
        }
        printf("\n");
    }
    return 0;
}
