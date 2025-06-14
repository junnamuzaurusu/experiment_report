/* 
 * p03.c
 */

/* 
 * usage:
 *
 *   ./a.out Ax Ay Az Bx By Bz
 *
 * Intented behavior:
 * It should print the angle between vector A and B, where
 * A is (Ax, Ay, Az)
 * B is (Bx, By, Bz), using the formula you should have learned
 * in high schools.
 *                 A * B       (dot product)
 *  cos(theta) = ---------
 *                |A| |B|
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct vect3
{
  double x;
  double y;
  double z;
} vect3;

/* dot product (naiseki) */
double dot(vect3 * A, vect3 * B)
{
  return A->x * B->x + A->y * B->y + A->z * B->z;
}

double angle(vect3 * A, vect3 * B)
{
  return acos(dot(A, B) / sqrt(dot(A, A) * dot(B, B)));
}

vect3 * mk_point(double x, double y, double z)
{
  vect3 * p = (vect3 *)malloc(sizeof(vect3));
  if (p == NULL) {
    fprintf(stderr, "メモリ割り当てに失敗しました\n");
    exit(1);
  }
  p->x = x;
  p->y = y;
  p->z = z;
  return p;
}

int main(int argc, char ** argv)
{
  if (argc != 7) {
    fprintf(stderr, "Usage: %s Ax Ay Az Bx By Bz\n", argv[0]);
    return 1;
  }
  vect3 * A = mk_point(atof(argv[1]), atof(argv[2]), atof(argv[3]));
  vect3 * B = mk_point(atof(argv[4]), atof(argv[5]), atof(argv[6]));
  double a = angle(A, B);
  printf("%f\n", a);
  free(A);
  free(B);
  return 0;
}
