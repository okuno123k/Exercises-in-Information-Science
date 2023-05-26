// ★☆☆☆☆
#include <stdio.h>

// 関数f(x)
double xFunction(double x) {
    if (x < -1) {
        return -1.0;
    } else if (x >= -1 && x <= 1) {
        return x;
    } else {
        return 1.0;
    }
}

int main() {
    double x;
    printf("実数xを入力してください。\n実数:");
    scanf("%lf",&x);
    printf("x=%f\n",  xFunction(x));
    return 0;
}
