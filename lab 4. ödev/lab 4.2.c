#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PrintJob {
    char fileName[50];
    struct PrintJob* next;
} PrintJob;

typedef struct Queue {
    PrintJob* front;
    PrintJob* rear;
} Queue;

void enqueuePrintJob(Queue* q, char* fileName);
void processNextJob(Queue* q);
void showQueue(Queue q);

void enqueuePrintJob(Queue* q, char* fileName) {
    PrintJob* yeniIs = (PrintJob*)malloc(sizeof(PrintJob));
    if (yeniIs == NULL) {
        printf("Bellek ayrilamadi!\n");
        return;
    }
    strcpy(yeniIs->fileName, fileName);
    yeniIs->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = yeniIs;
    } else {
        q->rear->next = yeniIs;
        q->rear = yeniIs;
    }
    printf("'%s' kuyruga basariyla eklendi.\n", fileName);
}

void processNextJob(Queue* q) {
    if (q->front == NULL) {
        printf("Uyari: Kuyruk bos, yazdirilacak dosya yok!\n");
        return;
    }

    PrintJob* temp = q->front;
    printf("Yazdiriliyor... -> %s\n", temp->fileName);

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
}

void showQueue(Queue q) {
    if (q.front == NULL) {
        printf("Yazici kuyrugu bos.\n");
        return;
    }

    PrintJob* temp = q.front;
    printf("\n--- Aktif Yazici Kuyrugu ---\n");
    int sira = 1;
    while (temp != NULL) {
        printf("%d. Dosya: %s\n", sira++, temp->fileName);
        temp = temp->next;
    }
    printf("-----------------------------\n");
}

int main() {
    Queue q;
    q.front = NULL;
    q.rear = NULL;

    int secim;
    char dosyaAdi[50];

    while (1) {
        printf("\n--- YAZICI KUYRUK SIMULASYONU ---\n");
        printf("1) Yeni dosya ekle\n");
        printf("2) Yazdir\n");
        printf("3) Kuyrugu goster\n");
        printf("4) Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        if (secim == 1) {
            printf("Yazdirilacak dosya adini girin: ");
            scanf("%s", dosyaAdi);
            enqueuePrintJob(&q, dosyaAdi);
        } 
        else if (secim == 2) {
            processNextJob(&q);
        } 
        else if (secim == 3) {
            showQueue(q);
        } 
        else if (secim == 4) {
            while (q.front != NULL) {
                PrintJob* temp = q.front;
                q.front = q.front->next;
                free(temp);
            }
            printf("Programdan cikiliyor...\n");
            break;
        } 
        else {
            printf("Gecersiz secim! Lutfen 1-4 arasinda bir deger girin.\n");
        }
    }

    return 0;
}