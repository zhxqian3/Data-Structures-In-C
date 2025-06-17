#include "al_graph.h"
#include <assert.h>
#include <complex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void InitALGraph(ALGraph *G, const char type) {
    assert(G);
    G->arcnum = 0;
    G->vexnum = 0;
    G->graphType = type;
    for (int i = 0; i < MaxVertexNum; i++) {
        G->vertices[i].data = VertexNullData;
        G->vertices[i].firstarc = NULL;
    }
}

void DestroyALGraph(ALGraph *G) {
    assert(G);
    ArcNode *curArc = NULL;
    VNode *curNode = NULL;
    for (int i = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data != VertexNullData) {
            curNode = &G->vertices[i];
            curArc = G->vertices[i].firstarc;
            ArcNode *tmp = NULL;
            // 销毁边
            while (curArc) {
                tmp = curArc;
                curArc = curArc->nextarc;
                free(tmp);
                G->arcnum--;
            }
            // 销毁点
            curNode->data = VertexNullData;
            curNode->firstarc = NULL;
            G->vexnum--;
        }
    }
}

bool Adjacent(const ALGraph *G, const VertexType x, const VertexType y) {
    assert(G != NULL);
    int xIndex = FindVNode(G, x);
    int yIndex = FindVNode(G, y);
    // 如果未找到 x 或点 y
    if (xIndex == -1 || yIndex == -1) {
        return false;
    }
    ArcNode *curArc = G->vertices[xIndex].firstarc;
    while (curArc) {
        if (curArc->adjvex == yIndex) {
            return true;
        }
        curArc = curArc->nextarc;
    }
    // 如果未找到 y
    return false;
}

void ListNeighbor(const ALGraph *G, const VertexType x) {
    assert(G != NULL);
    int index = FindVNode(G, x);
    // 如果未找到 x
    if (x == -1) {
        printf("没有找到%c :(\n", x);
        return;
    }
    // 如果有 x
    ArcNode *curArc = G->vertices[index].firstarc;
    if (curArc) {
        printf("%c 的邻居结点：", x);
    } else {
        printf("%c没有邻居结点 :(\n", x);
        return;
    }
    while (curArc) {
        printf("%c ", G->vertices[curArc->adjvex].data);
        curArc = curArc->nextarc;
    }
    printf("\n");
}

int FindVNode(const ALGraph *G, const VertexType x) {
    assert(G != NULL);
    for (int i = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data == x) {
            return i;
        }
    }
    return -1;
}

bool InsertVertex(ALGraph *G, const VertexType x) {
    assert(G != NULL);
    // 检查图的顶点数是否满了
    if (G->vexnum == MaxVertexNum) {
        return false;
    }
    // 检查是否已经有顶点 x
    int xIndex = FindVNode(G, x);
    if (xIndex >= 0) {
        return false;
    }
    for (int i = 0; i < MaxVertexNum; i++) {
        // 判断此位置是否可以插入点
        if (G->vertices[i].data == VertexNullData) {
            G->vertices[i].data = x;
            G->vertices[i].firstarc = NULL;
            G->vexnum++;
            return true;
        }
    }
    return false;
}

void DeleteVertex(ALGraph *G, const VertexType x) {
    assert(G != NULL);
    // 先确认是否有点x
    int xIndex = FindVNode(G, x);
    if (xIndex == -1) {
        return;
    }
    for (int i = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data == VertexNullData) {
            continue;
        }
        // 处理其余顶点是否有与 x 相关的边
        if (G->vertices[i].data != x) {
            ArcNode *curArc = G->vertices[i].firstarc;
            ArcNode *preArc = NULL;
            while (curArc) {
                if (G->vertices[curArc->adjvex].data == x) {
                    if (preArc) {
                        preArc->nextarc = curArc->nextarc;
                        free(curArc);
                    } else {
                        G->vertices[i].firstarc = curArc->nextarc;
                        free(curArc);
                    }
                    G->arcnum--; // 更新弧数量
                    break;       // 找到与 x 相关的边后退出循环，因为是简单图
                }
                preArc = curArc;
                curArc = curArc->nextarc;
            }
            continue; // 直接继续执行下一次循环
        }
        // 处理 x 顶点
        if (G->vertices[i].data == x) {
            xIndex = i;
            // 删除 x 相应的边
            ArcNode *curArc = G->vertices[i].firstarc;
            while (curArc) {
                ArcNode *tmp = curArc;
                curArc = curArc->nextarc;
                free(tmp);
                G->arcnum--;
            }
            G->vertices[i].firstarc = NULL;

            continue; // 继续执行下一个循环
        }
    }
    // 删除 x 点
    G->vertices[xIndex].data = VertexNullData;
    G->vexnum--;
}

