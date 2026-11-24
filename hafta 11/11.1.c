#include <stdio.h>

#define N 6

int adj[N + 1][N + 1];

void kenar_ekle(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;
}

void grafi_incele(const char *baslik) {
    int i, j;
    int derece[N + 1] = {0};
    int max_derece = 0;

    printf("\n=== %s ===\n", baslik);

    // 1. Komsuluk matrisi
    printf("\nKomsuluk Matrisi:\n");
    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    // 2. Dugum dereceleri ve genel derece
    printf("\nDugum Dereceleri:\n");
    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            derece[i] += adj[i][j];
        }
        printf("Dugum %d: %d\n", i, derece[i]);
        if (derece[i] > max_derece) {
            max_derece = derece[i];
        }
    }
    printf("Grafin genel derecesi (max): %d\n", max_derece);

    // 3. BFS ile bipartite kontrolu (1. dugum -> 0)
    int renk[N + 1];
    int kuyruk[N + 5];
    int bas = 0, son = 0;
    int bipartite = 1;

    for (i = 1; i <= N; i++) {
        renk[i] = -1;
    }

    renk[1] = 0;
    kuyruk[son++] = 1;

    while (bas < son) {
        int u = kuyruk[bas++];
        for (j = 1; j <= N; j++) {
            if (adj[u][j] == 1) {
                if (renk[j] == -1) {
                    renk[j] = 1 - renk[u];
                    kuyruk[son++] = j;
                } else if (renk[j] == renk[u]) {
                    bipartite = 0;
                }
            }
        }
    }

    printf("\nDugum Renk / Parite Degerleri:\n");
    for (i = 1; i <= N; i++) {
        printf("Dugum %d -> %d (%s)\n", i, renk[i], renk[i] == 0 ? "Cift" : "Tek");
    }

    if (bipartite) {
        printf("Sonuc: Graf Bipartite (Iki Parcali).\n");
    } else {
        printf("Sonuc: Graf Bipartite DEGIL (ayni renge sahip komsu dugum var).\n");
    }
}

int main() {
    // E = {(1, 2), (1, 4), (2, 3), (3, 4), (3, 6), (4, 5), (5, 6)}
    kenar_ekle(1, 2);
    kenar_ekle(1, 4);
    kenar_ekle(2, 3);
    kenar_ekle(3, 4);
    kenar_ekle(3, 6);
    kenar_ekle(4, 5);
    kenar_ekle(5, 6);

    grafi_incele("Ilk Graf");

    // 4. Dinamik test: (2, 4) kenari ekleniyor
    kenar_ekle(2, 4);
    grafi_incele("(2, 4) Eklendikten Sonra");

    return 0;
}