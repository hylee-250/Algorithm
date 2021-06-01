/*
 *  Algorithm Midterm Assignment
 *  2015003654 Lee Hoyoung
 *  234-Tree(Select mode)
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "delete.c"
#define MAX_LENGTH 500

void printNode(TreeNode *);
void printTree(TreeNode *);
void fprintNode(TreeNode *);
void fprintTree(TreeNode *);

FILE *fin, *fout;

// ���� �Է� ���� �� interaction mode�� batch ���� ����
int main(int argc, char *argv[])
{
    int mNum; // mode number�� �Է� ���� ����
    char cin; // command�� integer�� �Է� ���� ����
    int iin;
    int check;
    char *fileString;

    root = nodeInit();
    level = 1;
    printf("1.Interation mode\t2.Batch mode\n");
    printf("Please select mode: ");
    scanf("%d", &mNum);
    if (mNum == 1)
    {
        // Interaction mode
        printf("**********************************Interation mode start********************************************\n");
        printf("Insert : i\tDelete: d\tSearch: s\tQuit: q0\n");
        while (1)
        {
            scanf("%c%d", &cin, &iin);
            if (cin == 'i')
            {
                insert(root, iin);
                printf("i%d\n", iin);
                printTree(root);
            }
            else if (cin == 'd')
            {
                printf("d%d\n", iin);
                delete (root, iin);
                printTree(root);
            }
            else if (cin == 's')
            {
                printf("s%d\n", iin);
                check = search(root, iin);
                if (check != -1)
                {
                    printf("%d exists\n", iin);
                }
                else
                {
                    printf("%d not exists\n", iin);
                }
            }
            else if (cin == 'q')
            {
                break;
            }
            else
                continue;
            printf("\n");
        }
    }
    else if (mNum == 2)
    {
        // Batch mode
        printf("**********************************Batch mode start*************************************************\n");

        // // �Ķ���� Ȯ��
         if (argc != 2)
         {
             printf("No parameter\n");
             exit(1);
         }

         fileString = argv[1];
         if (fopen_s(&fin, fileString, "r") != 0)
         {
             printf("No %s\n", fileString);
             exit(1);
         }
         if (fopen_s(&fout, "output.txt", "w") != 0)
         {
             printf("Error\n");
             exit(1);
         }

        // visual studio code�� input ���� ��� �μ� ���� ����� ã�� ���ؼ�
        // �ε����ϰ� ��� ������ �ϰ� �Ǿ����ϴ�.
        //fin = fopen("C:\\Work\\C_Projects\\Algorithm\\Assignment\\Midterm\\input.txt", "r");
        //fout = fopen("C:\\Work\\C_Projects\\Algorithm\\Assignment\\Midterm\\output.txt", "w");
        //if (fin == NULL || fout == NULL)
        //{
        //    printf("���� ���� ����\n");
         //   return -1;
        //}
        //printf("input ���� ���� ����\n");
        while (1)
        {
            if (EOF == fscanf(fin, "%c%d", &cin, &iin))
            {
                fclose(fin);
                fclose(fout);

                printf("Finished\n");
                return 0;
            }
            if (cin == 'i')
            {
                insert(root, iin);
                fprintf(fout, "i%d\n", iin);
                fprintTree(root);
            }
            else if (cin == 'd')
            {
                delete (root, iin);
                fprintf(fout, "d%d\n", iin);
                fprintTree(root);
            }
            else if (cin == 's')
            {
                check = search(root, iin);
                fprintf(fout, "s%d\n", iin);
                if (check != -1)
                {
                    fprintf(fout, "exists\n");
                }
                else
                {
                    fprintf(fout, "not exists\n");
                }
            }
            fprintf(fout, "\n");
        }
    }
    else
    {
        printf("1�� 2 �� �ϳ��� �������ּ���.\n");
    }
}

void printNode(TreeNode *targetNode)
{
    if (targetNode->key[0] == 0)
        return;
    else if (targetNode->key[1] == 0)
    {
        printf("(%d) ", targetNode->key[0]);
    }
    else if (targetNode->key[2] == 0)
    {
        printf("(%d %d) ", targetNode->key[0], targetNode->key[1]);
    }
    else
    {
        printf("(%d %d %d) ", targetNode->key[0], targetNode->key[1], targetNode->key[2]);
    }
}

void printTree(TreeNode *targetNode)
{
    int i, j, k;
    int cnt;                         // �� �ٿ� �ִ� node ��
    TreeNode *node1[MAX_LENGTH];     // level Ȧ�� ��° node�� ����
    TreeNode *node2[MAX_LENGTH];     // level Ȧ�� ��° node�� ����
    memset(node1, 0, sizeof(node1)); // node1�� 0���� �ʱ�ȭ
    memset(node2, 0, sizeof(node2)); // node2�� 0���� �ʱ�ȭ
    node1[0] = targetNode;

    for (i = 0; i < level; i++)
    {
        cnt = 0;
        if (i % 2 == 0)
        {
            for (j = 0; j < MAX_LENGTH; j++)
            {
                if (node1[j] == NULL)
                {
                    break;
                }
                printNode(node1[j]);
                // child node���� node2�� ����
                for (int k = 0; k < 4; k++)
                {
                    if (node1[j]->cNode[k] == NULL)
                        break;
                    node2[cnt] = node1[j]->cNode[k];
                    cnt++;
                }
            }
        }
        else
        {
            for (j = 0; j < MAX_LENGTH; j++)
            {
                if (node2[j] == NULL)
                    break;
                printNode(node2[j]);
                // child node���� node1�� ����
                for (k = 0; k < 4; k++)
                {
                    if (node2[j]->cNode[k] == NULL)
                        break;
                    node1[cnt] = node2[j]->cNode[k];
                    cnt++;
                }
            }
        }
        printf("\n");
    }
}

void fprintNode(TreeNode *targetNode)
{
    if (targetNode->key[0] == 0)
        return;
    else if (targetNode->key[1] == 0)
    {
        fprintf(fout, "(%d) ", targetNode->key[0]);
    }
    else if (targetNode->key[2] == 0)
    {
        fprintf(fout, "(%d %d) ", targetNode->key[0], targetNode->key[1]);
    }
    else
    {
        fprintf(fout, "(%d %d %d) ", targetNode->key[0], targetNode->key[1], targetNode->key[2]);
    }
}

void fprintTree(TreeNode *targetNode)
{
    int i, j, k;
    int cnt;                         // �� �ٿ� �ִ� node ��
    TreeNode *node1[MAX_LENGTH];     // level Ȧ�� ��° node�� ����
    TreeNode *node2[MAX_LENGTH];     // level Ȧ�� ��° node�� ����
    memset(node1, 0, sizeof(node1)); // node1�� 0���� �ʱ�ȭ
    memset(node2, 0, sizeof(node2)); // node2�� 0���� �ʱ�ȭ
    node1[0] = targetNode;

    for (i = 0; i < level; i++)
    {
        cnt = 0;
        if (i % 2 == 0)
        {
            for (j = 0; j < MAX_LENGTH; j++)
            {
                if (node1[j] == NULL)
                {
                    break;
                }
                fprintNode(node1[j]);
                // child node���� node2�� ����
                for (int k = 0; k < 4; k++)
                {
                    if (node1[j]->cNode[k] == NULL)
                        break;
                    node2[cnt] = node1[j]->cNode[k];
                    cnt++;
                }
            }
        }
        else
        {
            for (j = 0; j < MAX_LENGTH; j++)
            {
                if (node2[j] == NULL)
                    break;
                fprintNode(node2[j]);
                // child node���� node1�� ����
                for (k = 0; k < 4; k++)
                {
                    if (node2[j]->cNode[k] == NULL)
                        break;
                    node1[cnt] = node2[j]->cNode[k];
                    cnt++;
                }
            }
        }
        fprintf(fout, "\n");
    }
}