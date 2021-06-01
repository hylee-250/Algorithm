/*
 *  Algorithm Midterm Assignment
 *  2015003654 Lee Hoyoung
 *  234-Tree Insert
 */

#include <stdlib.h>
#include "234tree.h"

// 함수 선언
TreeNode *nodeInit();
void insert(TreeNode *, int);
TreeNode *split(TreeNode *, TreeNode *);
void propagate(TreeNode *);
void equalizeNode(TreeNode *);

TreeNode *root;
int level = 0;

TreeNode *nodeInit()
{
    TreeNode *nNode;
    nNode = (TreeNode *)malloc(sizeof(TreeNode)); // Memory Allocate
    nNode->key[0] = 0;
    nNode->key[1] = 0;
    nNode->key[2] = 0;
    nNode->pLink = NULL;
    nNode->cNode[0] = NULL;
    nNode->cNode[1] = NULL;
    nNode->cNode[2] = NULL;
    nNode->cNode[3] = NULL;
    return nNode;
}

void insert(TreeNode *targetNode, int data)
{
    TreeNode *temp;
    // Leaf node & Root node
    if (targetNode->cNode[0] == NULL)
    {
        if (targetNode->key[0] == 0)
        { //Empty node
            targetNode->key[0] = data;
        }
        else if (targetNode->key[1] == 0)
        { //2-node
            if (data > targetNode->key[0])
            {
                targetNode->key[1] = data; // key0 data
            }
            else
            {
                targetNode->key[1] = targetNode->key[0];
                targetNode->key[0] = data; // data key0
            }
        }
        else if (targetNode->key[2] == 0)
        { //3-node
            if (data > targetNode->key[1])
            {
                targetNode->key[2] = data;
            }
            else if (data > targetNode->key[0]) // key0 data key1
            {
                targetNode->key[2] = targetNode->key[1];
                targetNode->key[1] = data;
            }
            else //data가 제일 작은 경우
            {
                targetNode->key[2] = targetNode->key[1];
                targetNode->key[1] = targetNode->key[0];
                targetNode->key[0] = data;
            }
        }
        else
        { // 4-node
            temp = nodeInit();
            temp->key[0] = data;
            targetNode = split(targetNode, temp);
            temp = NULL;
            propagate(targetNode);
            targetNode = NULL;
        }
    }
    else if (targetNode->key[0] > data)
    {
        insert(targetNode->cNode[0], data); // leaf node에 이를 때까지 recursive call이 일어남
    }
    else if (targetNode->key[1] > data || targetNode->key[1] == 0)
    {
        insert(targetNode->cNode[1], data);
    }
    else if (targetNode->key[2] > data || targetNode->key[2] == 0)
    {
        insert(targetNode->cNode[2], data);
    }
    else
    {
        insert(targetNode->cNode[3], data);
    }
}

TreeNode *split(TreeNode *targetNode, TreeNode *temp)
{
    TreeNode *nNode; //new node
    nNode = nodeInit();
    nNode->pLink = targetNode->pLink;
    nNode->cNode[0] = targetNode;
    nNode->cNode[1] = temp;
    targetNode->pLink = nNode;
    temp->pLink = nNode;

    if (targetNode->pLink != NULL)
    {
        for (int i = 0; i < 4; i++)
        {
            if (targetNode->pLink->cNode[i] == targetNode)
            {
                targetNode->pLink->cNode[i] = targetNode;
                break;
            }
        }
    }
    // 3번째로 작은 값 위로 올리기
    if (targetNode->key[0] > temp->key[0]) // (key0 key1 key2) (data) -> (data key0) (key2)
    {
        //key setting
        nNode->key[0] = targetNode->key[1];
        targetNode->key[1] = targetNode->key[0];
        targetNode->key[0] = temp->key[0];
        temp->key[0] = targetNode->key[2];
        targetNode->key[2] = 0;
        //child link setting
        targetNode->cNode[0] = temp->cNode[0];
        temp->cNode[0] = targetNode->cNode[2];
        targetNode->cNode[2] = targetNode->cNode[1];
        targetNode->cNode[1] = temp->cNode[1];
        temp->cNode[1] = targetNode->cNode[3];
        targetNode->cNode[3] = NULL;
    }
    else if (targetNode->key[1] > temp->key[0])
    {
        //key setting
        nNode->key[0] = targetNode->key[1];
        targetNode->key[1] = temp->key[0];
        temp->key[0] = targetNode->key[2];
        targetNode->key[2] = 0;
        //child link setting
        targetNode->cNode[1] = temp->cNode[0];
        temp->cNode[0] = temp->cNode[2];
        targetNode->cNode[2] = temp->cNode[1];
        temp->cNode[1] = targetNode->cNode[3];
        targetNode->cNode[3] = NULL;
    }
    else if (targetNode->key[2] > temp->key[0])
    {
        //key setting
        nNode->key[0] = temp->key[0];
        temp->key[0] = targetNode->key[2];
        targetNode->key[2] = 0;

        //children link setting
        targetNode->cNode[2] = temp->cNode[0];
        temp->cNode[0] = temp->cNode[1];
        temp->cNode[1] = targetNode->cNode[3];
        targetNode->cNode[3] = NULL;
    }
    else
    {
        nNode->key[0] = targetNode->key[2];
        targetNode->key[2] = 0;
        targetNode->cNode[3] = NULL;
    }
    equalizeNode(targetNode);
    equalizeNode(temp);
    return nNode;
}

void propagate(TreeNode *targetNode)
{
    // 기존 targetNode의 parent와 split을 통해 생겨난 parent를 합친다.
    TreeNode *pNode = targetNode->pLink;
    // targetNode가 root일 때
    if (pNode == NULL)
    {
        root = targetNode;
        level++;
        return;
    }
    // pNode가 4-node일 때
    if (pNode->key[2] != 0)
    {
        targetNode = split(pNode, targetNode);
        propagate(targetNode);
        return;
    }
    // pNode와 targetNode를 합침
    if (pNode->key[0] > targetNode->key[0])
    {
        // key setting
        pNode->key[2] = pNode->key[1];
        pNode->key[1] = pNode->key[0];
        pNode->key[0] = targetNode->key[0];
        // child node setting
        pNode->cNode[3] = pNode->cNode[2];
        pNode->cNode[2] = pNode->cNode[1];
        pNode->cNode[1] = targetNode->cNode[1];
        pNode->cNode[0] = targetNode->cNode[0];
    }
    else if ((pNode->key[1] > targetNode->key[0]) || pNode->key[1] == 0)
    {
        // key setting
        pNode->key[2] = pNode->key[1];
        pNode->key[1] = targetNode->key[0];
        // child node setting
        pNode->cNode[3] = pNode->cNode[2];
        pNode->cNode[2] = targetNode->cNode[1];
        pNode->cNode[1] = targetNode->cNode[0];
    }
    else
    {
        // key setting
        pNode->key[2] = targetNode->key[0];

        //child node setting
        pNode->cNode[2] = targetNode->cNode[0];
        pNode->cNode[3] = targetNode->cNode[1];
    }
    equalizeNode(pNode);
    free(targetNode);
}

void equalizeNode(TreeNode *targetNode)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (targetNode->cNode[i] == NULL)
            break;
        targetNode->cNode[i]->pLink = targetNode;
    }
    return;
}