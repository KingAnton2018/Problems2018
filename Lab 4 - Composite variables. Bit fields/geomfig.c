#include <stdio.h>
#include <ctype.h>

unsigned n;

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

typedef struct {
	figure_t fig;
	coord_t coord;
}geomfig_t;

void read_coord(geomfig_t f[])
{
	char c;
	int ok = 1;
	printf("Press c for circle, t for triangle, or r for rectangle: ");
	c = getchar();
	switch(c)
	{
		case 'c':
			f[n].fig = 1;
			printf("Introduce the radius (positive): r = ");
			if(!scanf("%f", &f[n].coord.c.r) || f[n].coord.c.r < 0) { ok = 0; goto check; }
			printf("Introduce the coordinates of the centre:\nx = "); 
			if(!scanf("%f", &f[n].coord.c.centre.x)) { ok = 0; goto check; }
			printf("y = ");
			if(!scanf("%f", &f[n].coord.c.centre.y)) { ok = 0; goto check; }
			break;
		case 't':
			f[n].fig = 2;
			printf("Introduce the coordinates of the first point:\nx = ");
			if(!scanf("%f", &f[n].coord.t.a.x)) { ok = 0; goto check; }
			printf("y = ");
			if(!scanf("%f", &f[n].coord.t.a.y)) { ok = 0; goto check; }
			printf("Introduce the coordinates of the second point:\nx = ");
			if(!scanf("%f", &f[n].coord.t.b.x)) { ok = 0; goto check; }
			printf("y = ");
			if(!scanf("%f", &f[n].coord.t.b.y)) { ok = 0; goto check; }
			printf("Introduce the coordinates of the third point:\nx = ");
			if(!scanf("%f", &f[n].coord.t.c.x)) { ok = 0; goto check; }
			printf("y = ");
			if(!scanf("%f", &f[n].coord.t.c.y)) { ok = 0; goto check; }
			break;
		case 'r':
			f[n].fig = 3;
			printf("Introduce the coordinates of the first point:\nx = ");
			if(!scanf("%f", &f[n].coord.r.a.x)) { ok = 0; goto check; }
			printf("y = ");
			if(!scanf("%f", &f[n].coord.r.a.y)) { ok = 0; goto check; }
			printf("Introduce the coordinates of the second point:\nx = ");
			if(!scanf("%f", &f[n].coord.r.b.x)){ ok = 0; goto check; }
			printf("y = ");
			if(!scanf("%f", &f[n].coord.r.b.y)){ ok = 0; goto check; }
			printf("Introduce the coordinates of the third point:\nx = ");
			if(!scanf("%f", &f[n].coord.r.c.x)){ ok = 0; goto check; }
			printf("y = ");
			if(!scanf("%f", &f[n].coord.r.c.y)){ ok = 0; goto check; }
			printf("Introduce the coordinates of the fourth point:\nx = ");
			if(!scanf("%f", &f[n].coord.r.d.x)){ ok = 0; goto check; }
			printf("y = ");
			if(!scanf("%f", &f[n].coord.r.d.y)){ ok = 0; goto check; }
			break;
		default: ok = 0;	
	}
check:
	if(ok) n++;
	else
	{
		while((c = getchar()) != '\n');
		printf("\nWrong input. Please try again\n");
		read_coord(f);
	}
}

void print_all(geomfig_t f[])
{
	if(n == 0)
	{
		printf("There are no entries.\n");
		return;
	}
	for(int i = 0; i < n; ++i)
	{
		printf("%d. ", i);
		if(f[i].fig == 1)
			printf("Circle: r = %.2f, O(%.2f, %.2f)\n", f[i].coord.c.r,
				   f[i].coord.c.centre.x, f[i].coord.c.centre.y);
		else if(f[i].fig == 2)
			printf("Triangle: A(%.2f, %.2f), B(%.2f, %.2f), C(%.2f, %.2f)\n", f[i].coord.t.a.x, f[i].coord.t.a.y,
				   f[i].coord.t.b.x, f[i].coord.t.b.y, f[i].coord.t.c.x, f[i].coord.t.c.y);
		else if(f[i].fig == 3)
			printf("Rectangle: A(%.2f, %.2f), B(%.2f, %.2f), C(%.2f, %.2f), D(%.2f, %.2f)\n",
				   f[i].coord.r.a.x, f[i].coord.r.a.y, f[i].coord.r.b.x, f[i].coord.r.b.y,
				   f[i].coord.r.c.x, f[i].coord.r.c.y, f[i].coord.r.d.x, f[i].coord.r.d.y);
	}
}

void delete_fig(geomfig_t f[])
{
	char c;
	if(n == 0)
	{
		printf("There are no entries.\n");
		return;
	}
	if(n == 1)
	{
		printf("There is only one entry. Do you want to delete it? (Y/N) ");
		c = getchar();
		if(tolower(c) == 'y') n = 0;
		else if(tolower(c) != 'n')
		{
			printf("Wrong input. Try again.\n");
			delete_fig(f);
		}
		while((c = getchar()) != '\n');
		return;
	}
	int del;
	printf("Which entry do you want to delete? ");
	if(!scanf("%d", &del) || del < 0)
	{
		while((c = getchar()) != '\n');
		printf("Wrong input. Try again.\n");
		delete_fig(f);
	}
	else if(del >= n)
	{
		printf("We don't have that many geometric figures. Try again.\n");
		delete_fig(f);
	}
	else
	{
		for(int i = del; i < n-1; i++)
			f[i] = f[i+1];
		n--;
	}
}
	
int main(void)
{
	geomfig_t f[512];
	int choise, c;
	do
	{  
		printf("\nMenu:\n");
		printf("0. Exit\n");
		printf("1. Introduce the coordinates of one geometric figure\n");
		printf("2. Print the list of all geometric figures\n");
		printf("3. Delete a geometric figure\n");
		printf("What is your choise? ");
		if(!scanf("%d", &choise))
			choise = 4;
		while((c = getchar()) != '\n');
		switch(choise)
		{
			case 0: return 0;
			case 1: read_coord(f); break;
			case 2: print_all(f); break;
			case 3: delete_fig(f); break;
			default: printf("Invalid option. Try again.\n");
		}
		if(n >= 511){ printf("Y u evil?\n"); return 0;}
	}while(choise != 0);
	return 0;
}
