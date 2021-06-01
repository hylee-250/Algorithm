#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define LINES 20 // �Է¹޴� ���� ����
#define INF 1000 // ������ ����� ū �� 1000���� ǥ��

typedef struct
{
    char str[500];  // ���ڿ��� �����ϱ� ���� char �迭
} string;

string DNA_String[LINES];  // ���ڿ� 20���� �����ϱ� ���� ����ü �迭

int weight[LINES][LINES] = { 0, };    // �� ���ڿ����� overlap ���� �����ϱ� ���� 2���� �迭
int travel_path[LINES] = { 0 }; // ���� overlap�� ���� ��θ� �����ϱ� ���� ����
int pos = 0;    // travel_path�� index�� ��Ÿ���� ���� ������ ����
int visit[LINES] = { 0 };   // �� �� ������ ���� 1�� �ٲ۴�.


int overlapCount(char* str1, char* str2)
{ // str1 �� �κа� str2�� �� �κп��� overlap�� ����
    int str1Len = strlen(str1);
    int str2Len = strlen(str2);
    int m = str1Len;
    int n = str2Len;
    int i, j, cnt;
    for (i = 0; i < n; i++)
    {
        cnt = 0;
        if (str1[0] == str2[i]) // str1�� ù ��° ���ڿ� str2���� ���� �κ��� ���� ��
        {
            for (j = 0; j < n - i; j++)
            {
                if (str1[j] == str2[i + j])
                    cnt++;
                else if (str1[j] != str2[i + j])
                    goto BREAK; // ���������� ���ڿ��� ��ġ�ϴ� ��츦 ã�Ƴ��� ���ؼ� ���
            }
            return cnt; // for���� ������ ������ ���� cnt�� ��ȯ�Ѵ�
        BREAK:;
        }
    }
    return 0;
}

int branch_and_bound(int matrix[LINES][LINES], int total_cost, int current)
{
    int least_cost_bound = INF; // overlap�� ���� ���δ� branch���� �ʱ� ���� ����
    int reduced_cost = 0;   // matrix���� �� row������ �ּڰ��� column������ �ּڰ��� ���� cost
    int update_matrix[LINES][LINES];    //�� row�� column�� �ּڰ��� �� matrix
    int row[LINES], col[LINES]; // matrix�� �� row�� column�� �ּڰ��� �����ϱ� ���� �迭
    int temp_node;
    int temp_matrix[LINES][LINES];
    visit[current] = 1;
    int recursion_time = 0;

    travel_path[pos] = current + 1; // branch and bound�� ȣ��Ǵ� ��带 travel path�� ����
    pos++;

    for (int i = 0; i < LINES; i++)
    {
        if (visit[i] != 1) // ���� �������� ���� ��尡 �ִ�
        {
            recursion_time++;
            for (int j = 0; j < LINES; j++)
            {
                for (int k = 0; k < LINES; k++)
                {   // matrix�� current node�� ���� node�� index�� INF�� �����Ѵ�
                    if (j == current || k == i || (k == current && j == i))
                        update_matrix[j][k] = INF;
                    else
                        update_matrix[j][k] = matrix[j][k];
                }
            }

            for (int j = 0; j < LINES; j++)
            {
                row[j] = update_matrix[j][0];
                for (int k = 0; k < LINES; k++)
                {
                    if (update_matrix[j][k] != INF)
                    { // row �迭�� �ּڰ��� ����
                        if (update_matrix[j][k] < row[j])
                            row[j] = update_matrix[j][k];
                    }
                }
                if (row[j] == INF)
                    row[j] = 0;
                reduced_cost += row[j]; // �� row���� �ּ� ����� reduced cost�� �ִ´�.
            }

            if (reduced_cost > 0)
            {
                for (int j = 0; j < LINES; j++)
                {
                    for (int k = 0; k < LINES; k++)
                    {
                        if (update_matrix[j][k] != INF) // update matrix�� ���� �ּڰ��� �� row�� ����� ���ش�.
                            update_matrix[j][k] = update_matrix[j][k] - row[j];
                        else
                            update_matrix[j][k] = update_matrix[j][k];
                    }
                }
            }
            for (int j = 0; j < LINES; j++)
            {
                col[j] = update_matrix[0][j];
                for (int k = 0; k < LINES; k++)
                {
                    if (update_matrix[k][j] != INF)
                    { // �� column������ �ּڰ��� col�� �ִ´�.
                        if (update_matrix[k][j] < col[j])
                            col[j] = update_matrix[k][j];
                    }
                }
                if (col[j] == INF)
                    col[j] = 0;
                reduced_cost += col[j]; // �� column���� �ּڰ����� reduced cost�� �ִ´�
            }

            if (reduced_cost > 0)
            {
                for (int j = 0; j < LINES; j++)
                {
                    for (int k = 0; k < LINES; k++)
                    {
                        if (update_matrix[j][k] != INF)
                        {   // col�� �ִ� �� column������ �ּڰ���� ��İ����� ����.
                            update_matrix[j][k] = update_matrix[j][k] - col[k];
                        }
                        else
                            update_matrix[j][k] = update_matrix[j][k];
                    }
                }
            }

            // �� ���� cost�� ������ �߰ߵȴٸ� ������ ������Ʈ�Ѵ�.
            if (least_cost_bound > total_cost + matrix[current][i] + reduced_cost)
            {
                least_cost_bound = total_cost + matrix[current][i] + reduced_cost;
                // least cost bound�� �ִ� ����� ��ġ�� ã�� ����
                temp_node = i;
                for (int j = 0; j < LINES; j++)
                {
                    for (int k = 0; k < LINES; k++)
                    {   // ���� ���� �������� matrix�� ����
                        temp_matrix[j][k] = update_matrix[j][k];
                    }
                }
            }
        }
        reduced_cost = 0;
    }

    if (recursion_time < 2)
    {   // �ּ� cost�� ã�Ƽ� travel path�� �ִ´�
        travel_path[pos] = temp_node + 1;
        return least_cost_bound;
    }
    else
    {   // least cost bound�� ��忡�� �ٽ� branch and bound ����
        total_cost = branch_and_bound(temp_matrix, least_cost_bound, temp_node);
    }
}

