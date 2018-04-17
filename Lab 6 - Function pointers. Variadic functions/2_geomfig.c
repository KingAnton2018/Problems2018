#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define N 3

typedef enum{
  CIRCLE = 1,
  TRIANGLE = 2,
  RECTANGLE = 3
}figure_t;

typedef struct{
  float x, y;
}point_t;

typedef struct{
  float r;
  point_t centre;
}circle_t;

typedef struct{
  point_t a, b, c;
}triangle_t;

typedef struct{
  point_t a, b, c, d;
}rectangle_t;

typedef union{
  circle_t c;
  triangle_t t;
  rectangle_t r;
}coord_t;

struct geomfig{
  int ID;
  figure_t fig;
  coord_t coord;
  void (*read_geomfig)(struct geomfig *f);
  void (*write_geomfig)(struct geomfig *f);
  float (*area)(struct geomfig *f);
};

void read_circle(struct geomfig *f)
{
  f->fig = 1;
  int ok = 1;
  printf("Introduce the radius (positive): r = ");
  if(!scanf("%f", &(f->coord.c.r)) || f->coord.c.r < 0) { ok = 0; goto check; }
  printf("Introduce the coordinates of the centre:\nx = "); 
  if(!scanf("%f", &(f->coord.c.centre.x))) { ok = 0; goto check; }
  printf("y = ");
  if(!scanf("%f", &(f->coord.c.centre.y))) { ok = 0; goto check; }
 check:
  if(!ok)
    {
      while(getchar() != '\n');
      printf("\nWrong input. Please try again\n");
      read_circle(f);
    }
}

void read_triangle(struct geomfig *f)
{
  f->fig = 2;
  int ok = 1;
  printf("Introduce the coordinates of the first point:\nx = ");
  if(!scanf("%f", &(f->coord.t.a.x))) { ok = 0; goto check; }
  printf("y = ");
  if(!scanf("%f", &(f->coord.t.a.y))) { ok = 0; goto check; }
  printf("Introduce the coordinates of the second point:\nx = ");
  if(!scanf("%f", &(f->coord.t.b.x))) { ok = 0; goto check; }
  printf("y = ");
  if(!scanf("%f", &(f->coord.t.b.y))) { ok = 0; goto check; }
  printf("Introduce the coordinates of the third point:\nx = ");
  if(!scanf("%f", &(f->coord.t.c.x))) { ok = 0; goto check; }
  printf("y = ");
  if(!scanf("%f", &(f->coord.t.c.y))) { ok = 0; goto check; }
 check:
  if(!ok)
    {
      while(getchar() != '\n');
      printf("\nWrong input. Please try again\n");
      read_triangle(f);
    }
}

void read_rectangle(struct geomfig *f)
{
  f->fig = 3;
  int ok = 1;
  printf("Introduce the coordinates of the first point:\nx = ");
  if(!scanf("%f", &(f->coord.r.a.x))) { ok = 0; goto check; }
  printf("y = ");
  if(!scanf("%f", &(f->coord.r.a.y))) { ok = 0; goto check; }
  printf("Introduce the coordinates of the second point:\nx = ");
  if(!scanf("%f", &(f->coord.r.b.x))){ ok = 0; goto check; }
  printf("y = ");
  if(!scanf("%f", &(f->coord.r.b.y))){ ok = 0; goto check; }
  printf("Introduce the coordinates of the third point:\nx = ");
  if(!scanf("%f", &(f->coord.r.c.x))){ ok = 0; goto check; }
  printf("y = ");
  if(!scanf("%f", &(f->coord.r.c.y))){ ok = 0; goto check; }
  printf("Introduce the coordinates of the fourth point:\nx = ");
  if(!scanf("%f", &(f->coord.r.d.x))){ ok = 0; goto check; }
  printf("y = ");
  if(!scanf("%f", &(f->coord.r.d.y))){ ok = 0; goto check; }
 check:
  if(!ok)
    {
      while(getchar() != '\n');
      printf("\nWrong input. Please try again\n");
      read_rectangle(f);
    }
}

