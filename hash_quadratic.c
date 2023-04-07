#include <stdio.h>
#include <stdlib.h>

typedef struct hash_tableT {
    int n;
    int* first;
} hash_table;

int hash(hash_table hashTable, int key) {
    int i = 0;
    int hashNr;

    do {
        hashNr = (key % hashTable.n + i + i * i) % hashTable.n;
        i++;
    } while (hashTable.first[hashNr] != 0 && i != hashTable.n);
    if (hashTable.first[hashNr] != 0) return -1;
    return hashNr;
}

void insert(hash_table hashTable, int key) {
    int hashNr = hash(hashTable, key);
    if (hashNr == -1) return;
    hashTable.first[hashNr] = key;
}

int searchKey(hash_table hashTable, int key) {
    for (unsigned int i = 0; i < hashTable.n; i++) {
        if (hashTable.first[i] == key) return i;
    }
    return -1;
}

int main() {
    hash_table hashTable;

    printf("n: ");
    scanf("%d", &hashTable.n);
    hashTable.first = calloc(hashTable.n, sizeof(int));

    insert(hashTable, 19);
    insert(hashTable, 36);
    insert(hashTable, 5);
    insert(hashTable, 21);
    insert(hashTable, 4);
    insert(hashTable, 26);
    insert(hashTable, 14);

    for (unsigned int i = 0; i < hashTable.n; i++) {
        printf("%d ", hashTable.first[i]);
    }

    printf("\n");
    printf("%d\n", searchKey(hashTable, 14));

    return 0;
}
