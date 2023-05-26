#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm_io.h"

// プロトタイプ宣言
void pgm_VerticalFlip(unsigned char image[][MAX_WIDTH], int height, int width);
void pgm_HorizontalFlip(unsigned char image[][MAX_WIDTH], int height, int width);
void pgm_Rotate90(unsigned char image[][MAX_WIDTH], int height, int width);

int main()
{
    const char input_file[] = "girl.pgm";
    const char output_file[] = "girl_out.pgm";
    FILE *fp;
    static unsigned char image[MAX_HEIGHT][MAX_WIDTH];
    int width, height;
    int num; // 加工方法を決定する関数
    /*** 画像の読み込み ***/
    fp = pgm_FileOpen(input_file, "r");
    pgm_ReadImage(fp, image, &height, &width);
    pgm_FileClose(fp);

    /*** 画像処理 ***/
    printf("加工方法の指定\n終了：0、上下反転：1、左右反転：2、90度回転：3\n");
    while (1)
    {
        printf("数値：");
        scanf("%d", &num);
        if (num == 0){
            break;
        }else if (num == 1){
            pgm_VerticalFlip(image, height, width);
            printf("上下反転完了\n");
        }else if (num == 2){
            pgm_HorizontalFlip(image, height, width);
            printf("左右反転完了\n");
        }else if (num == 3){
            pgm_Rotate90(image, height, width);
            printf("90度回転完了\n");
        }else{
        }
    }

    /*** 加工画像の書き出し ***/
    fp = pgm_FileOpen(output_file, "w");
    pgm_WriteImage(fp, image, height, width);
    pgm_FileClose(fp);
    return EXIT_SUCCESS;
}

// pgm_VerticalFlip：上下を反転させる
void pgm_VerticalFlip(unsigned char image[][MAX_WIDTH], int height, int width)
{
    int i, j;
    unsigned char tmp;
    for (i = 0; i < height / 2; i++){
        for (j = 0; j < width; j++){
            tmp = image[i][j];
            image[i][j] = image[height - i - 1][j];
            image[height - i][j] = tmp;
        }
    }
}

// pgm_HorizontalFlip：左右を反転させる
void pgm_HorizontalFlip(unsigned char image[][MAX_WIDTH], int height, int width)
{
    int i, j;
    unsigned char tmp;
    for (i = 0; i < height; i++){
        for (j = 0; j < width / 2; j++){
            tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j] = tmp;
        }
    }
}

// pgm_Rotate90：反時計周りに90度回転させる
void pgm_Rotate90(unsigned char image[][MAX_WIDTH], int height, int width)
{
    int i, j;
    // 画像を保存する配列を定義し、memcpy関数を用いて元の画像の配列をコピーする
    static unsigned char image2[MAX_HEIGHT][MAX_WIDTH];
    memcpy(image2, image, MAX_HEIGHT * MAX_WIDTH * sizeof(unsigned char));

    for (i = 0; i < height; i++){
        for (j = 0; j < width; j++){
            image[i][j] = image2[j][width - i - 1];
        }
    }
}