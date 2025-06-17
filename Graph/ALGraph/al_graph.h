// 图的存储实现（邻接表的形式）
// 部分算法并没有实现，另外算法实现可能也不规范
#ifndef AL_GRAPH_H
#define AL_GRAPH_H

#include <stdbool.h>

#define MaxVertexNum 100 // 图中顶点数目的最大数

typedef char VertexType;                // 顶点对应的数据类型
#define VertexNullData (VertexType)'\0' // 顶点无效时对应信息为 '\0'
typedef int InfoType;
#define MaxInfo 2147483647

// 边表结点
struct ArcNode {
    int adjvex;              // 该弧所指向的顶点位置
    struct ArcNode *nextarc; // 指向下一条弧的指针
    InfoType info;           // 网的边权值
};
typedef struct ArcNode ArcNode;

// 顶点表结点
struct VNode {
    VertexType data;   // 顶点信息
    ArcNode *firstarc; // 第一条依附该顶点的弧的指针
};
typedef struct VNode VNode;
typedef struct VNode AdjList[MaxVertexNum];

// 以邻接表存储的图类型定义
struct ALGraph {
    AdjList vertices;   // 邻接表
    int vexnum, arcnum; // 顶点数目，弧数目，注意当为无向图时，边数是弧数的一半
    char graphType;     // 图类型，为 'u' 时为无向图, 为 'd' 时为有向图
};
typedef struct ALGraph ALGraph;

// 图的基本操作函数

// 初始化, type 为 'u' 时为无向图, 为 'd' 时为有向图
void InitALGraph(ALGraph *G, const char type);

// 销毁图
void DestroyALGraph(ALGraph *G);

// 判断图 G 是否存在边 <x,y> 或 (x,y)
bool Adjacent(const ALGraph *G, const VertexType x, const VertexType y);

// 列出图 G 中与结点 x 邻接的边
void ListNeighbor(const ALGraph *G, const VertexType x);

// 找到点 x, 返回 x 所在的位置, 未找到返回 -1
int FindVNode(const ALGraph *G, const VertexType x);

// 在图 G 中插入顶点 x
bool InsertVertex(ALGraph *G, const VertexType x);

// 在图 G 中删除顶点 x
void DeleteVertex(ALGraph *G, const VertexType x);

// 若无向边(x,y)或有向边<x,y>不存在，则向图 G 中添加该边
void AddEdge(ALGraph *G, const VertexType x, const VertexType y,
             const InfoType info);

// 若无向边(x,y)或有向边<x,y>存在, 删除该边
void RemoveEdge(ALGraph *G, const VertexType x, const VertexType y);

// 求图 G 中顶点 x 的第一个邻接点，若有则返回顶点号。若 x 没有邻接点或图中不存在
// x, 返回 -1
int FirstNeighbor(const ALGraph *G, const VertexType x);

// 假设图 G 中顶点 y 是顶点 x 的一个邻接点，返回除 y 外顶点 x
// 的下一个邻接点的顶点号，若 y 是 x 的最后一个邻接点，则返回 -1, 其余情况返回
// -2
int NextNeighbor(const ALGraph *G, const VertexType x, const VertexType y);

// 广度优先搜索
void BFS(const ALGraph *G, const VertexType startNode);

// 深度优先搜索
void DFS(const ALGraph *G, const VertexType startNode);

// Prim 算法求最小生成树（对无向连通图）
void Prim(const ALGraph *G, ALGraph *T);

// 判断图中两点是否连通（利用广度优先）
bool IsConnected(const ALGraph *G, VertexType x, VertexType y);

// Kruskal 算法求最小生成树（对无向联通图）
void Kruskal(ALGraph *G, ALGraph *T);

// Dijkstra 算法
void Dijkstra(ALGraph *G, VertexType x);

// Floyd 算法（目前不能自动处理负权值回路）
void Floyd(ALGraph *G);

#endif
