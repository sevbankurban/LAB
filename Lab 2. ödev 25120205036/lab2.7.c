#include <stdio.h>
#include <stdlib.h>

struct Node{
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

int main (){

    struct Node *head = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n3 = (struct Node*)malloc(sizeof(struct Node));

    head -> data = 10; head -> next = n2;
    n2 -> data = 20; n2 -> next = n3;
    n3 -> data =30; n3 -> next = NULL;

    printf("yeni eleman eklemeden once:\n");
    yazdir(head);

    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode -> data = 5; newNode -> next = head;
    head = newNode;

    printf("yeni eleman ekledikten sonra:\n");
    yazdir(head);
    

    return 0;
}