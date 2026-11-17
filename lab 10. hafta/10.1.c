#include <stdio.h>
#include <stdlib.h>

#define V 5 

const char* sehirler[V] = {"istanbul", "ankara", "bursa", "antalya", "izmir"};

void shortestPathBfs(int graph[V][V], int start, int target) {
    int visited[V] = {0};
    int parent [V]; // kimin üzerinden geldiğini tutar.
    int queue[V];
    int front = 0, rear = 0;

    for (int i = 0; i < V; i++) parent[i] = -1;

    visited[start] = 1;
    queue[rear++] = start;

    int found = 0;

    
    while (front < rear) {
        int current = queue[front++];

        if(current == target) {
            found = 1;
            break;
        }
        
        for (int i = 0; i < V; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                parent[i] = current; //nereden geldiğini kaydet;
                queue[rear++] = i;
            }
        }
    }

    printf("\n===========================================\n");
    printf("\n NAVIGASYON SISTEMI GIRIS (BFS ROTA BULUCU)\n");
    printf("\n===========================================\n");

    if (found){
        //rotayı tersten yazdırmak için dizi kullanırız.

        int path[V];
        int count = 0;
        int curr = target;

        while (curr != -1){
            path[count++] = curr;
            curr = parent[curr];
        }

        printf("hedefe ulasildi.");
        for( int i = count -1 ; i >= 0; i--){
            printf("%s", sehirler[path[i]]);
            if ( i > 0) printf (" -> ");
        }
        printf("\n");
    }else {
        printf("hedefe giden yol bulunamadi.");
    }
    printf("===================================================\n");
}

int main() {
    int graph[V][V] = {
        {0, 1, 0, 1, 0}, // istanbul
        {1, 0, 1, 0, 1}, // ankara
        {0, 1, 0, 0, 0}, // izmir
        {1, 0, 0, 0, 1}, // bursa 
        {0, 1, 0, 1, 0}  // antalya
    };

    int baslangic, hedef;

    printf("\n=== SEHIR ICIN SECIM EKRANI ===\n");
    for(int i = 0; i < V; i++){
        printf("[%d] %s\n", i, sehirler[i]);
    }
    printf("=============================================================\n");

    printf("baslangic sehrin numarasini giriniz.(0 - 4):" );
    scanf("%d", &baslangic);

    printf("gidelecek sehrin numarasini giriniz.(0 - 4):" );
    scanf("%d", &hedef);

    if(baslangic < 0 || baslangic >= V || hedef < 0 ||  hedef >= V){
        printf("\n !!!HATA!!! \nLutfen uygun degerler giriniz.");
    }else{
        shortestPathBfs(graph, baslangic, hedef);
    }

    return 0;
}