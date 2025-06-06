#include "bi-tree.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InOrder(BiTree T) {
    // 当为空树时
    if (T == NULL) {
        return;
    }
    // 当不为空树时
    if (T->ltag == 0) {
        InOrder(T->lchild);
    }
    PrintTreeNode(T);
    if (T->rtag == 0) {
        InOrder(T->rchild);
    }
}

void PrintTreeNode(BiTNode *node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", (int)node->data);
}

void LevelOrder(BiTree T) {
    if (T == NULL) {
        return;
    }
    BiTNode *currentNode = T;
    TreeQueue queue = {0};
    InitTreeQueue(&queue);
    // 将根结点入队
    EnTreeQueue(&queue, currentNode);
    while (queue.front != NULL && queue.rear != NULL) {
        // 处理当前结点的孩子结点
        if (queue.front->treeNode->lchild != NULL &&
            queue.front->treeNode->ltag == 0) {
            EnTreeQueue(&queue, queue.front->treeNode->lchild);
        }
        if (queue.front->treeNode->rchild != NULL &&
            queue.front->treeNode->rtag == 0) {
            EnTreeQueue(&queue, queue.front->treeNode->rchild);
        }
        // 将队头成员出队
        DeTreeQueue(&queue, &currentNode);
        PrintTreeNode(currentNode);
    }
    DestroyTreeQueue(&queue);
}

void InitTreeQueue(TreeQueue *TQueue) {
    assert(TQueue);
    TQueue->front = NULL;
    TQueue->rear = NULL;
}

bool EnTreeQueue(TreeQueue *TQueue, const BiTNode *treeNode) {
    assert(TQueue && treeNode != NULL);
    TreeQueueNode *new = (TreeQueueNode *)malloc(sizeof(TreeQueueNode));
    if (new == NULL) {
        printf("error: EnTreeQueue() malloc() failed.\n");
        return false;
    }
    new->treeNode = (BiTNode *)treeNode;
    new->next = NULL;
    // 当为空队列时
    if (TQueue->front == NULL && TQueue->rear == NULL) {
        TQueue->front = new;
        TQueue->rear = new;
    } else {
        TQueue->rear->next = new;
        TQueue->rear = new;
    }
    return true;
}

bool DeTreeQueue(TreeQueue *TQueue, BiTNode **treeNode) {
    assert(TQueue && treeNode != NULL);
    // 当为空队列时
    if (TQueue->front == NULL && TQueue->rear == NULL) {
        return false;
    }
    // 当队列只用一个成员时
    if (TQueue->front == TQueue->rear) {
        *treeNode = TQueue->front->treeNode;
        free(TQueue->front);
        TQueue->front = NULL;
        TQueue->rear = NULL;
    }
    // 当队列成员大于一个时
    else {
        *treeNode = TQueue->front->treeNode;
        TreeQueueNode *tmp = TQueue->front;
        TQueue->front = tmp->next;
        free(tmp);
    }
    return true;
}

void DestroyTreeQueue(TreeQueue *TQueue) {
    if (TQueue == NULL) {
        return;
    }
    while (TQueue->front != NULL && TQueue->rear != NULL) {
        BiTNode *tmp = NULL;
        DeTreeQueue(TQueue, &tmp);
    }
}

void CreatInThread(BiTree T) {
    BiTNode *pre = NULL;
    if (T != NULL) {
        // 中序线索化
        InThread(T, &pre);
        // 处理最后一个结点
        if (pre->rtag == 0 && pre->rchild == NULL) {
            pre->rtag = 1;
        }
    }
}

void InThread(BiTree T, BiTNode **pre) {
    if (T == NULL || pre == NULL) {
        return;
    }
    // 遍历左子树
    InThread(T->lchild, pre);
    // 如果左孩子为NULL，更新前驱
    if (T->lchild == NULL && T->ltag == 0) {
        T->lchild = *pre;
        T->ltag = 1;
    }
    // 如果 pre 右孩子为 NULL，更新后驱
    if ((*pre) != NULL && (*pre)->rchild == NULL && (*pre)->rtag == 0) {
        (*pre)->rchild = T;
        (*pre)->rtag = 1;
    }
    // 更新 pre 所指向的树结点指针
    (*pre) = T; // 指向当前结点指针
    // 遍历右子树
    InThread(T->rchild, pre);
}

BiTNode *FirstNode(BiTNode *p) {
    assert(p);
    while (p->ltag == 0) {
        p = p->lchild;
    }
    return p;
}

BiTNode *NextNode(BiTNode *p) {
    assert(p);
    if (p->rtag == 0)
        return FirstNode(
            p->rchild); // 如果 p 有右孩子，返回 p 的右孩子的第一个结点
    else
        return p->rchild; // 否则，直接返回
}

void InThreadOrder(BiTree T) {
    if (T == NULL) {
        return;
    }
    for (BiTNode *node = FirstNode(T); node != NULL; node = NextNode(node)) {
        PrintTreeNode(node);
    }
}
