#include <stdio.h>
#define N 20 // データ数

int sort[N] = {5, 1, 3, 4, 2, 10, 15, 29, 30, 2, 28, 17, 38, 4, 12, 16, 18, 39, 100, 90};
void show(int x[], int word);

// マージソート
void mergeSort(int sort[], int tmp[], int left, int right);
void merge(int sort[], int tmp[], int left, int mid, int right);
int step = 0;
int compare = 0;

int main(void)
{
    int tmp[N]; // 配列を保管するための配列
    /* 入力データの表示 */
    printf("入力データ: \n");
    show(sort, N);
    /* ソートプログラム */
    printf("\n ソート開始:\n");
    mergeSort(sort, tmp, 0, N - 1);
    printf("\n ソート終了:\n");
    /* 結果の表示 */
    show(sort, N);
    printf("比較回数：%d回\n", compare);
    return 0;
}

// マージソート
void mergeSort(int sort[], int tmp[], int left, int right)
{
    int mid;

    // データ数が１の場合は終了
    if (left >= right)
    {
        return;
    }

    // 集合を中央で分割する
    mid = (left + right) / 2;
    // 左右をそれぞれソートする(再帰関数)
    mergeSort(sort, tmp, left, mid);
    mergeSort(sort, tmp, mid + 1, right);

    // ソートされた二つの配列をマージする
    merge(sort, tmp, left, mid, right);
}

// マージする
void merge(int sort[], int tmp[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left; // マージ後の配列のインデックス

    while (i <= mid && j <= right)
    {
        if (sort[i] <= sort[j])
        {
            tmp[k] = sort[i];
            i++;
        }
        else
        {
            tmp[k] = sort[j];
            j++;
        }
        compare++;
        k++;
    }

    // 左側の要素が残っている場合、残りの要素をtmpにコピーする
    while (i <= mid)
    {
        tmp[k] = sort[i];
        i++;
        k++;
    }

    // 右側の要素が残っている場合、残りの要素をtmpにコピーする
    while (j <= right)
    {
        tmp[k] = sort[j];
        j++;
        k++;
    }
    
    // tmpの要素をsortにコピーする
    for (int l = left; l <= right; l++)
    {
        sort[l] = tmp[l];
    }
    step++;
    printf("%2dステップ目: ", step);
    show(sort, N);
}

void show(int x[], int word)
{
    for (int i = 0; i < word; i++)
    {
        printf("%d ", x[i]);
    }
    printf("\n");
}
