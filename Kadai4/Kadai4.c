#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#define _USE_MATH_DEFINES /*M\PI_を使うための宣言*/
#define GNUPLOT_PATH "gnuplot.exeへのPATH"
#define DEG2RAD (M_PI / 180.0)
#define RAD2DEG (180.0 / M_PI)
#define GP_GREEN 2     /* gnuplot の仕様 */
#define GP_ROT_X 60    /* [deg] */
#define DELTA_DEGREE 1 /* [deg] */
#define SEC 1000000    /* [usec] */
#define WAIT_TIME (0.1 * SEC)
/*構造体の宣言*/
typedef struct plane_map
{
    double longitude; /* [deg] */
    double latitude;  /* [deg] */
} PLANE_MAP_TYPE;
typedef struct sphere_map
{
    double x;
    double y;
    double z;
} SPHERE_MAP_TYPE;

/*プロトタイプ宣言*/
void SphereMap(const char *, const char *);
void DrawMapData(const char *);
SPHERE_MAP_TYPE convert2Dto3D(PLANE_MAP_TYPE coordinates);

int main()
{
    const char plane_map[] = "world.dat";
    const char sphere_map[] = "world_sphere.dat";
    SphereMap(plane_map, sphere_map);
    DrawMapData(sphere_map);
    return EXIT_SUCCESS;
}

/*
 * 平面地図(world.dat)のデータを半径 1 の球面上の球面地図ファイル sphere_map を作成する
 */
void SphereMap(const char *plane_map, const char *sphere_map)
{
    FILE *fp_p, *fp_s;
    PLANE_MAP_TYPE data_p;
    SPHERE_MAP_TYPE data_s;
    fp_p = fopen(plane_map, "r");
    fp_s = fopen(sphere_map, "w");
    /* --- ここから --- */
    double x, y;
    char sentence[50];
    while (fgets(sentence, sizeof(sentence), fp_p) != NULL){
        // 行がコメント行でないか確認
        if (sentence[0] != '#' && sentence[0] != '\n'){
            // 数字の読み込み
            sscanf(sentence, "%lf %lf", &data_p.longitude, &data_p.latitude);
            data_s = convert2Dto3D(data_p);
            fprintf(fp_s, "%f %f %f\n", data_s.x, data_s.y, data_s.z);
        }else{
            fprintf(fp_s, "\n");
        }
    }
    /* --- ここまで --- */
    fclose(fp_p);
    fclose(fp_s);
}

/*
* gnuplot で球面地図データを描画する
*/
void DrawMapData(const char *sphere_map)
{
    FILE *gp;
    int gp_rot_z;
    gp = popen(GNUPLOT_PATH, "w");
    fprintf(gp, "unset xtics\n");
    fprintf(gp, "unset ytics\n");
    fprintf(gp, "unset ztics\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "unset border\n");
    fprintf(gp, "set size square\n");
    // パラメータ設定の前にデータファイルを指定する
    for (gp_rot_z = (int)(2.0 * M_PI * RAD2DEG); gp_rot_z > 0; gp_rot_z -= DELTA_DEGREE){
        fprintf(gp, "set view %d, %d\n", GP_ROT_X, gp_rot_z);
        fprintf(gp, "set parametric\n");
        fprintf(gp, "splot '%s' with lines,", sphere_map);
        fprintf(gp, "cos(u)*cos(v), cos(u)*sin(v), sin(u) lt %d\n", GP_GREEN);
        fflush(gp);
        usleep(WAIT_TIME);
    }
    pclose(gp);
}

/*緯度と経度をxyz座標に変換する関数　double型2つの構造体を引数とし、double型3つの構造体を戻り値とする。*/
SPHERE_MAP_TYPE convert2Dto3D(PLANE_MAP_TYPE coordinates)
{
    SPHERE_MAP_TYPE XYZPosition; /*xyz座標*/
    double lat_rad = coordinates.latitude * DEG2RAD;
    double lon_rad = coordinates.longitude * DEG2RAD;
    XYZPosition.x = cos(lat_rad) * cos(lon_rad);
    XYZPosition.y = cos(lat_rad) * sin(lon_rad);
    XYZPosition.z = sin(lat_rad);
    return XYZPosition;
}