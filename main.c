#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
    struct Node *prev;
} Node;

void insert(Node **head, char *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = strdup(data);
    newNode->next = *head;
    newNode->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

Node* find(Node *head, char *data) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void delete(Node **head, char *data) {
    Node *current = *head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                *head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current->data);
            free(current);
            return;
        }
        current = current->next;
    }
}

int main() {
    printf("Hello, World!\n");

    Node *head = NULL;

    //test insert function
    insert(&head, "Bulbasaur");
    insert(&head, "Charmander");
    insert(&head, "Squirtle");

    //test find function
    Node *found = find(head, "Charmander");
    if (found != NULL) {
        printf("Found: %s\n", found->data);
    }

    //test delete function
    delete(&head, "Charmander");
    found = find(head, "Charmander");
    if (found == NULL) {
        printf("Charmander was deleted.\n");
    }
    return 0;
}