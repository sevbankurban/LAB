#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hasta{
    int id;
    char name[50];
    char state[50];
    struct Hasta *next;
} Hasta;

typedef struct {
    Hasta *head;
    Hasta *tail;
}Queue;

typedef struct{
    Hasta* top;
}Stack;

typedef struct{
    Hasta* head;
}PastList;

void startQueue(Queue *q){
    q->head = NULL;
    q->tail = NULL;
}

void startStack(Stack *s){
    s -> top = NULL;
}

void startPastList(PastList *p){
    p -> head = NULL;
}

void enqueue (Queue *q, int id, const char name[])
{
    Hasta *newHasta = (Hasta*)malloc(sizeof(Hasta));
    newHasta -> id = id;
    strcpy (newHasta -> name, name);
    strcpy(newHasta->state, "waiting");
    newHasta -> next =NULL;

    if (q -> head == NULL){
        q -> head = newHasta;
        q -> tail = newHasta;
    }
    else{
        q -> tail ->  next = newHasta;
        q -> tail = newHasta;
    }
    printf("Patient %s with ID %d has been added to the queue.\n", name, id);
}

Hasta* dequeue(Queue *q){
    if (q -> head == NULL){
        printf("The queue is empty. No patient to dequeue.\n");
        return NULL;
    }
    Hasta* dequeued = q -> head;
    q -> head = q -> head -> next;
    if (q -> head == NULL){
        q -> tail = NULL;
    }
    dequeued -> next = NULL;
    return dequeued;
}

void push(Stack *s , Hasta *hasta){
    strcpy(hasta -> state, "in treatment");
    hasta -> next = s -> top;
    s -> top = hasta;
    printf("Patient %s with ID %d has been pushed to the stack for treatment.\n", hasta -> name, hasta -> id);
}

Hasta *pop(Stack *s){
    if (s -> top == NULL){
        printf("THe stack is empty. No patient to pop.\n");
        return NULL;
    }
    Hasta* popped = s -> top;
    s -> top = s -> top -> next;
    popped -> next = NULL;
    return popped;
}

void addToPastList(PastList *p, Hasta *hasta){
    hasta -> next = NULL;
    if (p -> head == NULL){
        p -> head = hasta;
    }
    else{
        
        Hasta *current = p -> head;
        while (current -> next != NULL){
            current = current -> next;
        }
        current -> next = hasta;
    }
    printf("Patient %s with ID %d has been added to the past list.\n", hasta -> name, hasta -> id);
}

void waitingPatients(Queue *q){
    printf("---------------Waiting Patients----------------\n");
    Hasta *current = q -> head;
    if (current == NULL){
        printf("No patients are waiting.\n");
        return;
    }
    while (current != NULL){
        printf("Patient ID: %d, Name: %s, State: %s\n", current -> id, current -> name, current -> state);
        current = current -> next;
    }
}

void inTreatmentPatients(Stack *s){
    printf("---------------In Treatment Patients----------------\n");
    Hasta *current = s -> top;
    if (current == NULL){
        printf("No patients are in treatment.\n");
        return;
    }
    while (current != NULL){
        printf("Patient ID: %d, Name: %s, State: %s\n", current -> id, current -> name, current -> state);
        current = current -> next;
    }
}

void pastPatients(PastList *p){
    printf("---------------Past Patients----------------\n");
    Hasta *current = p -> head;
    if (current == NULL){
        printf("No patients have been treated yet.\n");
        return;
    }
    while (current != NULL){
        printf("Patient ID: %d, Name: %s, State: %s\n", current -> id, current -> name, current -> state);
        current = current -> next;
    }
}

int main() {
    Queue queue;
    Stack stack;
    PastList pastList;

    startQueue(&queue);
    startStack(&stack);
    startPastList(&pastList);

int secim, id;
    char ad[50];

    do {
        printf("\n=========================================\n");
        printf("       HASTANE HASTA TAKIP SISTEMI       \n");
        printf("=========================================\n");
        printf("1. Yeni Hasta Ekle (Enqueue)\n");
        printf("2. Hastayi Muayeneye Al (Dequeue -> Push)\n");
        printf("3. Muayeneyi Tamamla (Pop -> Gecmis Listesi)\n");
        printf("4. Bekleyen Hastalari Listele (Kuyruk)\n");
        printf("5. Muayene Odasindakileri Listele (Yigin)\n");
        printf("6. Gecmis Kayitlari Listele (Bagli Liste)\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                printf("Hasta ID: ");
                scanf("%d", &id);
                printf("Hasta Adi: ");
                scanf("%s", ad);
                enqueue(&queue, id, ad);
                break;
            case 2: {
                Hasta* alinan = dequeue(&queue);
                if (alinan != NULL) {
                    push(&stack, alinan);
                }
                break;
            }
            case 3: {
                Hasta* tamamlanan = pop(&stack);
                if (tamamlanan != NULL) {
                    addToPastList(&pastList, tamamlanan);
                }
                break;
            }
            case 4:
                waitingPatients(&queue);
                break;
            case 5:
                inTreatmentPatients(&stack);
                break;
            case 6:
                pastPatients(&pastList);
                break;
            case 0:
                printf("Programdan cikiliyor...\n");
                break;
            default:
                printf("Gecersiz secim, tekrar deneyin!\n");
        }
    } while (secim != 0);

    return 0;
}
