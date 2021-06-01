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
    // ���� �����
    int arr[80000];
    char ch;
    double st, et;
    FILE *fin = fopen("C:\\Work\\Algorithm\\real_data2.txt", "r");
    FILE *fout = fopen("C:\\Work\\Algorithm\\output2.txt", "w");
    if (fin == NULL || fout == NULL)
    {
        printf("���� ���� ����");
        return -1;
    }
    printf("input ���� ���� ����\n");
    int num;
    printf("�Է� ������ ������ �����ΰ���?\n");
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
        printf("Sorting ����� �����ϼ���\n");
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
        printf("�ɸ� �ð� : %lfms\n", et - st);
        printf("Writing Numbers\n");
        for (int k = 0; k < idx; k++)
        {
            fprintf(fout, "%d ", arr[k]);
        }
        printf("output ���� ���� �Ϸ�\n");
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
        printf("Sorting ����� �����ϼ���\n");
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
        printf("�ɸ� �ð� : %lfms\n", et - st);
        printf("Writing Characters\n");
        for (int k = 0; k < idx; k++)
        {
            fprintf(fout, "%c ", arr[k]);
        }
        printf("output ���� ���� �Ϸ�");
    }
    else
    {
        fprintf(stderr, "���� 1, 2�� �ϳ��� �����Ͻÿ�\n");
        exit(1);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}