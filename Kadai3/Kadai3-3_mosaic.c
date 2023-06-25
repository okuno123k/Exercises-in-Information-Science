#include <stdio.h>
#include <stdlib.h>
#include "pgm_io.h"

/*
 * pgm_mosaic : モザイクをかける関数
 */
void pgm_mosaic(unsigned char image[][MAX_WIDTH], int height, int width)
{
    int i, j;
    int n = 16;
    unsigned char buf[MAX_HEIGHT][MAX_WIDTH];
    for (i = 1; i < height - 1; i++)
    {
        for (j = 1; j < width - 1; j++)
        {
            int i_0 = (int)i / n;
            int j_0 = (int)j / n;
            int p_d = i % n;
            int q_d = j % n;
            int p, q;
            if (p_d % 2 == 1){
                p = n - p_d;
            }else{
                p = (p_d + n / 2) % n;
            }
            if (q_d % 2 == 1){
                q = n - q_d;
            }else{
                q = (q_d + n / 2) % n;
            }
            buf[i][j] = image[i_0 * n + p][j_0 * n + q];
        }
    }
    for (i = 1; i < height - 1; i++){
        for (j = 1; j < width - 1; j++){
            image[i][j] = (unsigned char)buf[i][j];
        }
    }
}
int main()
{
    const char input_file[] = "pixelated_picture.pgm";
    const char output_file[] = "mosaic.pgm";
    FILE *fp;
    static unsigned char image[MAX_HEIGHT][MAX_WIDTH];
    int width, height;
    /*** 画像の読み込み ***/
    fp = pgm_FileOpen(input_file, "r");
    pgm_ReadImage(fp, image, &height, &width);
    pgm_FileClose(fp);
    /*** 画像処理 ***/
    pgm_mosaic(image, height, width);
    /*** 加工画像の書き出し ***/
    fp = pgm_FileOpen(output_file, "w");
    pgm_WriteImage(fp, image, height, width);
    pgm_FileClose(fp);
    return EXIT_SUCCESS;
}
