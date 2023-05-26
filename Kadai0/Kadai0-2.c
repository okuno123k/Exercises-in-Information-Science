// ★★☆☆☆
#include <stdio.h>
int main(void)
{
    int n, maxIndex=0; // 整数n,最大値が何番目か
    double max=0,currentNum=0; // 最大値、入力した数

    printf("nを入力してください。");
    scanf("%d",&n);

    // 入力した数が最大値より大きい場合その値を最大値に代入
    for (int i=1; i<=n; i++){
        printf("%d番目の数値を入力してください。",i);
        scanf("%lf",&currentNum);
        if(currentNum >= max){
            max = currentNum;
            maxIndex=i;
        }
    }
    printf("最も大きい数字は%d番目です。",maxIndex);
    return 0;
}