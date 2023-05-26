// ★★☆☆☆
#include <stdio.h>
int main(void)
{
    int a;
    double b;
    int current = 0;    // 現在の預金
    int monthCount = 0; // 何か月目か

    printf("aを入力してください。\na：");
    scanf("%d", &a);
    printf("bを入力してください。\nb：");
    scanf("%lf", &b);

    while (current <= 1000000){
        current = (current + a) * (1 + b / 100);
        monthCount++;
    }
    printf("1000000円を超えるのは%d回目です。", monthCount);
    return 0;
}