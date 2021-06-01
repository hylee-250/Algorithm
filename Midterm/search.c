/*
 *  Algorithm Midterm Assignment
 *  2015003654 Lee Hoyoung
 *  234-Tree Search
 */
#include "234tree.h"
#include <stdlib.h>

TreeNode *foundNode;

int search(TreeNode *targetNode, int data)
{
    // data가 0 일때
    if (data == 0)
    {
        return -1;
    }
    // data가 targetNode에 있을 때
    for (int i = 0; i < 3; i++)
    {
        if (targetNode->key[i] == data)
        {
            foundNode = targetNode;
            return i;
        }
    }
    // targetNode의 child로 이동해 search() 호출
    if (targetNode->key[0] > data && targetNode->cNode[0] != NULL)
    {
        return search(targetNode->cNode[0], data);
    }
    if ((targetNode->key[1] > data || targetNode->key[1] == 0) && targetNode->cNode[1] != NULL)
    {
        return search(targetNode->cNode[1], data);
    }
    if ((targetNode->key[2] > data || targetNode->key[2] == 0) && targetNode->cNode[2] != NULL)
    {
        return search(targetNode->cNode[2], data);
    }
    if (data > targetNode->key[2] && targetNode->cNode[3] != NULL)
    {
        return search(targetNode->cNode[3], data);
    }

    return -1;
}