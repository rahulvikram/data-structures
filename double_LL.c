#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// data type of doubly linked node
typedef struct node {
    int data;

    // previous and next pointers
    struct node *prev;
    struct node *next;
} node;

// node creation
node *createNode(int data);

// node insertion
void insertAtStart(node **head, int data);
void insertAtEnd(node **head, int data);

// list printing
void displayForward(node *head);
void displayBackward(node *head);

// list manipulation
void reverse(node **head);
void delete(node **head, int del);

int main(void) {
    node *head = NULL;

    for (int i = 1; i <= 10; i++)
    {
        insertAtEnd(&head, i);
    }

    // displayForward(head);

    delete(&head, 1);

    displayForward(head);

    return 0;
}

// FUNC: create's a node in memory
node *createNode(int data) {

    // creates new node by allocating memory for it
    node *newNode = malloc(sizeof(node));
    newNode->data = data; // assign data to num provided in argument
    
    // singular node created, so next and prev points to nothing
    newNode->next = NULL; 
    newNode->prev = NULL;

    return newNode;
}

// FUNC: creates a node, inserts the node at the START of LL
void insertAtStart(node **head, int data) {
    node *newNode = createNode(data); // creates a new node

    // HELP: *head = address of a node, stored in the head variable

    // whatever node head WAS pointing to (either a node, or NULL), newNode points forward to that now
    newNode->next= *head;

    // if head WAS pointing to a NODE
    if (*head != NULL) {
        (*head)->prev = newNode; // that NODE's (the one head WAS pointing to) points backwards to the NEW NODE
    }

    // update head to point to the new node, finishing the node prepending process
    *head = newNode;
}

// FUNC: creates a node, inserts the node at END of LL
void insertAtEnd(node **head, int data) {
    node *newNode = createNode(data); // creates a new node
    
    node *current = *head; // starts at the beginning of the linked list

    // if head points to nothing (if LL is currently EMPTY)
    if (*head == NULL) {
        *head = newNode; // make head point to the new node
        return;
    }

    // going through the LL
    while (current->next != NULL) { // while next node is NOT null (aka we are NOT at the last node)
        current = current->next; // reassign current to the next node
    }

    // current points forward to new node, new node points backwards to current. New node is appended to LL 
    current->next = newNode;
    newNode->prev = current;
}

void displayBackward(node *head) {
    node *current = head; // starts at the head

    // traverses the list until the last node
    while (current->next != NULL) {
        current = current->next;
    }

    printf("DLL in reverse order: ");

    // while going backwards in the list, and while the next node is not NULL (aka NOT end of list)
    while (current != NULL) {
        printf("%i <- ", current->data);
        current = current->prev; // move to the next (previous direction) node
    }
    printf("NULL\n");
}

void displayForward(node *head) {
    node *current = head; // starts at first node

    printf("DLL in forward order: ");
    
    // going forward in list, while next node is not null (aka NOT end of list)
    while (current != NULL) {
        printf("%i -> ", current->data); 
        current = current->next; // move to next node
    }
    printf("NULL\n");
}

void reverse(node **head) {
    node *temp = NULL;
    node *current = *head; // current node = node pointed to by head

    // going through the list, while the node isn't NULL (aka NOT end of list)
    while (current != NULL) {
        temp = current->prev; // store the previous node pointed to in temp variable
        
        // swap the next and previous pointers
        current->prev = current->next;
        current->next = temp;

        current = current->prev; // move to the next sequential node in the list (via the previous pointer, which we just updated)
    }

    // change head to point to the new list's beginning (end of the former list)
    if (temp != NULL) {
        *head = temp->prev;
    }
}

void delete(node **head, int del) {
    node *current  = *head;

    while (current != NULL) {
        // if the num to be deleted is found in the node
        if (current->data == del) {
            // if head node is being deleted
            if (current->prev == NULL) {

                printf("");
                // make head point to what the node is pointing forward to
                *head = current->next;

                // make node point forward to NOTHING
                current->next = NULL;

                // make the next node  point backwards to what current node WAS pointing backwards to (NULL, because its the head node)
                (*head)->prev = NULL;
                
                // frees the current node, deleting it
                free(current);
            }

            
            break; // break out of loop searching for correct node
        }

        // if the num to be deleted is NOT found in current node, move to the next node
        current = current->next;
    }

    
    // if it's the last node:
    if (current->next == NULL) {
        current->prev->next = NULL;
    }
        // make the previous node point forward to null
        // make the current node point backwards to NOTHING
    // if it's any other node:
        // make the previous node point forwards to the next node
        // make the next node point backwards to the previous node
        // make the current node point fowards and backwards to NOTHING
}