void AddEdge(ALGraph *G, const VertexType x, const VertexType y,
             const InfoType info) {
    assert(G != NULL);
    // 找点 x,y
    int indexX = FindVNode(G, x);
    int indexY = FindVNode(G, y);
    // 如果没有点 x 或点 y
    if (indexX == -1 || indexY == -1 || indexX == indexY) {
        return;
    }
    // 添加边
    ArcNode *curArc = G->vertices[indexX].firstarc;
    ArcNode *preArc = NULL;
    while (curArc) {
        // 判断是否已有弧 (x,y) 或 <x,y>
        if (curArc->adjvex == indexY) {
            return;
        }
        preArc = curArc;
        curArc = curArc->nextarc;
    }

    ArcNode *newArc = (ArcNode *)malloc(sizeof(ArcNode));
    ArcNode *newArc1 = (ArcNode *)malloc(sizeof(ArcNode)); // 为无向图
    if (newArc == NULL || newArc1 == NULL) {
        printf("fatal: malloc() failed.\n");
        return;
    }
    newArc->adjvex = indexY;
    newArc->info = info;
    newArc->nextarc = NULL;
    // 如果点 x 一条边都没有
    if (G->vertices[indexX].firstarc == NULL) {
        G->vertices[indexX].firstarc = newArc;
        G->arcnum++;
    }
    // 如果点 x 至少有一条边
    else {
        preArc->nextarc = newArc;
        G->arcnum++;
    }

    // 为无向图时
    if (G->graphType == 'u') {
        curArc = G->vertices[indexY].firstarc;
        newArc1->nextarc = curArc;
        newArc1->info = info;
        newArc1->adjvex = indexX;
        G->vertices[indexY].firstarc = newArc1;
        G->arcnum++;
    } else {
        free(newArc1);
    }
}

void RemoveEdge(ALGraph *G, const VertexType x, const VertexType y) {
    assert(G != NULL);
    // 找点 x 和点 y
    int xIndex = FindVNode(G, x);
    int yIndex = FindVNode(G, y);
    if (xIndex == -1 || yIndex == -1) {
        return;
    }
    // 找边
    ArcNode *curArc = G->vertices[xIndex].firstarc;
    ArcNode *preArc = NULL;
    while (curArc) {
        if (curArc->adjvex == yIndex) {
            if (preArc) {
                preArc->nextarc = curArc->nextarc;
            } else {
                G->vertices[xIndex].firstarc = curArc->nextarc;
            }
            free(curArc);
            G->arcnum--;
            break; // 处理完了退出循环
        }
        preArc = curArc;
        curArc = curArc->nextarc;
    }

    // 为无向图时, 删除 (y,x)
    if (G->graphType == 'u') {
        curArc = G->vertices[yIndex].firstarc;
        preArc = NULL;
        while (curArc) {
            if (curArc->adjvex == xIndex) {
                if (preArc) {
                    preArc->nextarc = curArc->nextarc;
                } else {
                    G->vertices[yIndex].firstarc = curArc->nextarc;
                }
                free(curArc);
                G->arcnum--;
                return;
            }
            preArc = curArc;
            curArc = curArc->nextarc;
        }
    }
}

int FirstNeighbor(const ALGraph *G, const VertexType x) {
    assert(G);
    int xIndex = FindVNode(G, x);
    if (xIndex == -1) {
        return -1;
    }
    ArcNode *curArc = G->vertices[xIndex].firstarc;
    if (curArc) {
        return curArc->adjvex;
    } else {
        return -1;
    }
}

int NextNeighbor(const ALGraph *G, const VertexType x, const VertexType y) {
    assert(G);
    int xIndex = FindVNode(G, x);
    int yIndex = FindVNode(G, y);
    if (xIndex == -1 || yIndex == -1) {
        return -2;
    }
    ArcNode *curArc = G->vertices[xIndex].firstarc;
    while (curArc) {
        if (curArc->adjvex == yIndex) {
            if (curArc->nextarc) {
                return curArc->nextarc->adjvex;
            } else {
                return -1;
            }
        }
        curArc = curArc->nextarc;
    }
    return -2;
}

