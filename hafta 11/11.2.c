#include <stdio.h>

#define N 6
#define INF 999999

char isim[N] = {'A', 'B', 'C', 'D', 'E', 'F'};
int matris[N][N];

void kenar_ekle(int u, int v, int w) {
    matris[u][v] = w;
    matris[v][u] = w; // yonsuz graf
}

int dugum_indeksi(char c) {
    if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
    for (int i = 0; i < N; i++) {
        if (isim[i] == c) return i;
    }
    return -1;
}

void yol_yazdir(int yol[], int hedef) {
    if (hedef == -1) return;
    if (yol[hedef] == -1) {
        printf("%c", isim[hedef]);
        return;
    }
    yol_yazdir(yol, yol[hedef]);
    printf(" -> %c", isim[hedef]);
}

// Her dugumun toplam en kisa mesafesini (veya agac maliyetini) dondurur
int dijkstra(int kok, int tablo_yazdir, int rota_ozel) {
    int known[N] = {0};
    int dist[N];
    int yol[N];

    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        yol[i] = -1;
    }
    dist[kok] = 0;

    for (int adim = 0; adim < N; adim++) {
        int u = -1;
        int min_d = INF;

        for (int i = 0; i < N; i++) {
            if (!known[i] && dist[i] < min_d) {
                min_d = dist[i];
                u = i;
            }
        }

        if (u == -1) break;
        known[u] = 1;

        for (int v = 0; v < N; v++) {
            if (matris[u][v] > 0 && !known[v]) {
                if (dist[u] + matris[u][v] < dist[v]) {
                    dist[v] = dist[u] + matris[u][v];
                    yol[v] = u;
                }
            }
        }

        // 1. Her adimda Known, Distance ve Path tablosunu guncelleyip yazdir
        if (tablo_yazdir) {
            printf("\n--- Adim %d (Secilen: %c) ---\n", adim + 1, isim[u]);
            printf("Dugum | Known | Distance | Path\n");
            for (int i = 0; i < N; i++) {
                char p = (yol[i] != -1) ? isim[yol[i]] : '-';
                if (dist[i] >= INF) {
                    printf("  %c   |   %d   |   INF    |  %c\n", isim[i], known[i], p);
                } else {
                    printf("  %c   |   %d   |    %2d    |  %c\n", isim[i], known[i], dist[i], p);
                }
            }
        }
    }

    // 2. Kok A secildiginde B ve D'ye en dusuk maliyetli yollar
    if (rota_ozel) {
        int b_idx = 1; // B
        int d_idx = 3; // D

        printf("\n=== Kok A icin B ve D Rotalari ===\n");
        printf("A -> B Maliyet: %d | Rota: ", dist[b_idx]);
        yol_yazdir(yol, b_idx);
        printf("\n");

        printf("A -> D Maliyet: %d | Rota: ", dist[d_idx]);
        yol_yazdir(yol, d_idx);
        printf("\n");
    }

    // Kokten diger dugumlere olan en kisa yollarin toplam maliyeti
    int toplam = 0;
    for (int i = 0; i < N; i++) {
        if (dist[i] < INF) {
            toplam += dist[i];
        }
    }
    return toplam;
}

int main() {
    // Kenar listesi
    kenar_ekle(0, 1, 7); // A - B : 7
    kenar_ekle(0, 2, 5); // A - C : 5
    kenar_ekle(0, 5, 1); // A - F : 1
    kenar_ekle(1, 2, 1); // B - C : 1
    kenar_ekle(1, 3, 1); // B - D : 1
    kenar_ekle(1, 4, 3); // B - E : 3
    kenar_ekle(2, 3, 2); // C - D : 2
    kenar_ekle(2, 4, 1); // C - E : 1
    kenar_ekle(3, 5, 7); // D - F : 7
    kenar_ekle(4, 5, 2); // E - F : 2

    // 1. Kullanicidan kok dugum alip adim adim tablo yazdir
    char giris;
    printf("Kok dugumu girin (A-F): ");
    scanf(" %c", &giris);

    int kok = dugum_indeksi(giris);
    if (kok == -1) {
        printf("Gecersiz dugum, varsayilan olarak A secildi.\n");
        kok = 0;
    }

    dijkstra(kok, 1, 0);

    // 2. Kok A icin B ve D rotalari
    dijkstra(0, 0, 1);

    // 3. Tum dugumleri (A-F) kok yaparak merkezi dugumu bul
    printf("\n=== Merkezi Dugum Analizi ===\n");
    int en_merkezi = 0;
    int en_dusuk_toplam = INF;

    for (int i = 0; i < N; i++) {
        int top = dijkstra(i, 0, 0);
        printf("Kok %c -> Toplam maliyet: %d\n", isim[i], top);
        if (top < en_dusuk_toplam) {
            en_dusuk_toplam = top;
            en_merkezi = i;
        }
    }

    printf("\nEn merkezi dugum: %c (Toplam maliyet: %d)\n", isim[en_merkezi], en_dusuk_toplam);

    return 0;
}