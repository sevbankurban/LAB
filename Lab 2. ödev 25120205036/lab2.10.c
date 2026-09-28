#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

// 1. Tüm listeyi gösteren fonksiyon (display)
void display(struct Node *head) {
    struct Node *current = head;
    printf("Liste: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 2. Listenin başına eleman ekleyen fonksiyon (insertBeginning)
void insertBeginning(struct Node **head, int yeniDeger) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = yeniDeger;
    newNode->next = *head;
    *head = newNode;
}

// 3. Eleman arayan fonksiyon (search)
void search(struct Node *head, int aranan) {
    struct Node *current = head;
    int index = 0;
    while (current != NULL) {
        if (current->data == aranan) {
            printf("%d degeri listede bulundu! (Dugum sirasi: %d)\n", aranan, index + 1);
            return;
        }
        current = current->next;
        index++;
    }
    printf("%d degeri listede bulunamadi.\n", aranan);
}

int main() {
    struct Node *head = NULL;

    // Fonksiyonları test etme
    insertBeginning(&head, 30);
    insertBeginning(&head, 20);
    insertBeginning(&head, 10);

    display(head);

    search(head, 20);
    search(head, 99);

    return 0;
}