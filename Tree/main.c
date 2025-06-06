#include "BiTree/bi-tree.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 构建一个深度为3的满二叉树
    BiTree tree = NULL;
    BiTNode *nodeBlock = (BiTNode *)malloc(sizeof(BiTNode) * 7);
    if (nodeBlock == NULL) {
        printf("malloc() failed.\n");
        return 1;
    }
    tree = (BiTree)nodeBlock; // 第一层
    tree->ltag = 0;
    tree->rtag = 0;
    tree->data = (TNodeData)1;
    // 第二层
    tree->lchild = nodeBlock + 1;
    tree->rchild = nodeBlock + 2;
    nodeBlock[1].ltag = 0;
    nodeBlock[1].rtag = 0;
    nodeBlock[1].data = (TNodeData)2;
    nodeBlock[2].ltag = 0;
    nodeBlock[2].rtag = 0;
    nodeBlock[2].data = (TNodeData)3;
    // 第三层
    nodeBlock[1].lchild = nodeBlock + 3;
    nodeBlock[1].rchild = nodeBlock + 4;
    nodeBlock[2].lchild = nodeBlock + 5;
    nodeBlock[2].rchild = nodeBlock + 6;
    nodeBlock[3].ltag = 0;
    nodeBlock[3].rtag = 0;
    nodeBlock[4].ltag = 0;
    nodeBlock[4].rtag = 0;
    nodeBlock[5].ltag = 0;
    nodeBlock[5].rtag = 0;
    nodeBlock[6].ltag = 0;
    nodeBlock[6].rtag = 0;
    nodeBlock[3].lchild = NULL;
    nodeBlock[3].rchild = NULL;
    nodeBlock[4].lchild = NULL;
    nodeBlock[4].rchild = NULL;
    nodeBlock[5].lchild = NULL;
    nodeBlock[5].rchild = NULL;
    nodeBlock[6].lchild = NULL;
    nodeBlock[6].rchild = NULL;
    nodeBlock[3].data = (TNodeData)4;
    nodeBlock[4].data = (TNodeData)5;
    nodeBlock[5].data = (TNodeData)6;
    nodeBlock[6].data = (TNodeData)7;

    // 中序遍历（不使用线索标志）
    InOrder(tree);
    printf("\n");

    // 层次遍历
    LevelOrder(tree);
    printf("\n");

    // 中序线索二叉树构建
    CreatInThread(tree);

    // 中序线索二叉树遍历
    InThreadOrder(tree);
    printf("\n");

    free(nodeBlock);
    nodeBlock = NULL;
    return 0;
}