// 遍历所需要的 visited 数组
struct VisitNode {
    bool hasVisited;    // 访问标志
    const VNode *vnode; // 指向的顶点
};
typedef struct VisitNode VisitNode;

static bool CreatVisited(const ALGraph *G, VisitNode **visitedPtr, int *len) {
    assert(visitedPtr && G != NULL);
    // 找顶点个数
    int count = 0;
    for (int i = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data != VertexNullData) {
            count++;
        }
    }
    *len = count;
    // 创建 visited
    if (count == 0) {
        printf("fatal: G does not have any vnode.\n");
        return false;
    }
    VisitNode *arr = (VisitNode *)malloc(sizeof(VisitNode) * count);
    if (arr == NULL) {
        printf("fatal: malloc() failed.\n");
        return false;
    }
    for (int i = 0, j = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data != VertexNullData) {
            arr[j].vnode = &(G->vertices[i]);
            arr[i].hasVisited = false;
            j++;
        }
    }
    *visitedPtr = arr;
    return true;
}

static void DestroyVisited(VisitNode **visitedPtr) {
    assert(visitedPtr);
    if (*visitedPtr != NULL) {
        free(*visitedPtr);
        *visitedPtr = NULL;
    }
}

// 广度优先所需要的队列实现
struct BFSQueueNode {
    const VNode *vNode;                 // 顶点指针
    struct BFSQueueNode *nextQueueNode; // 下一个队列成员
};
typedef struct BFSQueueNode BFSQueueNode;

struct BFSQueue {
    BFSQueueNode *front, *rear; // 首尾成员指针
    int len;                    // 队列长度
};
typedef struct BFSQueue BFSQueue;

static void InitBFSQueue(BFSQueue *queue) {
    assert(queue);
    queue->front = NULL;
    queue->rear = NULL;
    queue->len = 0;
}

static bool EnBFSQueue(BFSQueue *queue, const VNode *vnode) {
    assert(queue && vnode != NULL);
    BFSQueueNode *queueNode = (BFSQueueNode *)malloc(sizeof(BFSQueueNode));
    if (queueNode == NULL) {
        return false;
    }
    queueNode->nextQueueNode = NULL;
    queueNode->vNode = vnode;
    if (queue->len == 0) {
        queue->front = queueNode;
        queue->rear = queueNode;
        queue->len++;
    } else {
        queue->rear->nextQueueNode = queueNode;
        queue->rear = queueNode;
        queue->len++;
    }
    return true;
}

static void DeBFSQueue(BFSQueue *queue) {
    assert(queue);
    if (queue->len == 0) {
        return;
    }
    if (queue->len == 1) {
        free(queue->front);
        queue->front = NULL;
        queue->rear = NULL;
        queue->len = 0;
    } else {
        BFSQueueNode *tmp = queue->front;
        queue->front = tmp->nextQueueNode;
        queue->len--;
        free(tmp);
    }
}

static void DestroyBFSQueue(BFSQueue **queuePtr) {
    assert(queuePtr && (*queuePtr) != NULL);
    while ((*queuePtr)->len != 0) {
        DeBFSQueue(*queuePtr);
    }
    *queuePtr = NULL;
}

// 遍历访问函数
static void visit(const VNode *node) {
    if (node != NULL) {
        printf("%c ", node->data);
    }
}

