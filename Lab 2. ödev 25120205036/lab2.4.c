#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

int main(){

    struct Node *head = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n3 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n4 = (struct Node*)malloc(sizeof(struct Node));

    head->data = 10; head->next = n2;
    n2->data = 20; n2->next = n3;
    n3->data = 30; n3->next = n4;
    n4->data = 40; n4->next =NULL;
    int count = 0;
    struct Node *current = head;

    while(current != NULL) {
        count++;
        current = current->next;
    }

    printf("listede %d kadar Node eleman var",count);

    free(head); free(n2); free(n3); free(n4);

    return 0;
}

