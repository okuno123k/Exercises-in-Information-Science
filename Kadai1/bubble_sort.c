#include <stdio.h>
#include <stdlib.h>

#define FLG_OFF 0
#define FLG_ON 1
#define N 20

void show(int x[], int word);
int sort[N] = {5, 1, 3, 4, 2, 10, 15, 29, 30, 2, 28, 17, 38, 4, 12, 16, 18, 39, 100, 90};

int main(void)
{
    int tmp; /*置き換え用の変数*/
    int flag;
    int i, j, k;
    int step = 0;
    int compare = 0;

    /*ここから数字の比較（バブルソート）二重繰り返し文を使う*/
    for (i = N - 2; i >= 0; i--)
    {
        flag = FLG_OFF;
        for (j = 0; j <= i; j++)
        {
            if (sort[j] > sort[j + 1])
            {
                flag = FLG_ON;
                tmp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = tmp;
                step++;
                printf("%3dステップ目: ", step);
                show(sort, N);
            }
            compare++;
        }
        if (flag == FLG_OFF)
            break;
    }
    printf("\n ソート終了:\n");
    /* 結果の表示 */
    show(sort, N);
    printf("比較回数：%d回\n", compare);
    return EXIT_SUCCESS;
}

void show(int x[], int word)
{
    for (int i = 0; i < word; i++)
    {
        printf("%d ", x[i]);
    }
    printf("\n");
}