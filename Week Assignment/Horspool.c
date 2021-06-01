/*
 *  Algorithm W7 Assignment
 *  2015003654 Lee Hoyoung
 *  Horspool Algorithm  
 */

#include <stdio.h>

int table[500];

int horspool(int *text, int *pattern, int tLength, int pLength)
{
    int temp[pLength];
    int count;
    int k;
    int idx;

    for (int i = 0; i < pLength - 1; i++)
    {
        temp[i] = pLength - i - 1;
    }
    for (int i = 0; i < 500; i++)
    {
        table[i] = pLength;
    }
    for (int i = 0; i < pLength; i++)
    {
        table[pattern[i]] = temp[i];
    }
    idx = pLength - 1;
    while (idx <= tLength)
    {
        count = pLength - 1;
        k = idx;
        while (count >= 0 && text[k] == pattern[count])
        {
            count--;
            k--;
            if (count == -1)
                return k + 1;
        }
        idx += table[text[k]];
    }
    return -1;
}

int main()
{
    int result;
    int text[] = {'T', 'R', 'U', 'T', 'H', 'L', 'E', 'A', 'D', 'S', 'Y', 'O', 'U', 'T', 'O', 'F', 'R', 'E', 'E', 'D', 'O', 'M'};
    int pattern1[] = {'T', 'R', 'U', 'T', 'H'};
    int pattern2[] = {'F', 'R', 'E', 'E', 'D', 'O', 'M'};
    result = horspool(text, pattern1, sizeof(text) / sizeof(int), sizeof(pattern1) / sizeof(int));
    printf("%d번째에서 pattern이 발견됨\n", result);
    result = horspool(text, pattern2, sizeof(text) / sizeof(int), sizeof(pattern2) / sizeof(int));
    printf("%d번째에서 pattern이 발견됨\n", result);
}