// 广度优先
void BFS(const ALGraph *G, const VertexType startNode) {
    assert(G);
    // 判断 startNode 是否是顶点
    int startIndex = FindVNode(G, startNode);
    if (startIndex == -1) {
        printf("起点不是顶点\n");
        return;
    }
    // 创建 visited 数组
    VisitNode *visitedArr = NULL;
    int visitedArrLen = 0;
    CreatVisited(G, &visitedArr, &visitedArrLen);

    if (visitedArr == NULL) {
        printf("visited 数组为空\n");
        return;
    }
    // 创建 遍历辅助队列
    BFSQueue queue = {0};
    BFSQueue *queuePtr = &queue;
    InitBFSQueue(&queue);

    // 广度优先遍历
    EnBFSQueue(&queue, &G->vertices[startIndex]);
    // 修改 visited 数组
    for (int i = 0; i < visitedArrLen; i++) {
        if (visitedArr[i].vnode == &G->vertices[startIndex]) {
            visitedArr[i].hasVisited = true;
            break;
        }
    }

    while (queue.len != 0) {
        // 访问
        visit(queue.front->vNode);
        // 添加邻接点
        const VNode *curNode = queue.front->vNode;
        for (int neighborIndex = FirstNeighbor(G, curNode->data);
             neighborIndex != -1;
             neighborIndex = NextNeighbor(G, curNode->data,
                                          G->vertices[neighborIndex].data)) {
            // 检查邻接点是否已经visited
            for (int i = 0; i < visitedArrLen; i++) {
                if (visitedArr[i].vnode == &G->vertices[neighborIndex]) {
                    if (visitedArr[i].hasVisited == true) {
                        break;
                    } else {
                        EnBFSQueue(&queue, visitedArr[i].vnode);
                        visitedArr[i].hasVisited = true;
                        break;
                    }
                }
            }
        }
        DeBFSQueue(&queue);

        // 处理其他子图
        if (queue.len == 0) {
            for (int i = 0; i < visitedArrLen; i++) {
                if (visitedArr[i].hasVisited == false) {
                    EnBFSQueue(&queue, visitedArr[i].vnode);
                    visitedArr[i].hasVisited = true;
                    break;
                }
            }
        }
    }

    // 销毁 visited 数组
    DestroyVisited(&visitedArr);
    // 销毁辅助队列
    DestroyBFSQueue(&queuePtr);
}

// 深度优先搜索
static void DFSHandle(const ALGraph *G, const VNode *vNode,
                      VisitNode *visitedArr, int visitedArrLen) {
    assert(G && visitedArr);
    if (vNode == NULL) {
        return;
    }
    for (int i = 0; i < visitedArrLen; i++) {
        if (visitedArr[i].vnode == vNode) {
            if (visitedArr[i].hasVisited == true) {
                return;
            } else {
                visitedArr[i].hasVisited = true;
            }
            break;
        }
    }
    visit(vNode);
    for (int neighborIndex = FirstNeighbor(G, vNode->data); neighborIndex != -1;
         neighborIndex =
             NextNeighbor(G, vNode->data, G->vertices[neighborIndex].data)) {
        DFSHandle(G, &G->vertices[neighborIndex], visitedArr, visitedArrLen);
    }
}

void DFS(const ALGraph *G, const VertexType startNode) {
    assert(G);
    // 判断 startNode 是否是顶点
    int startIndex = FindVNode(G, startNode);
    if (startIndex == -1) {
        printf("起点不是顶点\n");
        return;
    }
    // 创建 visited 数组
    VisitNode *visitedArr = NULL;
    int visitedArrLen = 0;
    CreatVisited(G, &visitedArr, &visitedArrLen);

    if (visitedArr == NULL) {
        printf("visited 数组为空\n");
        return;
    }

    while (1) {
        // 判断循环结束
        int count = 0;
        for (int i = 0; i < visitedArrLen; i++) {
            if (visitedArr[i].hasVisited == true) {
                count++;
            }
        }
        if (count == visitedArrLen) {
            break;
        }

        // 深度遍历
        DFSHandle(G, &G->vertices[startIndex], visitedArr, visitedArrLen);

        // 遍历其他子图
        for (int i = 0; i < visitedArrLen; i++) {
            if (visitedArr[i].hasVisited == false) {
                startIndex = FindVNode(G, visitedArr[i].vnode->data);
                break;
            }
        }
    }

    // 销毁 visited 数组
    DestroyVisited(&visitedArr);
}

// 顶点集
struct VSetsElem {
    const VNode *vnode;
    struct VSetsElem *nextSetsElem;
};
typedef struct VSetsElem VSetsElem;
struct VSets {
    VSetsElem *firstSetsElem;
    int length;
};
typedef struct VSets VSets;

static void InitVSets(VSets *S) {
    assert(S);
    S->length = 0;
    S->firstSetsElem = NULL;
}

static bool VSetsAdd(VSets *S, VNode *vnode) {
    assert(S && vnode != NULL);
    VSetsElem *new = (VSetsElem *)malloc(sizeof(VSetsElem));
    if (new == NULL) {
        printf("malloc() failed.\n");
        return false;
    }
    new->vnode = vnode;
    new->nextSetsElem = NULL;
    if (S->firstSetsElem == NULL) {
        S->firstSetsElem = new;
        S->length++;
        return true;
    } else {
        new->nextSetsElem = S->firstSetsElem;
        S->firstSetsElem = new;
        S->length++;
        return true;
    }
}

