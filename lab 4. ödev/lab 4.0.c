#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[50];
    struct Song* next;
    struct Song* prev;
} Song;

void addSongToEnd(Song** head, char* name) {
    Song* yeniSarki = (Song*)malloc(sizeof(Song));
    strcpy(yeniSarki->name, name);
    yeniSarki->next = NULL;
    
    if (*head == NULL) {
        yeniSarki->prev = NULL;
        *head = yeniSarki;
        return;
    }
    
    Song* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = yeniSarki;
    yeniSarki->prev = temp;
}

void removeSong(Song** head, char* name) {
    if (*head == NULL) {
        printf("Liste bos!\n");
        return;
    }
    
    Song* temp = *head;
    
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Sarki bulunamadi.\n");
        return;
    }
    
    if (temp == *head) {
        *head = temp->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } 

    else {
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        }
    }
    
    free(temp);
    printf("'%s' silindi.\n", name);
}

void playNext(Song** current) {
    if (*current != NULL && (*current)->next != NULL) {
        *current = (*current)->next;
        printf("Su an calan: %s\n", (*current)->name);
    } else {
        printf("Son sarkidasiniz!\n");
    }
}

void playPrevious(Song** current) {
    if (*current != NULL && (*current)->prev != NULL) {
        *current = (*current)->prev;
        printf("Su an calan: %s\n", (*current)->name);
    } else {
        printf("Ilk sarkidasiniz!\n");
    }
}

int main(void) {
    Song* head = NULL;
    Song* current = NULL;
    char input[64];
    char name[50];
    int choice;

    while (1) {
        printf("\n1. Sarki ekle\n2. Sarki sil\n3. Sonraki sarki\n");
        printf("4. Onceki sarki\n5. Calma listesini goster\n0. Cikis\nSeciminiz: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        choice = (int)strtol(input, NULL, 10);

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            printf("Sarki adi: ");
            if (fgets(name, sizeof(name), stdin) == NULL) {
                break;
            }
            name[strcspn(name, "\n")] = '\0';
            if (name[0] != '\0') {
                addSongToEnd(&head, name);
                if (current == NULL) {
                    current = head;
                }
            }
        } else if (choice == 2) {
            Song* target = NULL;
            printf("Silinecek sarki adi: ");
            if (fgets(name, sizeof(name), stdin) == NULL) {
                break;
            }
            name[strcspn(name, "\n")] = '\0';
            for (Song* song = head; song != NULL; song = song->next) {
                if (strcmp(song->name, name) == 0) {
                    target = song;
                    break;
                }
            }
            if (target != NULL && target == current) {
                current = target->next != NULL ? target->next : target->prev;
            }
            removeSong(&head, name);
        } else if (choice == 3) {
            playNext(&current);
        } else if (choice == 4) {
            playPrevious(&current);
        } else if (choice == 5) {
            Song* song = head;
            if (song == NULL) {
                printf("Calma listesi bos.\n");
            }
            while (song != NULL) {
                printf("%s%s\n", song == current ? "> " : "  ", song->name);
                song = song->next;
            }
        } else {
            printf("Gecersiz secim.\n");
        }
    }

    while (head != NULL) {
        Song* next = head->next;
        free(head);
        head = next;
    }
    return 0;
}