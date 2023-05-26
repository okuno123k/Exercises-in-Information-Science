/*
 *   pgm ファイル入出力用ファイル
 */

#include <stdio.h>
#include <stdlib.h>
#include "pgm_io.h" 

#define RETURN_ERROR(err)  if(err != PGM_OK) return err

/*
 *  pgm_FileOpen : 指定ファイルを指定モードでオープンする
 */
FILE * pgm_FileOpen( const char filename[], char mode[] )
{
   FILE *fp;

   fp = fopen( filename, mode );

   if ( fp == NULL ) {
      pgm_ErrorComment( PGM_FILE_OPEN_ERROR );	
      exit(EXIT_FAILURE);
   }

   return fp;
}

/*
 *  pgm_FileClose : ファイルポインタのファイルをクローズする
 */
void pgm_FileClose( FILE *fp )
{
   fclose( fp );
}

/*
 *  pgm_ReadImage : pgm 形式の画像を読み込み、配列 image に格納する
 */
PGM_ERR pgm_ReadImage(FILE *fp, unsigned char image[][MAX_WIDTH], int *ph, int *pw)
{
   PGM_ERR pgm_err;

   pgm_err = pgm_ReadHeader( fp, ph, pw );
   if ( pgm_err != PGM_OK ) {
     pgm_ErrorComment( pgm_err );	
     exit(EXIT_FAILURE);
   }

   pgm_err = pgm_ReadData( fp, image, *ph, *pw );
   if ( pgm_err != PGM_OK ) {
     pgm_ErrorComment( pgm_err );	
     exit(EXIT_FAILURE);
   }

   return PGM_OK;
}

/*
 * pgm_ReadHeader : pgmファイルのヘッダー部分を読み込む
 */
PGM_ERR pgm_ReadHeader( FILE *fp, int *ph, int *pw )
{
    PGM_ERR pgm_err;
  
    pgm_err = pgm_ReadType(fp);           RETURN_ERROR(pgm_err);
    pgm_err = pgm_ReadComment(fp);        RETURN_ERROR(pgm_err);
    pgm_err = pgm_ReadSize(fp, ph, pw);   RETURN_ERROR(pgm_err);
    pgm_err = pgm_ReadComment(fp);        RETURN_ERROR(pgm_err);
    pgm_err = pgm_ReadMaxBrightness(fp);  RETURN_ERROR(pgm_err);
    pgm_err = pgm_ReadComment(fp);        RETURN_ERROR(pgm_err);

    return PGM_OK;
}

/*
 *  pgm_ReadType : ascii型のpgmファイルかどうかを判断する 
 */
PGM_ERR pgm_ReadType(FILE *fp)
{
    if ( fgetc(fp) != 'P' || fgetc(fp) != '2' ) return PGM_TYPE_ERROR;

    return PGM_OK;
}

/*
 *  pgm_ReadSize : 画像の縦横の画素数を読み込む
 */    
PGM_ERR pgm_ReadSize( FILE *fp, int *pw, int *ph )
{
    if ( fscanf(fp, "%d", pw) != SCAN_OK )  return PGM_READ_WIDTH_ERROR;
    if ( *pw > MAX_WIDTH )                  return PGM_WIDTH_SIZE_ERROR;
    if ( fscanf(fp, "%d", ph) != SCAN_OK )  return PGM_READ_HEIGHT_ERROR;
    if ( *ph > MAX_HEIGHT )                 return PGM_HEIGHT_SIZE_ERROR;

    return PGM_OK;
}

/*
 *   pgm_ReadComment : コメント文を読み飛ばす
 */
PGM_ERR pgm_ReadComment( FILE *fp )
{
   int  err;
   char buffer[MAX_BUFF_SIZE];

   fgetc(fp);
   while ( 1 ) {
       /* 空白・タブ・改行を読み飛ばす */
       fscanf(fp, "%*[ \t\n]"); 

       /* #がなければ終了 */
       if ( (err = fscanf(fp, "%1[#]", buffer)) != SCAN_OK ) break;

       /* #があれば改行の手前(この行の末尾)まで読み飛ばす */
       fscanf(fp, "%*[^\n]");
    }

   return PGM_OK;
}

/*
 *　pgm_ReadMaxBrightness : 画像が持てる最大輝度値を読み込む
 */
PGM_ERR pgm_ReadMaxBrightness( FILE *fp )
{
   int mb;

   if ( fscanf(fp, "%d", &mb) != SCAN_OK )  return PGM_READ_BRIGHTNESS_ERROR;
   if ( mb != MAX_BRIGHTNESS )              return PGM_MAX_BRIGHTNESS_ERROR;

   return PGM_OK;
}
        
/*
 *  pgm_ReadData : データ本体を読み込み、配列 image に格納する
 */
