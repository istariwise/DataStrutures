/*程式說明
addq 與 deleteq:

使用環狀佇列來實作，保證佇列不會因為線性增長而溢出。
addq 負責將節點加入佇列，deleteq 負責從佇列中取出節點。
走訪邏輯:

根節點加入佇列，然後逐層遍歷。
每取出一個節點時，將其左、右子節點（若存在）加入佇列。
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct node *treePointer;

typedef struct node {
    int data;
    treePointer leftChild, rightChild;
} Node;

treePointer queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

// 添加節點到佇列
void addq(treePointer element) {
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if (front == rear) {
        printf("Queue overflow\n");
        exit(EXIT_FAILURE);
    }
    queue[rear] = element;
}

// 從佇列取出節點
treePointer deleteq() {
    if (front == rear) {
        return NULL; // 佇列為空
    }
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}

// 階序走訪函式（並釋放節點記憶體）
void levelOrder(treePointer ptr) {
    if (!ptr) return; // 空樹直接返回

    addq(ptr); // 將根節點加入佇列

    while (1) {
        ptr = deleteq(); // 從佇列取出節點
        if (!ptr) break; // 若佇列空則結束

        printf("%d ", ptr->data); // 輸出節點資料

        // 如果有左或右子節點，加入佇列
        if (ptr->leftChild) addq(ptr->leftChild);
        if (ptr->rightChild) addq(ptr->rightChild);

        // 釋放該節點的記憶體
        free(ptr);
    }
}

// 建立新節點
treePointer createNode(int data) {
    treePointer newNode = (treePointer)malloc(sizeof(Node));
    newNode->data = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

// 測試主程式
int main() {
    // 建立樹的結構
    treePointer root = createNode(1);
    root->leftChild = createNode(2);
    root->rightChild = createNode(3);
    root->leftChild->leftChild = createNode(4);
    root->leftChild->rightChild = createNode(5);
    root->rightChild->leftChild = createNode(6);
    root->rightChild->rightChild = createNode(7);

    printf("Level Order Traversal: ");
    levelOrder(root); // 呼叫階序走訪
    printf("\n");

    return 0;
}
