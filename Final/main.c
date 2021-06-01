#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define LINES 20 // 입력받는 문장 개수
#define INF 1000 // 무한을 충분히 큰 수 1000으로 표현

typedef struct
{
    char str[500];  // 문자열을 저장하기 위한 char 배열
} string;

string DNA_String[LINES];  // 문자열 20개를 저장하기 위한 구조체 배열

int weight[LINES][LINES] = { 0, };    // 각 문자열간의 overlap 개수 저장하기 위한 2차원 배열
int travel_path[LINES] = { 0 }; // 가장 overlap이 많은 경로를 저장하기 위한 변수
int pos = 0;    // travel_path의 index를 나타내기 위해 선언한 변수
int visit[LINES] = { 0 };   // 한 번 지나간 곳을 1로 바꾼다.


int overlapCount(char* str1, char* str2)
{ // str1 앞 부분과 str2의 뒷 부분에서 overlap이 생김
    int str1Len = strlen(str1);
    int str2Len = strlen(str2);
    int m = str1Len;
    int n = str2Len;
    int i, j, cnt;
    for (i = 0; i < n; i++)
    {
        cnt = 0;
        if (str1[0] == str2[i]) // str1의 첫 번째 문자와 str2에서 같은 부분이 있을 때
        {
            for (j = 0; j < n - i; j++)
            {
                if (str1[j] == str2[i + j])
                    cnt++;
                else if (str1[j] != str2[i + j])
                    goto BREAK; // 연속적으로 문자열이 일치하는 경우를 찾아내기 위해서 사용
            }
            return cnt; // for문을 끝까지 돌았을 때만 cnt를 반환한다
        BREAK:;
        }
    }
    return 0;
}

