/* 
 * p06.c
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
#include <fcntl.h>
#include <unistd.h>

int main()
{
  int fd = open("./problems/06/p06.c", O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "ファイルを開けませんでした\n");
    return 1;
  }
  char buf[100];
  while (1) {
    int n = read(fd, buf, 100);
    if (n == 0) break;
    write(1, buf, n);
  }
  return 0;
}
