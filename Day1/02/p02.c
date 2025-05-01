/* 
 * p02.c
 */

/* 
 * Usage:
 *   
 *    ./a.out X Y
 * 
 * Intended behavior
 *  It should print X * Y if both X and Y can be read as
 *  floating point numbers, or print 0 otherwise.
 *
 * Example
 *    ./a.out 1.2 2.0
 *    2.400000
 *    ./a.out a b
 *    0.000000
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char ** argv)
{
  if (argc != 3) {
    fprintf(stderr, "Usage: %s X Y\n", argv[0]);
    return 1;
  }
  
  char *endptr1, *endptr2;
  errno = 0;  // エラー状態をリセット

  double x = strtod(argv[1], &endptr1);
  if (endptr1 == argv[1] || *endptr1 != '\0' || errno == ERANGE) {
    printf("0.000000\n");
    return 0;
  }

  double y = strtod(argv[2], &endptr2);
  if (endptr2 == argv[2] || *endptr2 != '\0' || errno == ERANGE) {
    printf("0.000000\n");
    return 0;
  }

  printf("%f\n", x * y);
  return 0;
}