int main(int argc, char const* argv[])
{
    int reduced_matrix[LINES][LINES];
    int row[LINES], col[LINES];
    int total_cost = 0;
    int len[LINES];
    // ���� ����� ����
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");
    if (fin == NULL || fout == NULL)
    {
        printf("���� ���� ����");
        return -1;
    }
    printf("input ���� ���� ����\n");
    printf("Reading DNA Strings\n");
    int line = 0;
    while (EOF != fscanf(fin, "%s", DNA_String[line].str))
    {
        line++;
    }
    printf("%d lines are read complete\n", line);
    // ���� ����� ���� ��
    for (int i = 0; i < LINES; i++)
    {
        printf("line %d : %s\n", i + 1, DNA_String[i].str);
    }

    for (int i = 0; i < LINES; i++)
    {
        len[i] = strlen(DNA_String[i].str);
        printf("len[%d] : %d\n", i, len[i]);
    }
    // Weight �׷��� �ʱ�ȭ
    for (int i = 0; i < LINES; i++)
    {
        for (int j = 0; j < LINES; j++)
        {
            if (i == j)
            {
                weight[i][j] = 0;
                continue;
            }
            weight[i][j] = -1 * overlapCount(DNA_String[j].str, DNA_String[i].str); // �ּ� ����� ���ϴ� TSP�� ���̵��� ���� ����ġ�� ������ �������
        }
    }
    // Weight �׷��� ���
    for (int i = 0; i < LINES; i++)
    {
        for (int j = 0; j < LINES; j++)
        {
            printf("%d ", weight[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < LINES; i++)
    {
        row[i] = weight[i][0];
        for (int j = 0; j < LINES; j++)
        {
            if (weight[i][j] != INF)
            {
                if (weight[i][j] < row[i])
                {   // row�� �ִ� �ּڰ����� weight�� �� ���� �� weight������ �ٲ�
                    row[i] = weight[i][j];
                }
            }
        }
        total_cost += row[i];
    }

    // ����� ��� ��ҿ��� �� row������ �ּڰ����� ���� reduced matrix�� �����
    for (int i = 0; i < LINES; i++)
    {
        for (int j = 0; j < LINES; j++)
        {
            if (weight[i][j] != INF)
                reduced_matrix[i][j] = weight[i][j] - row[i];
            else
                reduced_matrix[i][j] = weight[i][j];
        }
    }

    // weight�� �� column�� �ִ� ���� �� ���� ���� ��Ҹ� col�� ����
    for (int i = 0; i < LINES; i++)
    {
        col[i] = reduced_matrix[0][i];
        for (int j = 0; j < LINES; j++)
        {
            if (reduced_matrix[j][i] != INF)
            {
                if (reduced_matrix[j][i] < col[i])
                {
                    col[i] = reduced_matrix[j][i];
                }
            }
        }
        total_cost += col[i];
    }

    // �� column���� ���� ���� ������ ���� reduced matrix ���� �����Ѵ�
    for (int i = 0; i < LINES; i++)
    {
        for (int j = 0; j < LINES; j++)
        {
            if (reduced_matrix[i][j] != INF)
            {
                reduced_matrix[i][j] = reduced_matrix[i][j] - col[j];
            }
            else
                reduced_matrix[i][j] = reduced_matrix[i][j];
        }
    }
    // reduce�� matrix�� ���� �������� total cost�� ����Ͽ� root���� branch and bound�� ȣ���Ѵ�.
    total_cost = branch_and_bound(reduced_matrix, total_cost, 0);
    printf("\ntraveled path: ");
    for (int i = 0; i < LINES; i++)
    {
        if (i == LINES - 1)
        {
            printf("%d", travel_path[i]);
            break;
        }
        printf("%d -> ", travel_path[i]);
    }
    printf("\ntotal travel cost: %d\n", total_cost);

    for (int i = 0; i < LINES; i++)
    {
        printf("%s\n", DNA_String[travel_path[i] - 1].str);
        if (i != LINES - 1)
            printf("%d\t%d\t%d\n", travel_path[i], -weight[travel_path[i] - 1][travel_path[i + 1] - 1], travel_path[i + 1]);
    }
    // Superstring ����ϱ�
    printf("=================================superstring==========================================\n");
    for (int i = 0; i < LINES; i++)
    { // �� ���� ��ġ�� �κ��� ������� �ʵ��� ��
        if (i == LINES - 1)
        { // ������ ���� �� ���� ��� ���
            printf("%s", DNA_String[travel_path[i] - 1].str);
            fprintf(fout, "%s", DNA_String[travel_path[i] - 1].str);
            continue;
        }
        else
        {
            for (int j = 0; j < len[travel_path[i] - 1] + weight[travel_path[i] - 1][travel_path[i + 1] - 1]; j++)
            { // overlap�Ǵ� ������ ������� �ʵ��� ����
                printf("%c", DNA_String[travel_path[i] - 1].str[j]);
                fprintf(fout, "%c", DNA_String[travel_path[i] - 1].str[j]);
            }
        }
    }
    printf("\n");
    printf("output ��� �Ϸ�\n");
    fclose(fin);
    fclose(fout);
    return 0;
}