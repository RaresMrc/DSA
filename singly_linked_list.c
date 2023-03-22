#include <stdio.h>
#include <stdlib.h>

typedef struct nod {
    int val;
    struct nod* next;
} node;

node* createNode(int value) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

void init_(node** first, node** last) {
    (*first) = NULL;
    (*last) = NULL;
}

void showList(node* first) {
    while (first != NULL) {
        printf("%d ", first->val);
        first = first->next;
    }
}

void insert_first(node** first, int givenValue) {
    node* newNode = createNode(givenValue);
    if ((*first) == NULL) {
        (*first) = newNode;
        return;
    }
    newNode->next = (*first);
    (*first) = newNode;
}

void delete_first(node** first) {
    //daca lista e goala -> nimic, daca am un element *first == NULL
    if ((*first) == NULL) return;
    node* aux = (*first);
    (*first) = (*first)->next;
    free(aux);
}

void insert_last(node** first, node** last, int value) {
    node* newNode = createNode(value);
    if ((*first) == NULL) {
        (*first) = newNode;
        (*last) = newNode;
        return;
    }
    newNode->next = (*last)->next;
    (*last)->next = newNode;
    (*last) = newNode;
}

void delete_last(node** first, node** last) {
    node* parserPointer = (*first);

    if ((*first) == NULL && (*last) == NULL) return;
    if (parserPointer == (*last)) {
        free((*last));
        (*first) = NULL;
        (*last) = NULL;
    }

    while (parserPointer->next != (*last)) {
        parserPointer = parserPointer->next;
    }

    parserPointer->next = NULL;
    free((*last));
    (*last) = parserPointer;
}

node* search_node(node* first, int value) {
    while (first != NULL) {
        if (first->val == value) return first;
        first = first->next;
    }
    return NULL;
}

void insert_after_key(node** first, node** last, int key, int value) {
    node* newNode = createNode(value);
    node* parserPointer = (*first);
    if ((*first) == NULL) {
        (*first) = newNode;
        (*last) = newNode;
        newNode->next = NULL;
        return;
    }
    while(parserPointer != NULL && parserPointer->val != key) {
        parserPointer = parserPointer->next;
    }
    if (parserPointer == NULL) {
        printf("Key not found\n");
        return;
    }
    newNode->next = parserPointer->next;
    parserPointer->next = newNode;
}

void delete_key(node** first, int key) {
    node* p = search_node(*first, key);
    if (p == NULL) return;
    node* parserPointer = *first;
    if (p == *first) {
        (*first) = (*first)->next;
        free(p);
    } else {
        while (parserPointer->next != p) {
            parserPointer = parserPointer->next;
        }
        parserPointer->next = p->next;
        free(p);
    }
}

void reverse_list(node** first) {
    node* p = *first;
    node* aux = *first;
    node* temp;
    while (p != NULL) {
        if (p == *first) {
            p = p->next;
            aux->next = NULL;
            continue;
        }
        temp = p->next;
        if (temp == NULL) (*first) = p;
        p->next = aux;
        aux = p;
        p = temp;
    }
}

int main() {
    node* first;
    node* last;

    init_(&first, &last);

    for (int i = -10; i <= 10; i++) {
        insert_last(&first, &last, i);
    }

    for (int i = 0; i <= 10; i++) {
        delete_last(&first, &last);
    }

    for (int i = -10; i <= -1; i++) {
        insert_after_key(&first, &last, i, -i);
    }

    delete_key(&first, 10);

    reverse_list(&first);
//    printf("%d\n", search_node(first, -10)->val);

    showList(first);
    return 0;
}
