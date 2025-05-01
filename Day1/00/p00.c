/* 
 * p00.c
 */

/* 
 * usage:
 * 
 *   ./a.out
 *
 * Intented behavior:
 * It should print the content of this file.
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *fp = fopen("./problems/00/p00.c", "rb");
  if (fp == NULL) {
    fprintf(stderr, "ファイルを開けませんでした。\n");
    return 1;
  }

  while (1) {
    int c = fgetc(fp);
    if (c == EOF) break;
    fputc(c, stdout);
  }

  if (ferror(fp)) {
    fprintf(stderr, "読み込みエラーが発生しました。\n");
    fclose(fp);
    return 1;
  }

  fclose(fp);
  return 0;
}
