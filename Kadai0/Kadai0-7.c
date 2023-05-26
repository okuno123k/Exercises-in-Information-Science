// ★★☆☆☆
#include <stdio.h>

// xのy乗を計算する関数
double myPow(double x, int y) {
    if (y == 0) {
        // yが0の場合、1を返す
        return 1.0; 
    } else if (y < 0) {
        // yが負の場合、xを1/y乗して逆数を取る
        double result = 1.0;
        int absY = -y; // yの絶対値を取る
        for (int i = 1; i <= absY; i++) {
            result /= x;
        }
        return result;
    } else {
        // yが正の場合、xをy回乗算する
        double result = 1.0;
        for (int i = 0; i < y; i++) {
            result *= x;
        }
        return result;
    }
}

int main() {
    double x;
    int y;
    printf("実数xを入力してください。\n実数:");
    scanf("%lf",&x);
    printf("整数yを入力してください。\n整数:");
    scanf("%d",&y);
    double result = myPow(x, y);
    printf("%fの%d乗は: %fです。\n", x, y, result);

    return 0;
}