static void VSetsDelete(VSets *S, VNode *vnode) {
    assert(S && vnode != NULL);
    if (S->length == 0) {
        printf("sets is empty.\n");
        return;
    }
    VSetsElem *cur = S->firstSetsElem;
    VSetsElem *pre = NULL;
    while (cur) {
        if (cur->vnode == vnode) {
            if (pre) {
                pre->nextSetsElem = cur->nextSetsElem;
                free(cur);
                S->length--;
                return;
            } else {
                S->firstSetsElem = cur->nextSetsElem;
                free(cur);
                S->length--;
                return;
            }
        }
        pre = cur;
        cur = cur->nextSetsElem;
    }
}

static void DeleteVSets(VSets *S) {
    assert(S);
    if (S->length == 0) {
        return;
    }
    VSetsElem *cur = S->firstSetsElem;
    while (cur) {
        VSetsElem *tmp = cur;
        cur = cur->nextSetsElem;
        free(tmp);
        S->length--;
    }
}

// 边集
struct ArcSetsElem {
    ArcNode *arc;
    VertexType sourceNodeData;
    struct ArcSetsElem *nextElem;
};
typedef struct ArcSetsElem ArcSetsElem;
struct ArcSets {
    ArcSetsElem *firstArcSetsElem;
    int length;
};
typedef struct ArcSets ArcSets;

static void InitArcSets(ArcSets *S) {
    assert(S);
    S->length = 0;
    S->firstArcSetsElem = NULL;
}

static bool ArcSetsAdd(ArcSets *S, ArcNode *arcnode, VertexType sourceNode) {
    assert(S && arcnode != NULL);
    ArcSetsElem *new = (ArcSetsElem *)malloc(sizeof(ArcSetsElem));
    if (new == NULL) {
        printf("malloc() failed.\n");
        return false;
    }
    new->arc = arcnode;
    new->nextElem = NULL;
    new->sourceNodeData = sourceNode;
    if (S->firstArcSetsElem == NULL) {
        S->firstArcSetsElem = new;
        S->length++;
        return true;
    } else {
        new->nextElem = S->firstArcSetsElem;
        S->firstArcSetsElem = new;
        S->length++;
        return true;
    }
}

static void ArcSetsDelete(ArcSets *S, ArcNode *arcnode) {
    assert(S && arcnode != NULL);
    if (S->length == 0) {
        printf("sets is empty.\n");
        return;
    }
    ArcSetsElem *cur = S->firstArcSetsElem;
    ArcSetsElem *pre = NULL;
    while (cur) {
        if (cur->arc == arcnode) {
            if (pre) {
                pre->nextElem = cur->nextElem;
                free(cur);
                S->length--;
                return;
            } else {
                S->firstArcSetsElem = cur->nextElem;
                free(cur);
                S->length--;
                return;
            }
        }
        pre = cur;
        cur = cur->nextElem;
    }
}

static void DeleteArcSets(ArcSets *S) {
    assert(S);
    if (S->length == 0) {
        return;
    }
    ArcSetsElem *cur = S->firstArcSetsElem;
    while (cur) {
        ArcSetsElem *tmp = cur;
        cur = cur->nextElem;
        free(tmp);
        S->length--;
    }
    S->firstArcSetsElem = NULL;
}

