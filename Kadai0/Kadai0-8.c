// ★★☆☆☆
#include <stdio.h>
#include <math.h>
#define PI 3.14159265359 // πの定義

int main()
{
    double t;
    printf("角度を入力してください。\n（度）: ");
    scanf("%lf", &t);

    // 度をラジアンに変換
    double theta = t * PI / 180.0;

    // 2次元座標(x,y)を原点回りにt度回転させて(x', y') へ移動させる （x=0,1,…, 10, y=0,1,…,10）
    for (int x = 0; x < 11; x++){
        for (int y = 0; y < 11; y++){
            // 原点周りに回転させる
            double x_prime = cos(theta) * x - sin(theta) * y;
            double y_prime = sin(theta) * x + cos(theta) * y;

            // 結果を表示する　　(%10.6fとすることで、右詰めで、すべての桁数が10、小数部分が6桁で表示できる)
            printf("(%10.6f, %10.6f)  →  (%10.6f, %10.6f)\n", (double)x, (double)y, x_prime, y_prime);
        }
    }

    return 0;
}