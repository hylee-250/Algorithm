/*
 *  Algorithm Midterm Assignment
 *  2015003654 Lee Hoyoung
 *  234-Tree Delete
 */

#include <stdlib.h>
#include "234tree.h"
#include "search.c"
#include "insert.c"

void delete (TreeNode *, int);
int findSuccessor(TreeNode *, int);
void reconstruct(TreeNode *);
int findNum(TreeNode *);
void fusion(TreeNode *, TreeNode *);
void transferR(TreeNode *, TreeNode *);
void transferL(TreeNode *, TreeNode *);

void delete (TreeNode *targetNode, int data)
{
    int idx;
    TreeNode *selectedNode;
    idx = search(targetNode, data);
    selectedNode = foundNode;
    foundNode = NULL;

    // data가 존재하지 않음
    if (idx == -1)
    {
        printf("data not exists\n");
        return;
    }
    idx = findSuccessor(selectedNode, idx);
    selectedNode = foundNode;
    foundNode = NULL;

    //selectedNode가 3,4 node 일때
    if (selectedNode->key[1] != 0)
    {
        for (int i = idx; i < 3; i++)
        {
            selectedNode->key[i] = selectedNode->key[i + 1];
        }
        selectedNode->key[2] = 0;
        return;
    }
    else //selectedNode가 2 node라서 트리를 재구성해야함
    {
        selectedNode->key[0] = 0;
        reconstruct(selectedNode);
        return;
    }
}

int findSuccessor(TreeNode *targetNode, int idx)
{
    TreeNode *selectedNode = targetNode->cNode[idx + 1]; // 삭제할 key보다 큰 값들 중 가장 작은 값을 찾기위해 내려감

    // selectedNode가 NULL일 때(targetNode가 leaf node)
    if (selectedNode == NULL)
    {
        foundNode = targetNode;
        return idx;
    }

    while (1)
    {
        if (selectedNode->key[0] != 0)
        {
            if (selectedNode->cNode[0] == NULL) // targetNode의 successor node가 leaf node일 때
            {
                targetNode->key[idx] = selectedNode->key[0]; // successor node의 가장 작은 값을 삭제할 key 자리에 놓는다.
                foundNode = selectedNode;                    // successor node의 재구성을 위한 백업작업
                return 0;                                    // 삭제된 node 자리에 올라간 key의 index
            }
        }
        selectedNode = selectedNode->cNode[0]; // leaf node까지 이동함
    }
}

void reconstruct(TreeNode *targetNode)
{
    int idx;
    TreeNode *tPnode = targetNode->pLink;
    TreeNode *temp;

    // Tree가 비었음
    if (tPnode == NULL)
        return;

    // 빈 targetNode의 index를 찾는다.
    for (int i = 0; i < 4; i++)
    {
        if (tPnode->cNode[i] == targetNode)
        {
            idx = i;
            break;
        }
    }

    // Transfer
    // 3,4 node인 형제 노드에서 key를 가져온다.
    for (int i = 0; i < 4; i++)
    {
        if (tPnode->cNode[i] == NULL)
            break; // 3,4 node인 형제 노드가 없다.
        if (tPnode->cNode[i]->key[1] != 0)
        {
            if (idx > i)
            {
                transferR(tPnode, targetNode);
            }
            else
            {
                transferL(tPnode, targetNode);
            }
            return;
        }
    }

    // Fusion
    // 빈 targetNode의 모든 형제가 2-node일 때
    // tpNode가 3, 4-node
    if (tPnode->key[1] != 0)
    {
        fusion(tPnode, targetNode);
        return;
    }

    // Propagate
    // 부모와 형제가 모두 2-node일 때
    if (idx == 0)
    {
        tPnode->cNode[0] = targetNode->cNode[0];
        if (tPnode->cNode[0] != NULL)
            tPnode->cNode[0]->pLink = tPnode;
        propagate(tPnode->cNode[1]);
    }
    else // idx == 1
    {
        tPnode->cNode[1] = targetNode->cNode[0];
        if (tPnode->cNode[1] != NULL)
            tPnode->cNode[1]->pLink = tPnode;
        propagate(tPnode->cNode[0]);
    }
    free(targetNode);

    // tPnode가 root일 때 level을 1 낮춘다.
    if (tPnode->pLink == NULL)
    {
        level--;
        return;
    }

    // 2-node의 부모, 형제 노드일 경우 propagate하면서 level이 1이 줄어서
    // level을 맞춰주기 위한 작업
    temp = nodeInit();
    temp->pLink = tPnode->pLink;
    temp->cNode[0] = tPnode;
    tPnode->pLink = temp;
    if (temp->pLink != NULL)
    {
        for (int i = 0; i < 4; i++)
        {
            if (temp->pLink->cNode[i] == tPnode)
            {
                temp->pLink->cNode[i] = temp;
                break;
            }
        }
    }
    reconstruct(temp);
    return;
}