void Prim(const ALGraph *G, ALGraph *T) {
    assert(G && T != NULL);
    // 判断是否是无向图
    if (G->graphType == 'd' || T->graphType == 'd') {
        printf("图为有向图，不支持，退出\n");
        return;
    }
    // 清理 T 所指向的图
    if (T->vexnum != 0 || T->arcnum != 0) {
        for (int i = 0; i < MaxVertexNum; i++) {
            if (T->vertices[i].data != VertexNullData) {
                ArcNode *curArc = T->vertices[i].firstarc;
                ArcNode *nextArc = NULL;
                if (curArc != NULL) {
                    nextArc = curArc->nextarc;
                    free(curArc);
                    curArc = nextArc;
                }
                T->vertices[i].firstarc = NULL;
                T->vertices[i].data = VertexNullData;
            }
        }
        T->arcnum = 0;
        T->vexnum = 0;
    }
    // 添加任意一个顶点
    VSets vset1 = {0}; // 原始顶点集
    VSets vset2 = {0}; // 目的顶点集
    InitVSets(&vset1);
    InitVSets(&vset2);
    ArcSets arcSet = {0}; // 边集
    InitArcSets(&arcSet);
    for (int i = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data != VertexNullData) {
            if (vset2.length == 0) {
                VSetsAdd(&vset2, (VNode *)&G->vertices[i]);
            } else {
                VSetsAdd(&vset1, (VNode *)&G->vertices[i]);
            }
        }
    }
    // 直到原始顶点集为空
    while (vset1.length != 0) {
        ArcNode *nearArc = NULL;
        InfoType curInfo = MaxInfo; // 将权值赋予一个最高值
        VSetsElem *curSetElem = NULL;
        VNode *sourceNode = NULL;
        // 找最近的顶点
        for (int i = 0; i < vset1.length; i++) {
            if (curSetElem == NULL) {
                curSetElem = vset1.firstSetsElem;
            }
            VSetsElem *destSetElem = NULL;
            for (int j = 0; j < vset2.length; j++) {
                if (destSetElem == NULL) {
                    destSetElem = vset2.firstSetsElem;
                }
                VNode *curNode = (VNode *)destSetElem->vnode;
                // 遍历边
                ArcNode *curArc = curNode->firstarc;
                while (curArc) {
                    if (&G->vertices[curArc->adjvex] == curSetElem->vnode &&
                        curArc->info <= curInfo) {
                        curInfo = curArc->info;
                        nearArc = curArc;
                        sourceNode = (VNode *)destSetElem->vnode;
                    }
                    curArc = curArc->nextarc;
                }
                destSetElem = destSetElem->nextSetsElem;
            }
            curSetElem = curSetElem->nextSetsElem;
        }
        // 如果不是连通图
        if (curInfo == MaxInfo) {
            printf("不是连通图，无法生成最小生成树\n");
            // 清理点集和边集
            DeleteVSets(&vset1);
            DeleteVSets(&vset2);
            DeleteArcSets(&arcSet);
            return;
        } else {
            // 添加点集和边集
            VSetsAdd(&vset2, (VNode *)&G->vertices[nearArc->adjvex]);
            VSetsDelete(&vset1, (VNode *)&G->vertices[nearArc->adjvex]);
            ArcSetsAdd(&arcSet, nearArc, sourceNode->data);
        }
    }
    // 赋值给T
    VSetsElem *curVSetElem = NULL;
    for (int i = 0; i < vset2.length; i++) {
        if (curVSetElem == NULL) {
            curVSetElem = vset2.firstSetsElem;
        }
        InsertVertex(T, curVSetElem->vnode->data);
        curVSetElem = curVSetElem->nextSetsElem;
    }
    ArcSetsElem *curArcSetElem = NULL;
    for (int i = 0; i < arcSet.length; i++) {
        if (curArcSetElem == NULL) {
            curArcSetElem = arcSet.firstArcSetsElem;
        }
        AddEdge(T, curArcSetElem->sourceNodeData,
                G->vertices[curArcSetElem->arc->adjvex].data,
                curArcSetElem->arc->info);
        curArcSetElem = curArcSetElem->nextElem;
    }
}

bool IsConnected(const ALGraph *G, VertexType x, VertexType y) {
    assert(G);
    BFSQueue queue = {0};
    BFSQueue *queuePtr = &queue;
    InitBFSQueue(&queue);
    int xIndex = FindVNode(G, x);
    int yIndex = FindVNode(G, y);
    if (xIndex == -1 || yIndex == -1) {
        printf("点未找到\n");
        return false;
    }
    EnBFSQueue(&queue, &G->vertices[xIndex]);
    VisitNode *visitedArr = NULL;
    int visitedArrLen = 0;
    CreatVisited(G, &visitedArr, &visitedArrLen);
    if (visitedArr == NULL) {
        printf("visted 创建失败\n");
        DeBFSQueue(&queue);
        return false;
    }
    while (queue.len != 0) {
        // 队列成员加入
        VNode *curVNode = (VNode *)queue.front->vNode;
        ArcNode *curArc = curVNode->firstarc;
        while (curArc) {
            for (int i = 0; i < visitedArrLen; i++) {
                if (visitedArr[i].hasVisited == false &&
                    visitedArr[i].vnode == &G->vertices[curArc->adjvex]) {
                    visitedArr[i].hasVisited = true;
                    EnBFSQueue(&queue, visitedArr[i].vnode);
                    // 判断联通
                    if (visitedArr[i].vnode->data == y) {
                        DestroyVisited(&visitedArr);
                        DestroyBFSQueue(&queuePtr);
                        return true;
                    }
                    break;
                }
            }
            curArc = curArc->nextarc;
        }
        DeBFSQueue(&queue);
    }
    DestroyBFSQueue(&queuePtr);
    DestroyVisited(&visitedArr);
    return false;
}

