// ★★★☆☆
#include <stdio.h>
int main(void)
{
    int rmin, rmax, cmin, cmax;
    printf("整数rmin, rmax, cmin, cmaxを入力してください。\nrmin:");
    scanf("%d", &rmin);
    printf("rmax:");
    scanf("%d", &rmax);
    printf("cmin:");
    scanf("%d", &cmin);
    printf("cmax:");
    scanf("%d", &cmax);

    // rmin, rmax, cmin, cmaxの全てに0が入力された場合には終了する
    if (rmin == 0 && rmax == 0 && cmin == 0 && cmax == 0){
        printf("プログラムを終了します。\n");
        return 0;
    }

    // 最初の行を出力する
    printf("  |");
    if (cmin > cmax){
        // cminがcmaxより大きい時
        for (int i = cmin; i >= cmax; i--){
            printf("%4d", i);
        }
    }else{
        // cminがcmaxより小さい時
        for (int i = cmin; i <= cmax; i++){
            printf("%4d", i);
        }
    }
    printf("\n");

    // 横線を引く
    printf("--+");
    if (cmin > cmax){
        // cminがcmaxより大きい時
        for (int i = cmin; i >= cmax; i--){
            printf("----");
        }
    }else{
        // cminがcmaxより小さい時
        for (int i = cmin; i <= cmax; i++){
            printf("----");
        }
    }
    printf("-\n");


    // 行を入力する
    if (rmin > rmax){
        // rminがrmaxより大きい時
        for (int i = rmin; i >= rmax; i--){
            printf("%2d|", i);
            if (cmin > cmax){
                // cminがcmaxより大きい時
                for (int j = cmin; j >= cmax; j--){
                    printf("%4d", i * j);
                }
            }else{
                // cminがcmaxより小さい時
                for (int j = cmin; j <= cmax; j++){
                    printf("%4d", i * j);
                }
            }
            printf("\n");
        }
    }else{
        // rminがrmaxより小さい時
        for (int i = rmin; i <= rmax; i++){
            printf("%2d|", i);
            if (cmin > cmax){
                // cminがcmaxより大きい時
                for (int j = cmin; j >= cmax; j--){
                    printf("%4d", i * j);
                }
            }else{
                // cminがcmaxより小さい時
                for (int j = cmin; j <= cmax; j++){
                    printf("%4d", i * j);
                }
            }
            printf("\n");
        }
    }
    
    return 0;
}