#include <stdio.h>
#include <stdlib.h>

// AVL Düğüm Yapısı
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// Yükseklik alma fonksiyonu
int height(Node *n) {
    if (n == NULL) return 0;
    return n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Denge faktörünü hesaplama (Sol - Sağ)
int balanceFactor(Node *n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

// Sola Rotasyon (RR Dengesizliği için)
Node* rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // Yeni kök
}

// Soru 1 özelinde BST ekleme ve sadece RR rotasyonu kontrolü
Node* insertBST(Node* node, int key) {
    if (node == NULL) {
        printf("%d eklendi.\n", key);
        return createNode(key);
    }

    if (key < node->key)
        node->left = insertBST(node->left, key);
    else if (key > node->key)
        node->right = insertBST(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int bf = balanceFactor(node);
    printf("%d eklendi. BF(kok)=%d\n", key, bf);

    if (bf < -1 && key > node->right->key) {
        printf("RR dengesizligi: Sol rotasyon!\n");
        return rotateLeft(node);
    }

    return node;
}

// Inorder dolaşım (Sol - Kök - Sağ)
void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Preorder dolaşım (Kök - Sol - Sağ)
void preorder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

int main() {
    Node *root = NULL;
    int keys[] = {10, 20, 30};

    for (int i = 0; i < 3; i++) {
        root = insertBST(root, keys[i]);
    }

    printf("Kok: %d\n", root->key);
    printf("Inorder: ");
    inorder(root);
    printf("\nPreorder: ");
    preorder(root);
    printf("\n");

    return 0;
}