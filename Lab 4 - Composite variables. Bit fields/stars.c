#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
	MainSequence = 1,
	Binary = 2,
	VariableLight = 3
}class_t;

typedef struct{
	unsigned age;
	char color[13];
}mainSeq_t;

typedef struct{
	float rad1, rad2;
}binary_t;

typedef struct{
	float lo_lum, hi_lum, period;
}varLight_t;

typedef union{
	mainSeq_t s;
	binary_t b;
	varLight_t l;
}properties_t;

typedef struct{
	char *name;
	class_t class;
	properties_t prop;
}star_t;

void read_name(char *s)
{
	int len = 0, cnt = 1;
	printf("What is the name of your star?\n");
	char c = getchar();
	while(c != '\n')
	{
		if(len == (512*cnt - 1))
			s = realloc(s, 512 * (++cnt));
		s[len++] = c;
		c = getchar();
	}
}

void print_data(star_t star)
{
	putchar('\n');
	switch(star.class)
	{
		case 1:
			printf("Your star is named %s.\n", star.name);
			printf("It is a Main Sequence Star of age category %d ", star.prop.s.age);
			printf("and color %s.\n", star.prop.s.color);
			break;
		case 2:
			printf("Your stars are named %s.\n", star.name);
			printf("They are Binary Stars with the rotation radius of %f and %f.\n",
				   star.prop.b.rad1, star.prop.b.rad2);
			break;
		case 3:
			printf("Your star is named %s.\n", star.name);
			printf("It is a Variable Light Star with the following characteristics:\n");
			printf("Lowest luminosity: %f L;\n", star.prop.l.lo_lum);
			printf("Highest luminosity: %f L;\n", star.prop.l.hi_lum);
			printf("Light periodicity (in Earth days): %f.\n", star.prop.l.period);
			break;
		default : printf("Wrong input\n");
	}
}

int main(void)
{
	star_t star;
	star.name = malloc(512);
	read_name(star.name);
	int ok, c, ans;
	do
	{
		ok = 1;
		printf("What kind of star is it? Press s for Main Sequence Star, b for Binary Stars ");
		printf("or l for Variable Light Star\n");
		ans = getchar();
		getchar();
		if(ans == 's')
		{
			star.class = 1;
			printf("What age category does your star belong to (1-4)? ");
			if(!scanf("%u", &star.prop.s.age) || star.prop.s.age < 1 || star.prop.s.age > 4)
			{
				while((c = getchar())!='\n');
				ok = 0;
				goto end;
			}
			printf("What color is your star? ");
			if(!scanf("%12s", star.prop.s.color) || (c = getchar() != '\n'))
			{
				while((c = getchar() != '\n'));
				ok = 0;
				goto end;
			}
		}
		else if(ans == 'b')
		{
			star.class = 2;
			printf("What is the rotation radius of the first star? ");
			if(!scanf("%f", &star.prop.b.rad1) || star.prop.b.rad1 <= 0)
			{
				while((c = getchar() != '\n'));
				ok = 0;
				goto end;
			}
			printf("What is the rotation radius of the second star? ");
			if(!scanf("%f", &star.prop.b.rad2) || star.prop.b.rad2 <= 0)
			{
				while((c = getchar() != '\n'));
				ok = 0;
				goto end;
			}
		}
		else if(ans == 'l')
		{
			star.class = 3;
			printf("What is the lowest luminosity of your star (in solar luminosity units)? ");
			if(!scanf("%f", &star.prop.l.lo_lum))
			{
				while((c = getchar() != '\n'));
				ok = 0;
				goto end;
			}
			printf("What is the highest luminosity of your star (in solar luminosity units)? ");
			if(!scanf("%f", &star.prop.l.hi_lum))
			{
				while((c = getchar() != '\n'));
				ok = 0;
				goto end;
			}
			printf("What is the light periodicity of your star (in Earth days)? ");
			if(!scanf("%f", &star.prop.l.period) || star.prop.l.period < 0)
			{
				while((c = getchar() != '\n'));
				ok = 0;
				goto end;
			}
		}
		else 
			ok = 0;
end:
		if(!ok)
			printf("Wrong input. Please try again\n\n");
	}while(!ok);
	print_data(star);
	return 0;
}