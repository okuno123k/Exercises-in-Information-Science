// ★★★☆☆
#include <stdio.h>
#include <math.h>
#define ALLOW_ERROR 1e-9 // 許容誤差 今回は10の-9乗にしている

int main()
{
    double a, b, c, d;

    // 2つの2次元ベクトルの入力
    printf("aからdまでを入力してください\na: ");
    scanf("%lf", &a);
    printf("b: ");
    scanf("%lf", &b);
    printf("c: ");
    scanf("%lf", &c);
    printf("d: ");
    scanf("%lf", &d);

    // 2つのベクトルのx軸とy軸の比率を計算
    double ratio1 = 0.0, ratio2 = 0.0;
    // 0による除算を避けるため、0の時は割らない
    if (a != 0.0){
        ratio1 = b / a;
    }
    if (c != 0.0){
        ratio2 = d / c;
    }

    // 2つのベクトルの比率が一致するかどうかを判定
    // 2つの値の差が許容誤差より小さい場合は一致しているとする　(※fabsはdouble型の値の絶対値を取る関数)
    if (fabs(ratio1 - ratio2) < ALLOW_ERROR){
        printf("二つのベクトルは平行です。\n");
    }else{
        printf("二つのベクトルは平行でありません。\n");
    }

    return 0;
}
