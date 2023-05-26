/*
 *   pgm ファイル入出力用ヘッダー
 */

#ifndef _PGM_IO_H_
#define _PGM_IO_H_

/*** pgmファイルの各種パラメータ最大値 ***/
#define MAX_HEIGHT      512
#define MAX_WIDTH       512
#define MAX_BRIGHTNESS  255
#define MAX_BUFF_SIZE   128

/*** スキャン判定用 ***/
#define SCAN_OK         1

/*** エラー型の定義 ***/
typedef enum {
   PGM_OK,
   PGM_FILE_OPEN_ERROR,
   PGM_TYPE_ERROR,
   PGM_READ_WIDTH_ERROR,
   PGM_WIDTH_SIZE_ERROR,
   PGM_READ_HEIGHT_ERROR,
   PGM_HEIGHT_SIZE_ERROR,
   PGM_READ_BRIGHTNESS_ERROR,
   PGM_MAX_BRIGHTNESS_ERROR,
   PGM_READ_DATA_ERROR,
} PGM_ERR;

/*** ファイル入出力関連 ***/
FILE *  pgm_FileOpen( const char [], char [] );
void    pgm_FileClose( FILE * );

/*** pgmファイル入力関連 ***/
PGM_ERR pgm_ReadImage( FILE *, unsigned char [][MAX_WIDTH], int *, int * );
PGM_ERR pgm_ReadHeader( FILE *, int *, int * );
PGM_ERR pgm_ReadType( FILE * );
PGM_ERR pgm_ReadSize( FILE *, int *, int * );
PGM_ERR pgm_ReadComment( FILE * );
PGM_ERR pgm_ReadMaxBrightness( FILE * );
PGM_ERR pgm_ReadData( FILE *, unsigned char [][MAX_WIDTH], int, int );

/*** pgmファイル出力関連 ***/
PGM_ERR pgm_WriteImage( FILE *, unsigned char [][MAX_WIDTH], int, int );
PGM_ERR pgm_WriteHeader( FILE *, int, int );
PGM_ERR pgm_WriteType( FILE * ); 
PGM_ERR pgm_WriteSize( FILE *, int, int );
PGM_ERR pgm_WriteComment( FILE * );
PGM_ERR pgm_WriteMaxBrightness( FILE * );
PGM_ERR pgm_WriteData( FILE*, unsigned char [][MAX_WIDTH], int, int );

/*** エラー表示 ***/
void pgm_ErrorComment( PGM_ERR );


#endif /* _PGM_IO_H_ */
