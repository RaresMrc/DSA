#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 7

typedef struct nod {
    int val;
    struct nod* next;
} node;

typedef struct coada {
    int vec[CAPACITY];
    int size;
    int head, tail;
} queue;

typedef struct noduri {
    int val;
    struct noduri* next;
    struct noduri* prev;
} nodes;

typedef struct list_header {
    nodes* first;
    nodes* last;
} list;

node* createNode(int value) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

void push(node** first, int givenValue) {
    //creez un nod nou, daca e NULL first o sa fie pointer catre noul elem.
    node* newNode = createNode(givenValue);
    if ((*first) == NULL) {
        (*first) = newNode;
        return;
    }
    newNode->next = (*first);
    (*first) = newNode;
}

int pop(node** first) {
    if ((*first) == NULL) return - 1;
    node* aux = (*first);
    int temp = (*first)->val;
    (*first) = (*first)->next;
    free(aux);
    return temp;
}

void showStack(node* first) {
    while (first != NULL) {
        printf("%d ", first->val);
        first = first->next;
    }
}

void queue_init(queue* _queue) {
    _queue->size = 0;
    _queue->head = 0;
    _queue->tail = 0;
}

void enqueue(queue* _queue, int key) {
    if (_queue->size == CAPACITY) return;

    _queue->vec[_queue->tail] = key;
    _queue->size++;

    _queue->tail++;
    if (_queue->tail == CAPACITY) _queue->tail = 0;
}

int dequeue(queue* _queue) {
    if (_queue->size == 0) return -1;

    _queue->size--;
    int temp = _queue->head;
    _queue->head++;
    if (_queue->head == CAPACITY) _queue->head = 0;
    return _queue->vec[temp];
}
void init_list(list* _list) {
    _list->first = NULL;
    _list->last = NULL;
}
void insert_first(list* _list, int key) {
    nodes* p = (nodes*) malloc(sizeof(nodes));
    if (_list->first == NULL) {
        p->val = key;
        p->next = NULL;
        p->prev = NULL;
        _list->first = p;
        _list->last = p;
        return;
    }
    p->val = key;
    p->next = _list->first;
    _list->first->prev = p;
    _list->first = p;
    p->prev = NULL;
}

void insert_last(list* _list, int key) {
    nodes* p = (nodes*) malloc(sizeof(nodes));
    if (_list->first == NULL) {
        p->val = key;
        p->next = NULL;
        p->prev = NULL;
        _list->first = p;
        _list->last = p;
        return;
    }
    p->val = key;
    p->next = NULL;
    p->prev = _list->last;
    _list->last->next = p;
    _list->last = p;
}

void delete_first(list* _list) {
    if (_list->first == NULL) return;
    nodes* aux = _list->first;
    _list->first = _list->first->next;
    free(aux);
}

void delete_last(list* _list) {
    if (_list->first == NULL) return;
    if (_list->first->next == NULL) {
        free(_list->first);
        _list->first = NULL;
        _list->last = NULL;
        return;
    }
    nodes* aux = _list->last;
    _list->last = _list->last->prev;
    _list->last->next = NULL;
    free(aux);
}

nodes* searchKey(list* _list, int key) {
    for (nodes* p = _list->first; p != NULL; p = p->next) {
        if (p->val == key) return p;
    }
    return NULL;
}

void insert_after_key(list* _list, int key, int value) {
    nodes* aux = searchKey(_list, key);
    if (aux == NULL) return;

    nodes* p = (nodes*) malloc(sizeof(nodes));
    p->val = value;

    if (aux->next == NULL) {
        _list->last = p;
        p->next = NULL;
        p->prev = aux;
        aux->next = p;
        return;
    }

    p->next = aux->next;
    p->prev = aux;
    (aux->next)->prev = p;
    aux->next = p;
}

void delete_key(list* _list, int key) {
    nodes* p = searchKey(_list, key);
    if (p == NULL) return;

    if (p == _list->first && p == _list->last) {
        _list->first = NULL;
        _list->last = NULL;
        free(p);
        return;
    }

    if (p == _list->first) {
        _list->first = _list->first->next;
        free(p);
        return;
    }

    if (p == _list->last) {
        _list->last = _list->last->prev;
        free(p);
        return;
    }

    (p->prev)->next = p->next;
    (p->next)->prev = p->prev;
    free(p);
}

//void insert_after_key(list* _list, int key) {
//    nodes* aux = searchKey(_list, key);
//    if (aux == NULL) return;
//    nodes* p = (nodes*) malloc(sizeof(nodes));
//
//    p->val = key;
//    p->prev = aux;
//    p->next = aux->next;
//}

void showForwards(list* _list) {
    for (nodes* p = _list->first; p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
}

void showBackwards(list* _list) {
    for (nodes* p = _list->last; p != NULL; p = p->prev) {
        printf("%d ", p->val);
    }
    printf("\n");
}

//stiva, push - insert_first, pop - delete_first cu return
//coada, vector circular

int main() {
    // STIVA --------------------------------------------------------------------------------------------------------
//    node* first;
//    first = NULL;
//
//    for (int i = 0; i < 5; i++) {
//        push(&first, i);
//    }
//
//    showStack(first);
//
//    printf("\n");
//    for (int i = 0; i < 5; i++) {
//        printf("%d ", pop(&first));
//    }
//
//    printf("%d\n", pop(&first));
    // --------------------------------------------------------------------------------------------------------


    //COADA ---------------------------------------------------------------------------------------------------
//    queue coada;
//
//    printf("\n");
//    queue_init(&coada);
//    printf("%d %d %d\n", coada.size, coada.head, coada.tail);
//
//    for (int i = 0; i < 7; i++) {
//        enqueue(&coada, i);
//    }
//
//    enqueue(&coada, 8);
//
//    for (int i = 0; i < 7; i++) {
//        printf("%d ", dequeue(&coada));
//    }
//
//    printf("%d ", dequeue(&coada));
    list listHeader;
    init_list(&listHeader);
    printf("%p %p\n", listHeader.first, listHeader.last);

    printf("Insert first: ");
    for (int i = 0; i < 5; i++) {
        insert_first(&listHeader, i);
    }

    showForwards(&listHeader);
    showBackwards(&listHeader);

    printf("Insert last: ");
    for (int i = 0; i < 5; i++) {
        insert_last(&listHeader, i);
    }

    showForwards(&listHeader);

    printf("Delete first: ");
    for (int i = 0; i < 5; i++) {
        delete_first(&listHeader);
    }

    showForwards(&listHeader);

    printf("Delete last: ");
    for (int i = 0; i < 4; i++) {
        delete_last(&listHeader);
    }
    showForwards(&listHeader);

    printf("%p ", searchKey(&listHeader, 0));
    printf("%p\n", searchKey(&listHeader, -1));

    for (int i = 0; i < 4; i++) {
        insert_after_key(&listHeader, 0, i);
    }

    showForwards(&listHeader);

    for (int i = 0; i < 4; i++) {
        delete_key(&listHeader, i);
    }

    showForwards(&listHeader);
    return 0;
}