void transferR(TreeNode *pNode, TreeNode *receiver)
{
    int num;
    TreeNode *transmitter;
    for (int i = 1; i < 4; i++)
    {
        if (pNode->cNode[i] == receiver)
        {
            transmitter = pNode->cNode[i - 1];
            num = findNum(transmitter); // 형제 노드의 key 개수

            // key 값 이동
            receiver->key[0] = pNode->key[i - 1];
            pNode->key[i - 1] = transmitter->key[num - 1];
            transmitter->key[num - 1] = 0;
            // child link setting
            receiver->cNode[1] = receiver->cNode[0];
            receiver->cNode[0] = transmitter->cNode[num];
            transmitter->cNode[2] = NULL;

            if (receiver->cNode[0] != NULL)
            { // receiver node가 2개 나타나는 현상 방지
                receiver->cNode[0]->pLink = receiver;
            }
            // transmitter가 빈 노드가 되었을 때
            if (num == 1)
                transferR(pNode, transmitter);
            return;
        }
    }
}

int findNum(TreeNode *targetNode)
{
    if (targetNode->key[2] != 0)
        return 3;
    if (targetNode->key[1] != 0)
        return 2;
    if (targetNode->key[0] != 0)
        return 1;
    return 0;
}

void transferL(TreeNode *pNode, TreeNode *receiver)
{
    int num;
    TreeNode *transmitter=nodeInit();
    for (int i = 0; i < 4; i++)
    {
        if (pNode->cNode[i] == receiver)
        {
            transmitter = pNode->cNode[i + 1];
            num = findNum(transmitter); // key 값을 보낼 transmitter의 key 숫자
        }
        // key 값 이동
        receiver->key[0] = pNode->key[i];
        pNode->key[i] = transmitter->key[0];
        transmitter->key[0] = transmitter->key[1];
        transmitter->key[1] = transmitter->key[2];
        transmitter->key[2] = 0;
        // child link setting
        receiver->cNode[1] = transmitter->cNode[0];
        transmitter->cNode[0] = transmitter->cNode[1];
        transmitter->cNode[1] = transmitter->cNode[2];
        transmitter->cNode[2] = transmitter->cNode[3];
        transmitter->cNode[3] = NULL;

        if (receiver->cNode[1] != NULL)
        {
            receiver->cNode[1]->pLink = receiver;
        }

        if (num == 1)
            transferL(pNode, transmitter);
        return;
    }
}

void fusion(TreeNode *dPnode, TreeNode *dNode)
{
    int i, j;

    if (dPnode->cNode[0] == dNode) // dNode가 제일 왼쪽 노드일 때
    {
        // 오른쪽 node와 fusion
        // node 이동
        dPnode->cNode[0] = dPnode->cNode[1];
        dPnode->cNode[1] = dPnode->cNode[2];
        dPnode->cNode[2] = dPnode->cNode[3];
        dPnode->cNode[3] = NULL;

        // key 값 이동
        dPnode->cNode[0]->key[1] = dPnode->cNode[0]->key[0];
        dPnode->cNode[0]->key[0] = dPnode->key[0];
        dPnode->key[0] = dPnode->key[1];
        dPnode->key[1] = dPnode->key[2];
        dPnode->key[2] = 0;
        // child node setting
        dPnode->cNode[0]->cNode[2] = dPnode->cNode[0]->cNode[1];
        dPnode->cNode[0]->cNode[1] = dPnode->cNode[0]->cNode[0];
        dPnode->cNode[0]->cNode[0] = dNode->cNode[0];
        if (dNode->cNode[0] = NULL) // 같은 노드가 두 개 반복되는 현상 방지
            dPnode->cNode[0]->cNode[0]->pLink = dPnode->cNode[0];
    }
    else // 제일 왼쪽 노드가 아닐 때
    {
        // 왼쪽 node와 fusion
        // key 값의 회전
        for (i = 1; i < 4; i++)
        {
            if (dPnode->cNode[i] != dNode)
                continue;
            for (j = i; j < 3; j++)
            {
                dPnode->cNode[j] = dPnode->cNode[j + 1];
            }
            dPnode->cNode[3] = NULL;
            // key 값 이동
            dPnode->cNode[i - 1]->key[1] = dPnode->key[i - 1];
            for (j = i - 1; j < 2; j++)
            {
                dPnode->key[j] = dPnode->key[j + 1];
            }
            dPnode->key[2] = 0;

            // child node setting
            dPnode->cNode[i - 1]->cNode[2] = dNode->cNode[0];
            if (dPnode->cNode[i - 1]->cNode[2] != NULL)
                dPnode->cNode[i - 1]->cNode[2]->pLink = dPnode->cNode[i - 1];
            break;
        }
    }
    free(dNode);
    return;
}