PGM_ERR pgm_ReadData( FILE *fp, unsigned char image[][MAX_WIDTH], int height, int width )
{
   int i, j;
   int brightness;

   for ( i = 0; i < height; i++ ) {
      for ( j = 0; j < width; j++ ) {
         if ( fscanf(fp, "%d", &brightness) != SCAN_OK )      return PGM_READ_DATA_ERROR;
         if ( brightness < 0 || brightness > MAX_BRIGHTNESS ) return PGM_MAX_BRIGHTNESS_ERROR;
  
         image[i][j] = (unsigned char)brightness;
      }
   }
                
   return PGM_OK;
}

/*
 *   pgm_WriteImage : pgm 形式の画像を出力する
 */
PGM_ERR pgm_WriteImage( FILE *fp, unsigned char image[][MAX_WIDTH], int height, int width )
{
   PGM_ERR pgm_err;

   pgm_err = pgm_WriteHeader( fp, height, width );
   if ( pgm_err != PGM_OK ) {
     pgm_ErrorComment( pgm_err );	
     exit(EXIT_FAILURE);
   }

   pgm_WriteData( fp, image, height, width );
   if ( pgm_err != PGM_OK ) {
     pgm_ErrorComment( pgm_err );	
     exit(EXIT_FAILURE);
   }

   fprintf( stderr, "new image is created successfully!\n" );

   return PGM_OK;
}

/*
 *   pgm_WriteHeader : pgmファイルのヘッダー部分を出力する
 */
PGM_ERR pgm_WriteHeader( FILE *fp, int height, int width )
{
   PGM_ERR pgm_err;

   pgm_err = pgm_WriteType(fp);                   RETURN_ERROR(pgm_err);
   pgm_err = pgm_WriteSize(fp, height, width);    RETURN_ERROR(pgm_err);        
   pgm_err = pgm_WriteComment(fp);                RETURN_ERROR(pgm_err);
   pgm_err = pgm_WriteMaxBrightness(fp);          RETURN_ERROR(pgm_err);

   return PGM_OK;
}

/*
 *   pgm_WruteType : ascii型のpgmファイルとして識別子を出力する
 */
PGM_ERR pgm_WriteType( FILE *fp )
{
   fprintf(fp,"%s\n", "P2");

   return PGM_OK;
}

/*
 *   pgm_WriteSize : 画像の縦横の画素数を出力する
 */
PGM_ERR pgm_WriteSize( FILE *fp, int height, int width )
{
   fprintf(fp,"%d %d\n", height, width );

   return PGM_OK;
}

/*
 *   pgm_WriteComment : コメント文を出力する
 */
PGM_ERR pgm_WriteComment( FILE *fp )
{
   /*  何もしない */

   return PGM_OK;
}

/*
 *   pgm_WriteBrightness : 画像が持てる最大輝度値を出力する
 */
PGM_ERR pgm_WriteMaxBrightness( FILE *fp )
{
   fprintf(fp,"%d\n", MAX_BRIGHTNESS );

   return PGM_OK;
}

/*
 *   pgm_WriteData : 画像データ本体を出力する
 */
PGM_ERR pgm_WriteData( FILE *fp, unsigned char image[][MAX_WIDTH], int height, int width )
{
   int i, j;

   for ( i=0; i< height; i++ ) {
      for ( j=0; j< width; j++ )
         fprintf(fp,"%d ", image[i][j] ); 
   }  

   return PGM_OK;
}

/*
 *  pgm_ErrorComment : pgm_err の値に応じたエラー文を出力する 
 */
void pgm_ErrorComment( PGM_ERR pgm_err )
{
   switch(pgm_err) {
      case PGM_FILE_OPEN_ERROR:       fprintf(stderr, "can't open file!\n");           break;
      case PGM_TYPE_ERROR:            fprintf(stderr, "file type is invalid!\n");      break;
      case PGM_READ_WIDTH_ERROR:      fprintf(stderr, "can't read width data!\n");     break;
      case PGM_WIDTH_SIZE_ERROR:      fprintf(stderr, "width size is invalid!\n");     break;
      case PGM_READ_HEIGHT_ERROR:     fprintf(stderr, "can't read height data!\n");    break;
      case PGM_HEIGHT_SIZE_ERROR:     fprintf(stderr, "height size is invalid!\n");    break;
      case PGM_READ_BRIGHTNESS_ERROR: fprintf(stderr, "can't read brightness!\n");     break;
      case PGM_MAX_BRIGHTNESS_ERROR:  fprintf(stderr, "max brightness is invalid!\n"); break;
      case PGM_READ_DATA_ERROR:       fprintf(stderr, "can't read image data!\n");     break;
      default:                                                                         break;
   }
}
