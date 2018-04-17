#include <stdio.h>
#include <math.h>

#define MAX_ENTRIES 512

enum figures { RECTANGLE=0, TRIANGLE=1, CIRCLE=2};
  
typedef struct
{
  float x, y;
} point_t;

typedef struct
{
  point_t A,B,C;
} triangle_t;

typedef struct
{
  point_t A,B,C,D;
} rectangle_t;

typedef struct
{
  point_t C;
  float r;
} circle_t;

typedef union
{
  triangle_t t;
  circle_t c;
  rectangle_t r;
} shape2D_t;

typedef struct
{
  int flag_shapetype: 2;
  shape2D_t shape2D;
  float (*area)(shape2D_t *shape2D);
} entry_t;

float triangle_area (shape2D_t *shape2D)
{
  float A=0;
  A=(shape2D->t.A.x*(shape2D->t.B.y-shape2D->t.C.y)+shape2D->t.B.x*(shape2D->t.C.y-shape2D->t.A.y)+shape2D->t.C.x*(shape2D->t.A.y-shape2D->t.B.y))/2.0;
  if (A<0) return -A;
  else return A;
}
  
float rectangle_area (shape2D_t *shape2D)
{
  float xA=shape2D->r.A.x, yA=shape2D->r.A.y;
  float xB=shape2D->r.B.x, yB=shape2D->r.B.y;
  float xC=shape2D->r.C.x, yC=shape2D->r.C.y;

  float AB=sqrt((xB-xA)*(xB-xA)+(yB-yA)*(yB-yA));
  float BC=sqrt((xC-xB)*(xC-xB)+(yC-yB)*(yC-yB));

  return AB*BC;
}

float circle_area (shape2D_t *shape2D)
{
  float pi=3.141592;
  return pi*shape2D->c.r*shape2D->c.r;
}

void add_entry(entry_t *arr, unsigned *len)
{
  printf("What shape do you want to enter:\n");
  printf("0.Rectangle\n1.Triangle\n2.Circle\n");
  int sw=0;
  if(scanf("%d",&sw)!=1)
    {
      printf("Error!");
      return;
    }
 
  int size=*len;
  if (sw==RECTANGLE)
    {
      arr[size].flag_shapetype=RECTANGLE;
      
      printf("Give the first point in the format x y:\n");
      scanf("%f %f",&arr[size].shape2D.r.A.x,&arr[size].shape2D.r.A.y);

      printf("Give the second point in the format x y:\n");
      scanf("%f %f",&arr[size].shape2D.r.B.x,&arr[size].shape2D.r.B.y);

      printf("Give the third point in the format x y:\n");
      scanf("%f %f",&arr[size].shape2D.r.C.x,&arr[size].shape2D.r.C.y);

      printf("Give the fourth point in the format x y:\n");
      scanf("%f %f",&arr[size].shape2D.r.D.x,&arr[size].shape2D.r.D.y);

      arr[size].area=&rectangle_area;
    }
  else if(sw==TRIANGLE)
    {
      arr[size].flag_shapetype=TRIANGLE;
      
      printf("Give the first point in the format x y:\n");
      scanf("%f %f",&arr[size].shape2D.r.A.x,&arr[size].shape2D.r.A.y);

      printf("Give the second point in the format x y:\n");
      scanf("%f %f",&arr[size].shape2D.r.B.x,&arr[size].shape2D.r.B.y);

      printf("Give the third point in the format x y:\n");
      scanf("%f %f",&arr[size].shape2D.r.C.x,&arr[size].shape2D.r.C.y);arr[size].flag_shapetype=sw;
      arr[size].area=&triangle_area; 
    }
  else if (sw==CIRCLE)
    {
      arr[size].flag_shapetype=CIRCLE;
      
      printf("Give center in the format x y:\n");
      scanf("%f %f",&arr[size].shape2D.c.C.x,&arr[size].shape2D.c.C.y);

      printf("Give radius:\n");
      scanf("%f",&arr[size].shape2D.c.r);

       arr[size].area=&circle_area;
    }
  (*len)++;
}

void print_shapes(entry_t *arr, unsigned size)
{
  for (int i=0; i<size; i++)
    if (arr[i].flag_shapetype==RECTANGLE)
      {
	printf("RECTANGLE:\n");
	printf("(%f,%f) ",arr[i].shape2D.r.A.x,arr[i].shape2D.r.A.y);
	printf("(%f,%f) ",arr[i].shape2D.r.B.x,arr[i].shape2D.r.B.y);
	printf("(%f,%f) ",arr[i].shape2D.r.C.x,arr[i].shape2D.r.C.y);
	printf("(%f,%f)\n",arr[i].shape2D.r.D.x,arr[i].shape2D.r.D.y);
	putchar('\n'); putchar('\n');
      }
    else if (arr[i].flag_shapetype==TRIANGLE)
      {
	printf("TRIANGLE:\n");
	printf("(%f,%f) ",arr[i].shape2D.t.A.x,arr[i].shape2D.t.A.y);
	printf("(%f,%f) ",arr[i].shape2D.t.B.x,arr[i].shape2D.t.B.y);
	printf("(%f,%f)\n",arr[i].shape2D.t.C.x,arr[i].shape2D.t.C.y);
	putchar('\n'); putchar('\n');
      }
    else
      {
	printf("CIRCLE:\n");
	printf("(%f,%f) ",arr[i].shape2D.c.C.x,arr[i].shape2D.c.C.y);
	printf("%f\n",arr[i].shape2D.c.r);
	putchar('\n'); putchar('\n');
      }
  
}

void del_shape(entry_t *arr, unsigned *size)
{
  int index=0;
  printf("Give the index for deleting:\n");
  scanf("%d",&index);
  index=index-1;
  if (index>=(*size)) return;
  
  for (int i=index;i<(*size)-1;i++)
    arr[i]=arr[i+1];
  (*size)--;
}

int main (void)
{
  entry_t shapesarr[MAX_ENTRIES];
  unsigned len=0;
  unsigned sw=1;
  while (sw>0&&sw<4)
    {
      printf("0.Exit\n1.Add shape\n2.List shape\n3.Delete shapes based on index\n");
      scanf("%u",&sw);
      if (sw==1)
	add_entry(shapesarr,&len);
      else if (sw==2)
	print_shapes(shapesarr,len);
      else if (sw==3)
        del_shape(shapesarr,&len);
    }
  for (int i=0;i<len;i++)
    {
      if (shapesarr[i].flag_shapetype==RECTANGLE)
	printf("%f ",shapesarr[i].area(&shapesarr[i].shape2D));
    }
}
