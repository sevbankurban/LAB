#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void insertAt(Node** head, int value, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (position <= 0 || *head == NULL) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* current = *head;
    int currentIndex = 0;

    while (current->next != NULL && currentIndex < position - 1) {
        current = current->next;
        currentIndex++;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void deleteAt(Node** head, int position) {
    if (*head == NULL || position < 0) return;

    Node* temp = *head;

    if (position == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    Node* current = *head;
    int currentIndex = 0;

    while (current->next != NULL && currentIndex < position - 1) {
        current = current->next;
        currentIndex++;
    }

    if (current->next == NULL) {
        return; 
    }

    Node* nodeToDelete = current->next;
    current->next = nodeToDelete->next;
    free(nodeToDelete);
}

void clear(Node** head) {
    Node* current = *head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int main() {
    Node* head = NULL;

    insertAt(&head, 10, 0); 
    insertAt(&head, 20, 1); 
    insertAt(&head, 30, 2); 
    insertAt(&head, 15, 1); 
    
    printf("Baslangic Listesi:\n");
    printList(head);

    deleteAt(&head, 1);
    printf("1. indis silindikten sonra:\n");
    printList(head);

    clear(&head);
    return 0;
}