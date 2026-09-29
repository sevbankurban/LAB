#include <stdio.h>
#include <stdlib.h>

// Node yapısı
typedef struct Node {
    int data;
    struct Node* next;
} Node;

void addOrdered(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL || (*head)->data >= value) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL && current->next->data < value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void removeNode(Node** head, int value) {
    if (*head == NULL) return;

    Node* current = *head;
    Node* temp = NULL;

    if (current->data == value) {
        *head = current->next;
        free(current);
        return;
    }

    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }

    if (current->next != NULL) {
        temp = current->next;
        current->next = temp->next;
        free(temp);
    }
}

int count(Node* head) {
    int sayac = 0;
    Node* current = head;
    while (current != NULL) {
        sayac++;
        current = current->next;
    }
    return sayac;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void clear(Node** head) {
    Node* current = *head;
    Node* nextNode = NULL;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head = NULL;
}

int main() {
    Node* head = NULL;
    int sayilar[] = {23, 11, 5, 9, 6, 4, 12, 24};
    int n = sizeof(sayilar) / sizeof(sayilar[0]);

    for (int i = 0; i < n; i++) {
        addOrdered(&head, sayilar[i]);
    }

    printf("Sirali Liste: ");
    printList(head);
    printf("Dugum Sayisi: %d\n", count(head));

    removeNode(&head, 9);
    printf("9 silindikten sonra: ");
    printList(head);

    clear(&head);
    printf("Liste temizlendikten sonra dugum sayisi: %d\n", count(head));

    return 0;
}
