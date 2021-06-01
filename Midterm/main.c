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

// 숫자 입력 받은 후 interaction mode와 batch 모드로 나뉨
int main(int argc, char *argv[])
{
    int mNum; // mode number를 입력 받을 변수
    char cin; // command와 integer을 입력 받을 변수
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

        // // 파라미터 확인
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

        // visual studio code의 input 파일 명령 인수 설정 방법을 찾지 못해서
        // 부득이하게 경로 설정을 하게 되었습니다.
        //fin = fopen("C:\\Work\\C_Projects\\Algorithm\\Assignment\\Midterm\\input.txt", "r");
        //fout = fopen("C:\\Work\\C_Projects\\Algorithm\\Assignment\\Midterm\\output.txt", "w");
        //if (fin == NULL || fout == NULL)
        //{
        //    printf("파일 오픈 실패\n");
         //   return -1;
        //}
        //printf("input 파일 오픈 성공\n");
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
        printf("1과 2 중 하나를 선택해주세요.\n");
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
    int cnt;                         // 한 줄에 있는 node 수
    TreeNode *node1[MAX_LENGTH];     // level 홀수 번째 node들 저장
    TreeNode *node2[MAX_LENGTH];     // level 홀수 번째 node들 저장
    memset(node1, 0, sizeof(node1)); // node1을 0으로 초기화
    memset(node2, 0, sizeof(node2)); // node2를 0으로 초기화
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
                // child node들을 node2에 저장
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
                // child node들을 node1에 저장
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
    int cnt;                         // 한 줄에 있는 node 수
    TreeNode *node1[MAX_LENGTH];     // level 홀수 번째 node들 저장
    TreeNode *node2[MAX_LENGTH];     // level 홀수 번째 node들 저장
    memset(node1, 0, sizeof(node1)); // node1을 0으로 초기화
    memset(node2, 0, sizeof(node2)); // node2를 0으로 초기화
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
                // child node들을 node2에 저장
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
                // child node들을 node1에 저장
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