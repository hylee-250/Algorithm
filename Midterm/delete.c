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

    // data�� �������� ����
    if (idx == -1)
    {
        printf("data not exists\n");
        return;
    }
    idx = findSuccessor(selectedNode, idx);
    selectedNode = foundNode;
    foundNode = NULL;

    //selectedNode�� 3,4 node �϶�
    if (selectedNode->key[1] != 0)
    {
        for (int i = idx; i < 3; i++)
        {
            selectedNode->key[i] = selectedNode->key[i + 1];
        }
        selectedNode->key[2] = 0;
        return;
    }
    else //selectedNode�� 2 node�� Ʈ���� �籸���ؾ���
    {
        selectedNode->key[0] = 0;
        reconstruct(selectedNode);
        return;
    }
}

int findSuccessor(TreeNode *targetNode, int idx)
{
    TreeNode *selectedNode = targetNode->cNode[idx + 1]; // ������ key���� ū ���� �� ���� ���� ���� ã������ ������

    // selectedNode�� NULL�� ��(targetNode�� leaf node)
    if (selectedNode == NULL)
    {
        foundNode = targetNode;
        return idx;
    }

    while (1)
    {
        if (selectedNode->key[0] != 0)
        {
            if (selectedNode->cNode[0] == NULL) // targetNode�� successor node�� leaf node�� ��
            {
                targetNode->key[idx] = selectedNode->key[0]; // successor node�� ���� ���� ���� ������ key �ڸ��� ���´�.
                foundNode = selectedNode;                    // successor node�� �籸���� ���� ����۾�
                return 0;                                    // ������ node �ڸ��� �ö� key�� index
            }
        }
        selectedNode = selectedNode->cNode[0]; // leaf node���� �̵���
    }
}

void reconstruct(TreeNode *targetNode)
{
    int idx;
    TreeNode *tPnode = targetNode->pLink;
    TreeNode *temp;

    // Tree�� �����
    if (tPnode == NULL)
        return;

    // �� targetNode�� index�� ã�´�.
    for (int i = 0; i < 4; i++)
    {
        if (tPnode->cNode[i] == targetNode)
        {
            idx = i;
            break;
        }
    }

    // Transfer
    // 3,4 node�� ���� ��忡�� key�� �����´�.
    for (int i = 0; i < 4; i++)
    {
        if (tPnode->cNode[i] == NULL)
            break; // 3,4 node�� ���� ��尡 ����.
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
    // �� targetNode�� ��� ������ 2-node�� ��
    // tpNode�� 3, 4-node
    if (tPnode->key[1] != 0)
    {
        fusion(tPnode, targetNode);
        return;
    }

    // Propagate
    // �θ�� ������ ��� 2-node�� ��
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

    // tPnode�� root�� �� level�� 1 �����.
    if (tPnode->pLink == NULL)
    {
        level--;
        return;
    }

    // 2-node�� �θ�, ���� ����� ��� propagate�ϸ鼭 level�� 1�� �پ
    // level�� �����ֱ� ���� �۾�
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
            num = findNum(transmitter); // ���� ����� key ����

            // key �� �̵�
            receiver->key[0] = pNode->key[i - 1];
            pNode->key[i - 1] = transmitter->key[num - 1];
            transmitter->key[num - 1] = 0;
            // child link setting
            receiver->cNode[1] = receiver->cNode[0];
            receiver->cNode[0] = transmitter->cNode[num];
            transmitter->cNode[2] = NULL;

            if (receiver->cNode[0] != NULL)
            { // receiver node�� 2�� ��Ÿ���� ���� ����
                receiver->cNode[0]->pLink = receiver;
            }
            // transmitter�� �� ��尡 �Ǿ��� ��
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
            num = findNum(transmitter); // key ���� ���� transmitter�� key ����
        }
        // key �� �̵�
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

    if (dPnode->cNode[0] == dNode) // dNode�� ���� ���� ����� ��
    {
        // ������ node�� fusion
        // node �̵�
        dPnode->cNode[0] = dPnode->cNode[1];
        dPnode->cNode[1] = dPnode->cNode[2];
        dPnode->cNode[2] = dPnode->cNode[3];
        dPnode->cNode[3] = NULL;

        // key �� �̵�
        dPnode->cNode[0]->key[1] = dPnode->cNode[0]->key[0];
        dPnode->cNode[0]->key[0] = dPnode->key[0];
        dPnode->key[0] = dPnode->key[1];
        dPnode->key[1] = dPnode->key[2];
        dPnode->key[2] = 0;
        // child node setting
        dPnode->cNode[0]->cNode[2] = dPnode->cNode[0]->cNode[1];
        dPnode->cNode[0]->cNode[1] = dPnode->cNode[0]->cNode[0];
        dPnode->cNode[0]->cNode[0] = dNode->cNode[0];
        if (dNode->cNode[0] = NULL) // ���� ��尡 �� �� �ݺ��Ǵ� ���� ����
            dPnode->cNode[0]->cNode[0]->pLink = dPnode->cNode[0];
    }
    else // ���� ���� ��尡 �ƴ� ��
    {
        // ���� node�� fusion
        // key ���� ȸ��
        for (i = 1; i < 4; i++)
        {
            if (dPnode->cNode[i] != dNode)
                continue;
            for (j = i; j < 3; j++)
            {
                dPnode->cNode[j] = dPnode->cNode[j + 1];
            }
            dPnode->cNode[3] = NULL;
            // key �� �̵�
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