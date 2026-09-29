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

Node* findMiddle(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow; 
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

    Node* n1 = (Node*)malloc(sizeof(Node)); n1->data = 10;
    Node* n2 = (Node*)malloc(sizeof(Node)); n2->data = 20;
    Node* n3 = (Node*)malloc(sizeof(Node)); n3->data = 30;
    Node* n4 = (Node*)malloc(sizeof(Node)); n4->data = 40;
    Node* n5 = (Node*)malloc(sizeof(Node)); n5->data = 50;

    head = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = NULL;

    printf("Liste: ");
    printList(head);

    Node* orta = findMiddle(head);
    if (orta != NULL) {
        printf("Ortadaki dugumun degeri: %d\n", orta->data);
    } else {
        printf("Liste bos.\n");
    }

    clear(&head);
    return 0;
}