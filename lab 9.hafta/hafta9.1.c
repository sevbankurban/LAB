#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

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

int balanceFactor(Node *n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

// Sağa Rotasyon (LL durumu için)
Node* rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Sola Rotasyon (RR durumu için)
Node* rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Genel AVL Ekleme Fonksiyonu (Dört Rotasyonu Destekler)
Node* insertAVL(Node* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = balanceFactor(node);

    // 1. LL Durumu
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // 2. RR Durumu
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // 3. LR Durumu
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // 4. RL Durumu
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void preorder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void runTest(const char* testName, int arr[], int n) {
    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        root = insertAVL(root, arr[i]);
    }
    printf("%s -> Kok: %d | Preorder: ", testName, root->key);
    preorder(root);
    printf("\n");
}

int main() {
    int testA[] = {30, 20, 10};
    int testB[] = {10, 20, 30};
    int testC[] = {30, 10, 20};
    int testD[] = {10, 30, 20};

    runTest("Test A (LL)", testA, 3);
    runTest("Test B (RR)", testB, 3);
    runTest("Test C (LR)", testC, 3);
    runTest("Test D (RL)", testD, 3);

    return 0;
}