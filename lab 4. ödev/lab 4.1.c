#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char text[50];
    struct Word* next;
} Word;

void pushWord(Word** top, char* text) {
    Word* yeniKelime = (Word*)malloc(sizeof(Word));
    if (yeniKelime == NULL) {
        printf("Bellek hatasi!\n");
        return;
    }
    strcpy(yeniKelime->text, text);
    yeniKelime->next = *top;
    *top = yeniKelime;
    printf("Eklendi: %s\n", text);
}

void popWord(Word** top) {
    if (*top == NULL) {
        printf("Geri alinacak kelime yok (Metin zaten bos)!\n");
        return;
    }
    
    Word* temp = *top;
    *top = (*top)->next;
    printf("Geri alindi (Silindi): %s\n", temp->text);
    free(temp);
}

void showRecursive(Word* top) {
    if (top == NULL) {
        return;
    }
    showRecursive(top->next);
    printf("%s ", top->text);
}

void showWords(Word* top) {
    printf("> show -> ");
    if (top == NULL) {
        printf("(Bos)\n");
        return;
    }
    showRecursive(top);
    printf("\n");
}

int main() {
    Word* top = NULL;
    int secim;
    char kelime[50];

    while (1) {
        printf("\n--- METIN DUZENLEYICI (UNDO SIMULASYONU) ---\n");
        printf("1. Kelime Ekle (add)\n");
        printf("2. Geri Al (undo)\n");
        printf("3. Kelimeleri Goster (show)\n");
        printf("4. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        if (secim == 1) {
            printf("Eklenecek kelimeyi girin: ");
            scanf("%s", kelime);
            pushWord(&top, kelime);
        } 
        else if (secim == 2) {
            popWord(&top);
        } 
        else if (secim == 3) {
            showWords(top);
        } 
        else if (secim == 4) {
            while (top != NULL) {
                Word* temp = top;
                top = top->next;
                free(temp);
            }
            printf("Programdan cikiliyor...\n");
            break;
        } 
        else {
            printf("Gecersiz secim! Tekrar deneyin.\n");
        }
    }

    return 0;
}