/********************************************/
// File name : main.c
// 2015003654 Lee Hoyoung
// Algorithm week2 Assignment
// Insertion Sort, Selection Sort, Bubble Sort
/********************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "insertionSort.c"
#include "selectionSort.c"
#include "bubbleSort.c"
#include "mergeSort.c"

int main()
{
    // 파일 입출력
    int arr[80000];
    char ch;
    double st, et;
    FILE *fin = fopen("C:\\Work\\Algorithm\\real_data2.txt", "r");
    FILE *fout = fopen("C:\\Work\\Algorithm\\output2.txt", "w");
    if (fin == NULL || fout == NULL)
    {
        printf("파일 오픈 실패");
        return -1;
    }
    printf("input 파일 오픈 성공\n");
    int num;
    printf("입력 데이터 유형이 무엇인가요?\n");
    printf("1.Integer\t2.Character\n");
    scanf("%d", &num);
    if (num == 1)
    {
        printf("Reading Numbers\n");
        int idx = 0;
        while (EOF != fscanf(fin, "%d", &arr[idx]))
        {
            idx++;
        }
        printf("%d\n", idx);
        int temp_idx = idx;
        printf("Sorting 방식을 선택하세요\n");
        printf("1.Insertion Sort\t2.Bubble Sort\t3.Selection Sort\n");
        printf("4.Merge Sort Recursion\t5.Merge Sort Sequential\n");
        int snum;
        scanf("%d", &snum);
        st = clock();
        switch (snum)
        {
        case 1:
            insertionSort(arr, temp_idx);
            break;
        case 2:
            bubbleSort(arr, temp_idx);
            break;
        case 3:
            selectionSort(arr, temp_idx);
            break;
        case 4:
            mergeSort_r(arr, 0, temp_idx - 1);
            break;
        case 5:
            mergeSort_s(arr, 0, temp_idx - 1);
            break;
        default:
            break;
        }
        et = clock();
        printf("걸린 시간 : %lfms\n", et - st);
        printf("Writing Numbers\n");
        for (int k = 0; k < idx; k++)
        {
            fprintf(fout, "%d ", arr[k]);
        }
        printf("output 파일 쓰기 완료\n");
    }
    else if (num == 2)
    {
        printf("Reading Characters\n");
        int idx = 0;
        while (EOF != fscanf(fin, "%c ", &arr[idx]))
        {
            idx++;
        }
        printf("%d\n", idx);
        int temp_idx = idx;
        printf("Sorting 방식을 선택하세요\n");
        printf("1.Insertion Sort\t2.Bubble Sort\t3.Selection Sort\n");
        printf("4.Merge Sort Recursion\t5.Merge Sort Sequential\n");
        int snum;
        scanf("%d", &snum);
        st = clock();
        switch (snum)
        {
        case 1:
            insertionSort(arr, temp_idx);
            break;
        case 2:
            bubbleSort(arr, temp_idx);
            break;
        case 3:
            selectionSort(arr, temp_idx);
            break;
        case 4:
            mergeSort_r(arr, 0, temp_idx - 1);
            break;
        case 5:
            mergeSort_s(arr, 0, temp_idx - 1);
            break;
        default:
            break;
        }
        et = clock();
        printf("걸린 시간 : %lfms\n", et - st);
        printf("Writing Characters\n");
        for (int k = 0; k < idx; k++)
        {
            fprintf(fout, "%c ", arr[k]);
        }
        printf("output 파일 쓰기 완료");
    }
    else
    {
        fprintf(stderr, "숫자 1, 2중 하나를 선택하시오\n");
        exit(1);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}