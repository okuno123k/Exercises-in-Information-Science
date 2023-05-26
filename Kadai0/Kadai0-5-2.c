// ★★☆☆☆
// 標準ライブラリ未使用
#include <stdio.h>

// double型を四捨五入してint型にする関数
int DoubleToInt(double num)
{
    int int_num;
    if (num >= 0){
        // 0.5を足して小数点を切り捨て
        int_num = (int)(num + 0.5);
    }else{
        // 0.5を引いて小数点を切り捨て
        int_num = (int)(num - 0.5);
    }
    return int_num;
}

int main() {
    double num;
    printf("実数を入力してください。\n実数:");
    scanf("%lf",&num);
    int int_num = DoubleToInt(num);
    printf("整数に変換後:%d\n", int_num);
    return 0;
}