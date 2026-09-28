#include <stdio.h>

struct Node{
    int data;
    struct Node *next;
};


int main(){

    struct Node node1;
    node1.data = 10;
    node1.next = NULL;

    printf("Node degeri:%d",node1.data);
    
    return 0;
}