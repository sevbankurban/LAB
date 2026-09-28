#include <stdio.h>

struct Node{
    int data;
    struct Node *next;
};


int main(){

    struct Node node1, node2;

    node1.data = 10;
    node1.next = &node2;

    node2.data = 20;    
    node2.next = NULL;

    printf("1. node: %d\n",node1.data);
    printf("2. node degeri (1. node uzerinden):%d\n",node1.next->data);

    return 0;
}