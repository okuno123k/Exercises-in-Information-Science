// ★☆☆☆☆
// 標準ライブラリ使用
#include <stdio.h>
#include <math.h>

// double型を四捨五入してint型にする関数
int DoubleToInt(double num) {
    // 標準ライブラリのround関数を仕様
    return (int)round(num);
}

int main() {
    double num;
    printf("実数を入力してください。\n実数:");
    scanf("%lf",&num);
    int int_num = DoubleToInt(num);
    printf("整数に変換後:%d\n", int_num);
    return 0;
}
