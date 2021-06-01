/****************************************/
//  Algorithm 주별 과제 4
//  Merge Sort - Sequential, Recursion
//  2015003654 이호영
/****************************************/
//#include <stdlib.h>
//#include <stdio.h>

int arrn[70000];

void merge(int *arr, int s, int m, int e)
{
    int i, j, k;
    i = s;
    j = m + 1;
    k = s;
    //printf("i = %d, j = %d\n", i, j);
    int n = e - s + 1;
    while (i <= m && j <= e)
    {
        if (arr[i] < arr[j])
        {
            arrn[k] = arr[i];
            //printf("i - arrn[%d] = %d\n", k, arrn[k]);
            i++;
        }
        else
        {
            arrn[k] = arr[j];
            //printf("j - arrn[%d] = %d\n", k, arrn[k]);
            j++;
        }
        k++;
    }
    if (i > m)
    {
        for (int t = j; t <= e; t++)
        {
            arrn[k] = arr[t];
            //printf("j remain - arrn[%d] = %d\n", k, arrn[k]);
            k++;
        }
    }
    else
    {
        for (int t = i; t <= m; t++)
        {
            arrn[k] = arr[t];
            //printf("i remain - arrn[%d] = %d\n", k, arrn[k]);
            k++;
        }
    }
    //printf("원래 배열에 복사\n");
    for (int t = 0; t < n; t++)
    {
        arr[s + t] = arrn[s + t];
        //printf("arrn[%d] = %d\n", s + t, arrn[s + t]);
    }
    /*
    free(arrn);
    if (arrn == NULL)
    {
        printf("size %d 배열 동적할당 해제\n", n);
    }
    */
}

// Recursive Merge Sort
void mergeSort_r(int *arr, int s, int e)
{
    if (s < e)
    {
        int m = (s + e) / 2;
        mergeSort_r(arr, s, m);
        mergeSort_r(arr, m + 1, e);
        merge(arr, s, m, e);
    }
}

// Sequential Merge Sort
void mergeSort_s(int *arr, int s, int e)
{
    int n = e - s + 1;
    int gap = 2;
    int i, j, m;
    for (; gap <= n; gap *= 2)
    {
        //printf("gap : %d\n", gap);
        i = s;
        j = i + gap - 1;
        m = (i + j) / 2;
        while (i < e)
        {
            merge(arr, i, m, j);
            i = j + 1;
            j = i + gap - 1;
            if (j > e)
            {
                j = e;
            }
            m = (i + j) / 2;
            //printf("sequential - i = %d, j = %d, m = %d\n", i, j, m);
        }
    }
    gap /= 2;
    merge(arr, s, s + gap - 1, e);
}