void Kruskal(ALGraph *G, ALGraph *T) {
    assert(G && T != NULL);
    // 判断是否是无向图
    if (G->graphType == 'd' || T->graphType == 'd') {
        printf("图为有向图，不支持，退出\n");
        return;
    }
    // 清理 T 所指向的图
    if (T->vexnum != 0 || T->arcnum != 0) {
        for (int i = 0; i < MaxVertexNum; i++) {
            if (T->vertices[i].data != VertexNullData) {
                ArcNode *curArc = T->vertices[i].firstarc;
                ArcNode *nextArc = NULL;
                if (curArc != NULL) {
                    nextArc = curArc->nextarc;
                    free(curArc);
                    curArc = nextArc;
                }
                T->vertices[i].firstarc = NULL;
                T->vertices[i].data = VertexNullData;
            }
        }
        T->arcnum = 0;
        T->vexnum = 0;
    }
    // 复制 G 的顶点到 T
    T->vexnum = G->vexnum;
    for (int i = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data != VertexNullData) {
            T->vertices[i].data = G->vertices[i].data;
        }
    }
    // 创建边集
    ArcSets arcSet = {0};
    InitArcSets(&arcSet);
    for (int i = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data != VertexNullData) {
            ArcNode *curArc = G->vertices[i].firstarc;
            while (curArc) {
                ArcSetsAdd(&arcSet, curArc, G->vertices[i].data);
                curArc = curArc->nextarc;
            }
        }
    }
    // 开始
    while (T->arcnum / 2 < T->vexnum - 1) {
        ArcSetsElem *curArcSetElem = NULL;
        InfoType curInfo = MaxInfo;
        ArcNode *curArc = NULL;
        VertexType sourceNodeData = VertexNullData;
        for (int i = 0; i < arcSet.length; i++) {
            if (curArcSetElem == NULL) {
                curArcSetElem = arcSet.firstArcSetsElem;
            }
            // 找权值最小边
            if (curArcSetElem->arc->info <= curInfo) {
                if (!IsConnected(
                        T, curArcSetElem->sourceNodeData,
                        G->vertices[curArcSetElem->arc->adjvex].data)) {
                    curArc = curArcSetElem->arc;
                    curInfo = curArc->info;
                    sourceNodeData = curArcSetElem->sourceNodeData;
                }
            }
            curArcSetElem = curArcSetElem->nextElem;
        }
        // 如果未找到边
        if (curArc == NULL) {
            printf("未连通，失败\n");
            DeleteArcSets(&arcSet);
            return;
        }
        // 找到了
        else {
            AddEdge(T, sourceNodeData, G->vertices[curArc->adjvex].data,
                    curInfo);
            ArcSetsDelete(&arcSet, curArc);
        }
    }
    DeleteArcSets(&arcSet);
}

// Dijkstra 所需要的辅助数组定义
struct DijkStraArr {
    VNode *vNode;
    int isFinal;
    InfoType dist;
    VNode *path;
};
typedef struct DijkStraArr DijkStraArr;

static void CreatDijkArr(ALGraph *G, DijkStraArr **arrPtr) {
    assert(G && arrPtr != NULL);
    int length = G->vexnum;
    *arrPtr = (DijkStraArr *)malloc(sizeof(DijkStraArr) * length);
    if (*arrPtr == NULL) {
        printf("malloc() failed\n");
        return;
    }
    for (int i = 0, j = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data != VertexNullData) {
            (*arrPtr)[j].vNode = &G->vertices[i];
            (*arrPtr)[j].isFinal = 0;
            (*arrPtr)[j].dist = MaxInfo;
            (*arrPtr)[j].path = NULL;
            j++;
        }
    }
}

static void DestroyDijkArr(DijkStraArr **arrPtr) {
    assert(arrPtr);
    if (*arrPtr != NULL) {
        free(*arrPtr);
        *arrPtr = NULL;
    }
}

