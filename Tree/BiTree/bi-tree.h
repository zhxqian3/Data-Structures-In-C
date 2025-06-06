// 线索二叉树（线索二叉链表实现）
#ifndef BI_TREE_H
#define BI_TREE_H

#include <stdbool.h>

typedef int TNodeData;

struct BiTNode {
    TNodeData data;                  // 数据元素
    struct BiTNode *lchild, *rchild; // 左右孩子指针
    int ltag, rtag;                  // 左右线索标志
};

typedef struct BiTNode BiTNode;
typedef BiTNode *BiTree;

// 中序遍历（不使用线索标志）
void InOrder(BiTree T);

// 打印当前指向的结点
void PrintTreeNode(BiTNode *node);

// 层次遍历
void LevelOrder(BiTree T);

// 中序线索二叉树构建
void CreatInThread(BiTree T);
void InThread(BiTree T, BiTNode **pre);

// 中序线索二叉树遍历
// 找到p下的第一个结点
BiTNode *FirstNode(BiTNode *p);
// 找到p的后继
BiTNode *NextNode(BiTNode *p);
// 中序线索二叉树的中序遍历
void InThreadOrder(BiTree T);

// 层次遍历所需的队列定义
struct TreeQueueNode {
    BiTNode *treeNode;          // 存储树结点指针
    struct TreeQueueNode *next; // 下一个队列成员
};

typedef struct TreeQueueNode TreeQueueNode;

struct TreeQueue {
    TreeQueueNode *front, *rear; // 队首和队尾指针
};

typedef struct TreeQueue TreeQueue;

// 初始化队列
void InitTreeQueue(TreeQueue *TQueue);

// 队列添加成员
bool EnTreeQueue(TreeQueue *TQueue, const BiTNode *treeNode);

// 队列出成员
bool DeTreeQueue(TreeQueue *TQueue, BiTNode **treeNode);

// 销毁队列
void DestroyTreeQueue(TreeQueue *TQueue);

#endif
