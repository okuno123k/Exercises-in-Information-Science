#include <stdio.h>
#include <stdlib.h>
#include "pgm_io.h"
#define ELEMENT 9

// 中央値を求める関数　要素数が奇数の時のみ利用可能　配列を受け取り、中央値を返す。
int median(int array[])
{
    // 配列の要素数を定義
    int index = ELEMENT;

    // バブルソートを用いて並び替え
    for (int i = 0; i < ELEMENT; i++){
        for (int j = 0; j < index - 1; j++){
            if (array[j] < array[j + 1]){
                int tmp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = tmp;
            }
        }
        index = index - 1;
    }
    // 中央値を戻り値として返す
    return array[ELEMENT / 2];
}

/*
 * pgm_medianFilter : 入力画像に中央値フィルタをかける
 */
void pgm_medianFilter(unsigned char image[][MAX_WIDTH], int height, int width)
{
    int i, j;
    // 画像サイズと同じ大きさの配列を作成する。
    int buf[MAX_HEIGHT][MAX_WIDTH];
    for (i = 1; i < height - 1; i++){
        for (j = 1; j < width - 1; j++){
            // 対象画素とその周りの8つの画素からmedian関数を用いて中央値を求め、その値をbuf配列に代入する。
            int array[] = {(int)image[i - 1][j - 1], (int)image[i - 1][j], (int)image[i - 1][j + 1], (int)image[i][j - 1], (int)image[i][j], (int)image[i][j + 1], (int)image[i + 1][j - 1], (int)image[i + 1][j], (int)image[i + 1][j + 1]};
            buf[i][j] = median(array);
        }
    }
    for (i = 1; i < height - 1; i++){
        for (j = 1; j < width - 1; j++){
            // buf配列の中身をimage配列に移す
            image[i][j] = (unsigned char)buf[i][j];
        }
    }
}
int main()
{
    const char input_file[] = "lena_noise.pgm";
    const char output_file[] = "lena_median.pgm";
    FILE *fp;
    static unsigned char image[MAX_HEIGHT][MAX_WIDTH];
    int width, height;
    /*** 画像の読み込み ***/
    fp = pgm_FileOpen(input_file, "r");
    pgm_ReadImage(fp, image, &height, &width);
    pgm_FileClose(fp);
    /*** 画像処理 ***/
    pgm_medianFilter(image, height, width);
    /*** 加工画像の書き出し ***/
    fp = pgm_FileOpen(output_file, "w");
    pgm_WriteImage(fp, image, height, width);
    pgm_FileClose(fp);
    return EXIT_SUCCESS;
}
