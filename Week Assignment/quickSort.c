/*
 *  Algorithm Assignment 6
 *  Quick Sort(Recursion, Sequential)
 *  2015003654  Lee Hoyoung
 */

#include <stdlib.h>

int partition(int *arr, int p, int r)
{
    int i, j, tmp, pivot;
    pivot = arr[r];
    i = p - 1;
    for (j = p; j < r; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    arr[r] = arr[i + 1];
    arr[i + 1] = pivot;
    return i + 1;
}

void quickSort_r(int *arr, int p, int r)
{
    int q;
    if (p < r)
    {
        q = partition(arr, p, r);
        quickSort_r(arr, p, q - 1);
        quickSort_r(arr, q + 1, r);
    }
}

void quickSort_s(int *arr, int p, int r)
{
    int *q = (int *)malloc(sizeof(int) * (r - p + 1)); // pivot을 여러 개 저장할 수 있는 동적 배열 할당
    int i = -1;
    int rc = r;

    while (p < r) // pivot의 왼쪽 부분을 정렬
    {
        i++;
        q[i] = partition(arr, p, r);
        r = q[i] - 1;

        while (p >= r) // 외부 while loop 탈출하기 위한 loop
        {
            p = q[i] + 1;
            if (i == 0)
            {
                break;
            }
            else
            {
                r = q[i - 1] - 1;
                i--;
            }
        }
    }
    r = rc;
    while (p < r) // pivot의 오른쪽 부분을 정렬
    {
        i++;
        q[i] = partition(arr, p, r);
        p = q[i] + 1;
        while (p >= r) // 외부 while loop를 탈출하기 위한 loop
        {
            r = q[i] - 1;
            if (i == 0)
            {
                break;
            }
            else
            {
                p = q[i - 1] + 1;
                i--;
            }
        }
    }
    free(q);
}