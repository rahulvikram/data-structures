#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 5

// data structure for key-value pairs; the node"s data
typedef struct KeyValue {
    char key[50];
    int value;
} KeyValue;

// data structure for node; each item that holds data and pointer to next item in LL in hash table
typedef struct Node {
    KeyValue data;
    struct Node *next;
} Node;

// data structure for the actual hashtable; an array of linkedlists, each containing nodes
typedef struct HashTable {
    Node *table[TABLE_SIZE];
} HashTable;

// Hash function
unsigned int hash(char* key) {
    unsigned int hashVal = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashVal = 31 * hashVal + key[i];
    }
    return hashVal % TABLE_SIZE; // will return a value between 0 and 4, AKA table"s index
}

// function to initialize a hashtable, by setting each node to NULL (therefore, each node exists)
void initializeHashTable(HashTable *hashtable) {
    for (int i = 0; i < TABLE_SIZE; i++) { // for each item in the table
        hashtable->table[i] = NULL; // set each Node to NULL
    }
}

// function to insert node into a hashtable; params: table to insert into, key and value to insert into a node, to insert into table
// user will be mostly using this function repeatedly
void insertNode(HashTable *hashtable, char *key, int value) {
    unsigned int tableIndex = hash(key);

    Node *newNode = malloc(sizeof(Node));
    // ensures node properly allocated
    if (newNode == NULL) {
        fprintf(stderr, "Node memory allocation failed.\n");
        exit(1);
    }

    // assign node values
    strcpy(newNode->data.key, key);
    newNode->data.value=value;
    
    // insert node into the beginning of whatever index its at
    newNode->next=hashtable->table[tableIndex]; // newNode points to beginning of linked list at index
    hashtable->table[tableIndex] = newNode; // updates hashtable"s linked list at index to be equal to the new node, completing process
}

// searches and returns value of a key in hash table
int returnValue(HashTable *hashtable, char *key) {
    unsigned int index = hash(key); // gets hash value of whatever key

    // Linked-list traversal at whatever index of the table we are at
    Node *current = hashtable->table[index]; // start current node at index
    while (current != NULL) // while the node is not NULL
    {
        // if user inputted key matches the current node's key
        if (strcmp(current->data.key, key) == 0) {
            return current->data.value; // return the node's value, end function
        }
        // else if it does not match, move to the next node in LL
        current = current->next; 
    }
    
    printf("Value not found; Key does not exist.\n");
    return -1;
}

int main() {
    HashTable hashtable;
    initializeHashTable(&hashtable);

    // upload data into hash table
    // insertNode(&hashtable, "Software", 213000);
    insertNode(&hashtable, "Hardware", 221000);
    // insertNode(&hashtable, "Manager", 289000);
    // insertNode(&hashtable, "Director", 453000);
    insertNode(&hashtable, "VP", 853000);
    // insertNode(&hashtable, "CEO", 1654000);

    // returnValue testing
    printf("%i\n", returnValue(&hashtable, "Hardware"));
    printf("%i", returnValue(&hashtable, "VP"));

    return 0;
}