int branch_and_bound(int matrix[LINES][LINES], int total_cost, int current)
{
    int least_cost_bound = INF; // overlap이 적은 노드로는 branch하지 않기 위해 선언
    int reduced_cost = 0;   // matrix에서 각 row에서의 최솟값과 column에서의 최솟값을 더한 cost
    int update_matrix[LINES][LINES];    //각 row와 column의 최솟값을 뺀 matrix
    int row[LINES], col[LINES]; // matrix의 각 row와 column의 최솟값을 저장하기 위한 배열
    int temp_node;
    int temp_matrix[LINES][LINES];
    visit[current] = 1;
    int recursion_time = 0;

    travel_path[pos] = current + 1; // branch and bound가 호출되는 노드를 travel path에 저장
    pos++;

    for (int i = 0; i < LINES; i++)
    {
        if (visit[i] != 1) // 아직 지나가지 않은 노드가 있다
        {
            recursion_time++;
            for (int j = 0; j < LINES; j++)
            {
                for (int k = 0; k < LINES; k++)
                {   // matrix의 current node와 다음 node의 index를 INF로 설정한다
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
                    { // row 배열에 최솟값을 넣음
                        if (update_matrix[j][k] < row[j])
                            row[j] = update_matrix[j][k];
                    }
                }
                if (row[j] == INF)
                    row[j] = 0;
                reduced_cost += row[j]; // 각 row에서 최소 비용을 reduced cost를 넣는다.
            }

            if (reduced_cost > 0)
            {
                for (int j = 0; j < LINES; j++)
                {
                    for (int k = 0; k < LINES; k++)
                    {
                        if (update_matrix[j][k] != INF) // update matrix의 값을 최솟값이 들어간 row의 값들로 빼준다.
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
                    { // 각 column에서의 최솟값을 col에 넣는다.
                        if (update_matrix[k][j] < col[j])
                            col[j] = update_matrix[k][j];
                    }
                }
                if (col[j] == INF)
                    col[j] = 0;
                reduced_cost += col[j]; // 각 column들의 최솟값들을 reduced cost에 넣는다
            }

            if (reduced_cost > 0)
            {
                for (int j = 0; j < LINES; j++)
                {
                    for (int k = 0; k < LINES; k++)
                    {
                        if (update_matrix[j][k] != INF)
                        {   // col에 있는 각 column에서의 최솟값들로 행렬값들을 뺀다.
                            update_matrix[j][k] = update_matrix[j][k] - col[k];
                        }
                        else
                            update_matrix[j][k] = update_matrix[j][k];
                    }
                }
            }

            // 더 낮은 cost의 하한이 발견된다면 하한을 업데이트한다.
            if (least_cost_bound > total_cost + matrix[current][i] + reduced_cost)
            {
                least_cost_bound = total_cost + matrix[current][i] + reduced_cost;
                // least cost bound가 있는 노드의 위치를 찾는 과정
                temp_node = i;
                for (int j = 0; j < LINES; j++)
                {
                    for (int k = 0; k < LINES; k++)
                    {   // 다음 노드로 가기위한 matrix를 저장
                        temp_matrix[j][k] = update_matrix[j][k];
                    }
                }
            }
        }
        reduced_cost = 0;
    }

    if (recursion_time < 2)
    {   // 최소 cost를 찾아서 travel path에 넣는다
        travel_path[pos] = temp_node + 1;
        return least_cost_bound;
    }
    else
    {   // least cost bound인 노드에서 다시 branch and bound 실행
        total_cost = branch_and_bound(temp_matrix, least_cost_bound, temp_node);
    }
}

int main(int argc, char const* argv[])
{
    int reduced_matrix[LINES][LINES];
    int row[LINES], col[LINES];
    int total_cost = 0;
    int len[LINES];
    // 파일 입출력 세팅
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");
    if (fin == NULL || fout == NULL)
    {
        printf("파일 오픈 실패");
        return -1;
    }
    printf("input 파일 오픈 성공\n");
    printf("Reading DNA Strings\n");
    int line = 0;
    while (EOF != fscanf(fin, "%s", DNA_String[line].str))
    {
        line++;
    }
    printf("%d lines are read complete\n", line);
    // 파일 입출력 세팅 끝
    for (int i = 0; i < LINES; i++)
    {
        printf("line %d : %s\n", i + 1, DNA_String[i].str);
    }

    for (int i = 0; i < LINES; i++)
    {
        len[i] = strlen(DNA_String[i].str);
        printf("len[%d] : %d\n", i, len[i]);
    }
    // Weight 그래프 초기화
    for (int i = 0; i < LINES; i++)
    {
        for (int j = 0; j < LINES; j++)
        {
            if (i == j)
            {
                weight[i][j] = 0;
                continue;
            }
            weight[i][j] = -1 * overlapCount(DNA_String[j].str, DNA_String[i].str); // 최소 비용을 구하는 TSP의 아이디어에서 따와 가중치를 음수로 만들어줌
        }
    }
    // Weight 그래프 출력
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
                {   // row에 있는 최솟값보다 weight가 더 작을 때 weight값으로 바꿈
                    row[i] = weight[i][j];
                }
            }
        }
        total_cost += row[i];
    }

    // 행렬의 모든 요소에서 각 row에서의 최솟값들을 빼서 reduced matrix를 만든다
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

    // weight의 각 column에 있는 값들 중 가장 작은 요소를 col에 저장
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

    // 각 column에서 가장 작은 값들을 빼서 reduced matrix 값을 설정한다
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
    // reduce된 matrix와 현재 노드까지의 total cost를 사용하여 root에서 branch and bound를 호출한다.
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
    // Superstring 출력하기
    printf("=================================superstring==========================================\n");
    for (int i = 0; i < LINES; i++)
    { // 뒤 쪽의 겹치는 부분은 출력하지 않도록 함
        if (i == LINES - 1)
        { // 마지막 줄은 한 줄을 모두 출력
            printf("%s", DNA_String[travel_path[i] - 1].str);
            fprintf(fout, "%s", DNA_String[travel_path[i] - 1].str);
            continue;
        }
        else
        {
            for (int j = 0; j < len[travel_path[i] - 1] + weight[travel_path[i] - 1][travel_path[i + 1] - 1]; j++)
            { // overlap되는 범위는 출력하지 않도록 설정
                printf("%c", DNA_String[travel_path[i] - 1].str[j]);
                fprintf(fout, "%c", DNA_String[travel_path[i] - 1].str[j]);
            }
        }
    }
    printf("\n");
    printf("output 출력 완료\n");
    fclose(fin);
    fclose(fout);
    return 0;
}