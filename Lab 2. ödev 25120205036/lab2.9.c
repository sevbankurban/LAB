#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void yazdir(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node *head = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n3 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n4 = (struct Node*)malloc(sizeof(struct Node));

    head->data = 10; head->next = n2;
    n2->data = 20;   n2->next = n3;
    n3->data = 30;   n3->next = n4;
    n4->data = 40;   n4->next = NULL;

    printf("Mevcut liste: ");
    yazdir(head);

    int silinecek;
    printf("Silmek istediginiz degeri giriniz: ");
    scanf("%d", &silinecek);

    struct Node *current = head;
    struct Node *previous = NULL;

    if (current != NULL && current->data == silinecek) {
        head = current->next;
        free(current);
        printf("%d silindi.\n", silinecek);
    } else {
        
        while (current != NULL && current->data != silinecek) {
            previous = current;
            current = current->next;
        }

        if (current == NULL) {
            printf("Silinecek deger bulunamadi.\n");
        } else {
            // Bağlantıyı kopar ve düğümü sil
            previous->next = current->next;
            free(current);
            printf("%d silindi.\n", silinecek);
        }
    }

    printf("Guncel liste: ");
    yazdir(head);

    return 0;
}