void Dijkstra(ALGraph *G, VertexType x) {
    assert(G);
    int xIndex = FindVNode(G, x);
    if (xIndex == -1) {
        printf("源点未找到，退出\n");
        return;
    }
    for (int i = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data != VertexNullData) {
            ArcNode *curArc = G->vertices[i].firstarc;
            while (curArc) {
                if (curArc->info < 0) {
                    printf("有负权值边，退出\n");
                    return;
                }
                curArc = curArc->nextarc;
            }
        }
    }
    DijkStraArr *dijkArr = NULL;
    CreatDijkArr(G, &dijkArr);
    if (dijkArr == NULL) {
        printf("辅助数组创建失败\n");
        return;
    }
    // 初始化源点
    VSets vset = {0};
    InitVSets(&vset);
    for (int i = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data != VertexNullData) {
            if (G->vertices[i].data != x) {
                VSetsAdd(&vset, &G->vertices[i]);
            }
        }
    }
    // 初始化辅助数组
    for (int i = 0; i < G->vexnum; i++) {
        if (dijkArr[i].vNode->data == x) {
            dijkArr[i].dist = 0;
            dijkArr[i].isFinal = 1;
            dijkArr[i].path = NULL;
            ArcNode *curArc = dijkArr[i].vNode->firstarc;
            while (curArc) {
                VNode *curVNode = &G->vertices[curArc->adjvex];
                for (int j = 0; j < G->vexnum; j++) {
                    if (dijkArr[j].vNode == curVNode) {
                        dijkArr[j].dist = curArc->info;
                        dijkArr[j].path = dijkArr[i].vNode;
                        break;
                    }
                }
                curArc = curArc->nextarc;
            }
            break;
        }
    }
    while (vset.length > 0) {
        // 选出最短路径
        InfoType minDist = MaxInfo;
        int nextIndex = -1;
        for (int i = 0; i < G->vexnum; i++) {
            if (dijkArr[i].isFinal == 0 && dijkArr[i].dist <= minDist) {
                nextIndex = i;
                minDist = dijkArr[i].dist;
            }
        }
        dijkArr[nextIndex].isFinal = 1;
        VSetsDelete(&vset, dijkArr[nextIndex].vNode);
        // 更新辅助数组
        for (int i = 0; i < G->vexnum; i++) {
            if (dijkArr[i].isFinal == 0) {
                ArcNode *tmpArc = dijkArr[nextIndex].vNode->firstarc;
                while (tmpArc) {
                    if (G->vertices[tmpArc->adjvex].data ==
                        dijkArr[i].vNode->data) {
                        if (dijkArr[i].dist >=
                            tmpArc->info + dijkArr[nextIndex].dist) {
                            dijkArr[i].dist =
                                tmpArc->info + dijkArr[nextIndex].dist;
                            dijkArr[i].path = dijkArr[nextIndex].vNode;
                        }
                        break;
                    }
                    tmpArc = tmpArc->nextarc;
                }
            }
        }
    }
    // 打印辅助数组
    for (int i = 0; i < G->vexnum; i++) {
        if (dijkArr[i].vNode->data != x) {
            printf("%c->%c: %d\n", x, dijkArr[i].vNode->data, dijkArr[i].dist);
        }
    }
    DeleteVSets(&vset);
    DestroyDijkArr(&dijkArr);
}

void Floyd(ALGraph *G) {
    assert(G);
    if (G->vexnum == 0) {
        printf("图为空，退出\n");
        return;
    }
    // 创建索引
    VNode *nodeArr[G->vexnum];
    for (int i = 0, j = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data != VertexNullData) {
            nodeArr[j] = &G->vertices[i];
            j++;
        }
    }
    // 创建最短路径方阵
    InfoType dist[G->vexnum][G->vexnum];
    // 初始化方阵
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            int surIndex = FindVNode(G, nodeArr[i]->data);
            int desIndex = FindVNode(G, nodeArr[j]->data);
            if (surIndex == desIndex) {
                dist[i][j] = 0;
                continue;
            }
            ArcNode *curArc = G->vertices[surIndex].firstarc;
            int tmpFlag = 0;
            while (curArc) {
                if (curArc->adjvex == desIndex) {
                    dist[i][j] = curArc->info;
                    tmpFlag = 1;
                    break;
                }
                curArc = curArc->nextarc;
            }
            if (tmpFlag == 0) {
                dist[i][j] = MaxInfo;
            }
        }
    }
    // 递推方阵序列
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            for (int k = 0; k < G->vexnum; k++) {
                if (dist[j][k] >= dist[j][i] + dist[i][k]) {
                    dist[j][k] = dist[j][i] + dist[i][k];
                }
            }
        }
    }
    // 输出结果
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            printf("%c->%c: %d; ", nodeArr[i]->data, nodeArr[j]->data,
                   dist[i][j]);
        }
        printf("\n");
    }
}
