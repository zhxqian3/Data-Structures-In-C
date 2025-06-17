#include "test.h"
#include "../ALGraph/al_graph.h"
#include <assert.h>
#include <stdio.h>

static void PrintALGraph(const ALGraph *G) {
    assert(G);
    printf("当前邻接表：\n");
    printf("图类型: ");
    if (G->graphType == 'u') {
        printf("无向图\n");
    } else {
        printf("有向图\n");
    }
    printf("顶点数目：%d\n", G->vexnum);
    if (G->graphType == 'u') {
        printf("弧数目：%d\n", G->arcnum / 2);
    } else {
        printf("弧数目：%d\n", G->arcnum);
    }
    printf("顶点及边信息：\n");
    for (int i = 0; i < MaxVertexNum; i++) {
        if (G->vertices[i].data != VertexNullData) {
            printf("%c: ", G->vertices[i].data);
            ArcNode *curArc = G->vertices[i].firstarc;
            while (curArc) {
                printf("%c->%c(%d) ", G->vertices[i].data,
                       G->vertices[curArc->adjvex].data, curArc->info);
                curArc = curArc->nextarc;
            }
            printf("\n");
        }
    }
}

static void cleanIO(void) {
    while (getchar() != '\n') {
        ;
    }
}

void ALGraphTest(void) {
    int inputFlag = -1;
    ALGraph graph = {0};
inputType:
    printf("请指定图类型(u 为无向图，d 为有向图): ");
    char graphType = 0;
    scanf(" %c", &graphType);
    cleanIO();
    if (graphType == 'u' || graphType == 'd') {
        InitALGraph(&graph, graphType);
    } else {
        goto inputType;
    }
    do {
        // 打印当前邻接表状态
        printf("############################\n");
        PrintALGraph(&graph);
    // 输入 & 处理
    input:
        printf("############################\n");
        printf("请选择操作：\n");
        printf("1. 判断是否存在边\n");
        printf("2. 列出与顶点邻接边\n");
        printf("3. 插入顶点\n");
        printf("4. 删除顶点\n");
        printf("5. 添加边\n");
        printf("6. 删除边\n");
        printf("7. 求第一个邻接点\n");
        printf("8. 求下一个邻接点\n");
        printf("9. 广度优先遍历\n");
        printf("10: 深度优先遍历\n");
        printf("11: Prim 算法\n");
        printf("12: Kruskal 算法\n");
        printf("13: Dijkstra 算法\n");
        printf("14: Floyd 算法\n");
        printf("0. Exit\n");
        printf("############################\n");
        printf("输入-> ");
        if (scanf("%d", &inputFlag) != 1) {
            printf("输入不合法，重新输入\n");
            cleanIO();
            goto input;
        }
        cleanIO();
        switch (inputFlag) {
        case 1: {
            printf("输入顶点信息：");
            VertexType x = 0, y = 0;
            scanf("%c %c", &x, &y);
            if (Adjacent(&graph, x, y)) {
                printf("%c->%c 存在\n", x, y);
            } else {
                printf("%c->%c 不存在\n", x, y);
            }
            // 清空输入缓冲区
            cleanIO();
            break;
        }
        case 2: {
            printf("输入顶点信息：");
            VertexType x = 0;
            scanf("%c", &x);
            ListNeighbor(&graph, x);
            cleanIO();
            break;
        }
        case 3: {
            printf("输入要插入的顶点信息：");
            VertexType x = 0;
            scanf("%c", &x);
            if (InsertVertex(&graph, x)) {
                printf("插入成功\n");
            } else {
                printf("顶点数已达上限或已有该顶点\n");
            }
            cleanIO();
            break;
        }
        case 4: {
            printf("输入要删除的顶点信息: ");
            VertexType x = 0;
            scanf("%c", &x);
            DeleteVertex(&graph, x);
            cleanIO();
            break;
        }
        case 5: {
            printf("输入添加的边的信息：");
            VertexType x = 0, y = 0;
            InfoType info = 0;
            scanf("%c %c %d", &x, &y, &info);
            AddEdge(&graph, x, y, info);
            cleanIO();
            break;
        }
        case 6: {
            printf("输入要删除的边的信息：");
            VertexType x = 0, y = 0;
            scanf("%c %c", &x, &y);
            RemoveEdge(&graph, x, y);
            cleanIO();
            break;
        }
        case 7: {
            printf("输入要查找的点: ");
            VertexType x = 0;
            scanf("%c", &x);
            int neighborIndex = FirstNeighbor(&graph, x);
            if (neighborIndex >= 0) {
                printf("%c 的第一个邻接点是 %c\n", x,
                       graph.vertices[neighborIndex].data);
            } else {
                printf("%c 没有邻接点或 %c 不存在\n", x, x);
            }
            cleanIO();
            break;
        }
        case 8: {
            printf("输入要查找的点及其邻接点：");
            VertexType x = 0, y = 0;
            scanf("%c %c", &x, &y);
            int nextIndex = NextNeighbor(&graph, x, y);
            if (nextIndex >= 0) {
                printf("%c 的邻接点 %c 的下一个邻接点是 %c\n", x, y,
                       graph.vertices[nextIndex].data);
            } else {
                printf("未找到\n");
            }
            cleanIO();
            break;
        }
        case 9: {
            printf("输入广度优先遍历起点：");
            VertexType x = 0;
            scanf(" %c", &x);
            printf("广度优先序列：");
            BFS(&graph, x);
            printf("\n");
            cleanIO();
            break;
        }
        case 10: {
            printf("输入深度优先遍历起点：");
            VertexType x = 0;
            scanf(" %c", &x);
            printf("深度优先序列：");
            DFS(&graph, x);
            printf("\n");
            cleanIO();
            break;
        }
        case 11: {
            printf("Prim 结果：\n");
            ALGraph ret = {0};
            InitALGraph(&ret, 'u');
            Prim(&graph, &ret);
            PrintALGraph(&ret);
            DestroyALGraph(&ret);
            break;
        }
        case 12: {
            printf("Kruskal 结果：\n");
            ALGraph ret = {0};
            InitALGraph(&ret, 'u');
            Kruskal(&graph, &ret);
            PrintALGraph(&ret);
            DestroyALGraph(&ret);
            break;
        }
        case 13: {
            printf("输入源点：");
            VertexType input = 0;
            scanf(" %c", &input);
            printf("Dijkstra 结果：\n");
            Dijkstra(&graph, input);
            cleanIO();
            break;
        }
        case 14: {
            Floyd(&graph);
            break;
        }
        case 0: {
            return;
        }
        default: {
            printf("输入不合法，重新输入\n");
            goto input;
        }
        }
    } while (1);
}
