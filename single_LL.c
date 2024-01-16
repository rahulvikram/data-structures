#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// creating node data type (data, pointer to next)
typedef struct node {
    int data; // value of data you want to store in the list position
    struct node *next; // pointer: node that points to (holds address of) next node in list
} node;

void printList(node *head);
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: list must have at least one value.\n");
        return 1;
    }

    // inits the head of the LL
    node *head = NULL;

    // for each num provided by the user in terminal...
    for (int i = 1; i < argc; i++) {
        int num = atoi(argv[i]); // converts num to int

        node *n = malloc(sizeof(node)); // allocates memory for node
        if (n == NULL) {
            printf("error allocating memory for node\n");
            return 2;
        }
        
        n->data = num;
        n->next = head;
        head = n; // IMPORTANT: this is done so that in the next iteration, n can point to the new head, not the original head
    }

    printList(head);
}


void printList(node *head) {
    node *temp = head; // temporarily, the head is the current node

    printf("Linked List: ");

    // while the next node in list is not NULL, AKA for each node in the list
    while (temp != NULL) {
        printf("%i --> ", temp->data); // print each node's data
        temp = temp->next; // reassign temp var to point to the next node
    }
    
    // if end of LL reached, make last node point to NULL when printing
    if (temp == NULL) {
        printf(" NULL\n");
    }
}