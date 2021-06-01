#ifndef _TreeNode
#define _TreeNode

#include <stdio.h>

typedef struct TreeNode
{
    int key[3];
    struct TreeNode *cNode[4];
    struct TreeNode *pLink;
} TreeNode;

#endif