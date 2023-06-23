#include <stdio.h>
#include <stdlib.h>
#include "pgm_io.h"

/*
 * pgm_LaplacianFilter : 入力画像にラプラシアンフィルタをかける関数
 * 二次元配列と画像の高さと幅を引数として受け取り、戻り値は返さない
 */
void pgm_LaplacianFilter(unsigned char image[][MAX_WIDTH], int height, int width)
{
    int i, j;
    // 新しく同じサイズの配列を定義する。
    int buf[MAX_HEIGHT][MAX_WIDTH];
    for (i = 1; i < height - 1; i++){
        for (j = 1; j < width - 1; j++){
            // 周囲の画素(8つ)の和から対象となる画素の8倍を引く
            buf[i][j] = (int)image[i - 1][j - 1] + (int)image[i - 1][j] + (int)image[i - 1][j + 1] + (int)image[i][j - 1] + (int)image[i][j + 1] + (int)image[i + 1][j - 1] + (int)image[i + 1][j] + (int)image[i + 1][j + 1] - 8 * (int)image[i][j];
            // 計算結果が0から255の範囲内に収まるようにする。
            if (buf[i][j] > 255){
                buf[i][j] = 255;
            }else if (buf[i][j] < 0){
                buf[i][j] = 0;
            }
        }
    }
    for (i = 1; i < height - 1; i++){
        for (j = 1; j < width - 1; j++){
            // bufの配列をそのままimage配列に移す
            image[i][j] = (unsigned char)buf[i][j];
        }
    }
}

int main()
{
    const char input_file[] = "lena.pgm";
    const char output_file[] = "lena_laplacian.pgm";
    FILE *fp;
    static unsigned char image[MAX_HEIGHT][MAX_WIDTH];
    int width, height;
    /*** 画像の読み込み ***/
    // ファイルを開く
    fp = pgm_FileOpen(input_file, "r");
    // 画像の中身をimage配列に移す
    pgm_ReadImage(fp, image, &height, &width);
    // ファイルを閉じる
    pgm_FileClose(fp);
    /*** 画像処理 ***/
    // ラプラシアンフィルタを用いて画像を処理する。
    pgm_LaplacianFilter(image, height, width);
    /*** 加工画像の書き出し ***/
    fp = pgm_FileOpen(output_file, "w");
    pgm_WriteImage(fp, image, height, width);
    pgm_FileClose(fp);
    return EXIT_SUCCESS;
}
