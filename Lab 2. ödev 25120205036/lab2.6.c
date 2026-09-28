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

    head -> data = 10 ; head -> next = n2;
    n2 -> data = 20 ; n2 -> next = n3;
    n3 -> data = 30 ; n3 -> next = n4;
    n4 -> data = 40 ; n4 -> next = NULL;

    int a,b = 0;
    printf("aranacak bir sayi giriniz;");
    scanf("%d",&a);

    struct Node *current = head;
    while(current != NULL){
        if(current->data == a){
            b = 1;
            break;
        }
        current = current -> next;
    }

    if(b){
        printf("sayi listede bulundu.\n");
    }else{
        printf("sayi listede yok.\n");
    }
    
    free(head); free(n2); free(n3); free(n4);

    return 0;
}