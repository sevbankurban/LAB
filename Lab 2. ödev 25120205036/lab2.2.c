#include <stdio.h>

struct Node{
    int data;
    struct Node *next;
};

int main(){
    
    struct Node node1, node2, node3;

    node1.data = 10;
    node1.next = &node2;

    node2.data = 20;
    node2.next = &node3;

    node3.data = 30;
    node3.next = NULL;

    struct Node *current = &node1;  

    printf("Liste elemalari: ");
    while(current != NULL){
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    return 0;
}