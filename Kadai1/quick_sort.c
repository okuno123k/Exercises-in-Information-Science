#include <stdio.h>
#define N 20

int sort[N] = {5, 1, 3, 4, 2, 10, 15, 29, 30, 2, 28, 17, 38, 4, 12, 16, 18, 39, 100, 90};
int step = 0;
int compare = 0;

void show(int x[], int word);
void quicksort(int arr[], int left, int right);

int main(void)
{
    /* 入力データの表示 */
    printf("入力データ: \n");
    show(sort, N);
    /* ソートプログラム */

    printf("\n ソート開始:\n");
    quicksort(sort, 0, N - 1);

    printf("\n ソート終了:\n");
    /* 結果の表示 */
    show(sort, N);
    printf("比較回数：%d回\n", compare);
    return 0;
}


// 配列を表示する関数　配列と要素数を引数として受け取る
void show(int x[], int word)
{
    for (int i = 0; i < word; i++)
    {
        printf("%d ", x[i]);
    }
    printf("\n");
}

// クイックソートする関数　配列、どこからどこまでをクイックソートするかの変数を引数として受け取る
void quicksort(int sort[], int left, int right)
{
    int i, j;
    if (left >= right)
    {
        return;
    }

    // 真ん中を基準点とする
    int pivot = sort[(left + right) / 2];
    // 右側からと左から
    i = left;
    j = right;

    while (i <= j)
    {
        // 基準値より小さい場合右に移動
        while (sort[i] < pivot)
        {
            i++;
            compare++; // 比較回数を増やす
        }
        compare++;
        // 基準値より大きい場合左に移動
        while (sort[j] > pivot)
        {
            j--;
            compare++;
        }
        compare++;
        if (i <= j)
        {
            // 右と左どちらかが基準値より小さい、もしくは大きいので入れ替える
            int temp = sort[i];
            sort[i] = sort[j];
            sort[j] = temp;
            i++;
            j--;
            // 変更したので表示する
            step++;
            printf("%2dステップ目: ", step);
            show(sort, N);
        }
        compare++;
    }

    quicksort(sort, left, j);
    quicksort(sort, i, right);
}