float triangle_area(struct geomfig *f)
{
  float a = sqrt((f->coord.t.b.x-f->coord.t.c.x)*(f->coord.t.b.x-f->coord.t.c.x)
				 + (f->coord.t.b.y-f->coord.t.c.y)*(f->coord.t.b.y-f->coord.t.c.y));
  float b = sqrt((f->coord.t.a.x-f->coord.t.c.x)*(f->coord.t.a.x-f->coord.t.c.x)
				 + (f->coord.t.a.y-f->coord.t.c.y)*(f->coord.t.a.y-f->coord.t.c.y));
  float c = sqrt((f->coord.t.a.x-f->coord.t.b.x)*(f->coord.t.a.x-f->coord.t.b.x)
				 + (f->coord.t.a.y-f->coord.t.b.y)*(f->coord.t.a.y-f->coord.t.b.y));
  float s = (a+b+c)/3;
  return sqrt(s*(s-a)*(s-b)*(s-c));
}

float circle_area(struct geomfig *f)
{
	return M_PI * f->coord.c.r * f->coord.c.r;
}

float rectangle_area(struct geomfig *f)
{
	float l1 = sqrt((f->coord.t.a.x-f->coord.t.b.x)*(f->coord.t.a.x-f->coord.t.b.x)
				 + (f->coord.t.a.y-f->coord.t.b.y)*(f->coord.t.a.y-f->coord.t.b.y));
	float l2 = sqrt((f->coord.t.b.x-f->coord.t.c.x)*(f->coord.t.b.x-f->coord.t.c.x)
				 + (f->coord.t.b.y-f->coord.t.c.y)*(f->coord.t.b.y-f->coord.t.c.y));
	return l1*l2;
}

void write_circle(struct geomfig *f)
{
  printf("Circle: r = %.2f, O(%.2f, %.2f)\n", f->coord.c.r,
	 f->coord.c.centre.x, f->coord.c.centre.y);
}

void write_triangle(struct geomfig *f)
{
  printf("Triangle: A(%.2f, %.2f), B(%.2f, %.2f), C(%.2f, %.2f)\n",
	 f->coord.t.a.x, f->coord.t.a.y, f->coord.t.b.x, f->coord.t.b.y,
	 f->coord.t.c.x, f->coord.t.c.y);
}

void write_rectangle(struct geomfig *f)
{
  printf("Rectangle: A(%.2f, %.2f), B(%.2f, %.2f), C(%.2f, %.2f), D(%.2f, %.2f)\n",
	       f->coord.r.a.x, f->coord.r.a.y, f->coord.r.b.x, f->coord.r.b.y,
	       f->coord.r.c.x, f->coord.r.c.y, f->coord.r.d.x, f->coord.r.d.y);
}


int main(void)
{
  struct geomfig f[N];
	char type;
	for(int i = 0; i < N; i++)
		do
		{
			printf("Shape ID: %d\n",i);
			printf("What shape is it? (c = circle, t = triangle, r = rectangle) ");
			type = getchar();
			getchar();
			//printf("type = %c\n",type);
			switch(type)
			{
				case 'c':
					f[i].fig = 1;
					f[i].ID = i;
					f[i].read_geomfig = &read_circle;
					f[i].area = &circle_area;
					f[i].write_geomfig = &write_circle;
					break;
				case 't':
					f[i].fig = 2;
					f[i].ID = i;
					f[i].read_geomfig = &read_triangle;
					f[i].area = &triangle_area;
					f[i].write_geomfig = &write_triangle;
					break;
				case 'r':
					f[i].fig = 3;
					f[i].ID = i;
					f[i].read_geomfig = &read_rectangle;
					f[i].area = &rectangle_area;
					f[i].write_geomfig = &write_rectangle;
					break;
				default:
					printf("Wrong input. Try again.\n");
			}
		}while((type != 'c') && (type != 'r') && (type != 't'));
	for(int i = 0; i < N; i++)
	{
		printf("\n***Reading data for shape #%d***\n", i);
		f[i].read_geomfig(&f[i]);
	}
	printf("\nThe list of shapes is:\n");
	for(int i = 0; i < N; i++)
	{
		printf("#%d. ", i);
		f[i].write_geomfig(&f[i]);
	}
	printf("\nThe list of all rectangles area:\n");
	for(int i = 0; i < N; i++)
		if(f[i].fig == 3)
			printf("Shape #%d. Area = %f\n", i, f[i].area(&f[i]));
  return 0;
}
