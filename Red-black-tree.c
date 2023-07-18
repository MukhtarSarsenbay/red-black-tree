//red black tree, adding new element
#include <stdio.h>
#include <stdlib.h>

// Структура для представления узла в красно-черном дереве
struct Node {
    int data;              // Значение узла
    int color;             // Цвет узла (0 - черный, 1 - красный)
    struct Node* parent;   // Родительский узел
    struct Node* left;     // Левый дочерний узел
    struct Node* right;    // Правый дочерний узел
};

// Создание нового узла
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = 1;  // При вставке нового узла он всегда будет красным
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Поворот влево
void leftRotate(struct Node** root, struct Node* node) {
    struct Node* rightChild = node->right;
    node->right = rightChild->left;

    if (node->right != NULL)
        node->right->parent = node;

    rightChild->parent = node->parent;

    if (node->parent == NULL)
        *root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
}

// Поворот вправо
void rightRotate(struct Node** root, struct Node* node) {
    struct Node* leftChild = node->left;
    node->left = leftChild->right;

    if (node->left != NULL)
        node->left->parent = node;

    leftChild->parent = node->parent;

    if (node->parent == NULL)
        *root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
}

// Вспомогательная функция для поддержания свойств красно-черного дерева после вставки
void fixInsert(struct Node** root, struct Node* node) {
    while (node != *root && node->parent->color == 1) {
        if (node->parent == node->parent->parent->left) {
            struct Node* uncle = node->parent->parent->right;
            
            if (uncle != NULL && uncle->color == 1) {
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(root, node);
                }
                
                node->parent->color = 0;
                node->parent->parent->color = 1;
                rightRotate(root, node->parent->parent);
            }
        } else {
            struct Node* uncle = node->parent->parent->left;

            if (uncle != NULL && uncle->color == 1) {
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(root, node);
                }
                
                node->parent->color = 0;
                node->parent->parent->color = 1;
                leftRotate(root, node->parent->parent);
            }
        }
    }

    (*root)->color = 0;
}

// Вставка нового узла в красно-черное дерево
void insert(struct Node** root, int data) {
    struct Node* newNode = createNode(data);
    struct Node* current = *root;
    struct Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (newNode->data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;

    if (parent == NULL)
        *root = newNode;
    else if (newNode->data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixInsert(root, newNode);
}

// Вспомогательная функция для печати красно-черного дерева
void printTree(struct Node* node) {
    if (node == NULL)
        return;

    printf("%d ", node->data);

    if (node->color == 0)
        printf("(Black) ");
    else
        printf("(Red) ");

    if (node->left != NULL)
        printf("Left child: %d, ", node->left->data);
    else
        printf("Left child: NULL, ");

    if (node->right != NULL)
        printf("Right child: %d\n", node->right->data);
    else
        printf("Right child: NULL\n");

    printTree(node->left);
    printTree(node->right);
}

int main() {
    struct Node* root = NULL;

    insert(&root, 7);
    insert(&root, 3);
    insert(&root, 18);
    insert(&root, 10);
    insert(&root, 22);
    insert(&root, 8);
    insert(&root, 11);
    insert(&root, 26);
    insert(&root, 2);
    insert(&root, 6);
    insert(&root, 13);

    printf("Красно-черное дерево после вставки новых элементов:\n");
    printTree(root);

    return 0;
}
