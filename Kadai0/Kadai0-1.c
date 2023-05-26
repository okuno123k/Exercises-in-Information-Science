// ★☆☆☆☆
#include <stdio.h>
int main(void)
{
    int n; // 整数
    double sum = 0; // 合計
    printf("数字を入力してください。\n数字：");
    scanf("%d", &n);
    
    // 1からnまで繰り返し、足し合わせる
    for (int i = 1; i <= n; i++){
        sum += 1.0 / (i * i); // 1.0にすることでdouble型の割り算にする。1の場合は整数同士の計算となり、四捨五入され、結果が整数となる。
    }
    printf("計算結果は%fです。", sum);
    return 0;
}