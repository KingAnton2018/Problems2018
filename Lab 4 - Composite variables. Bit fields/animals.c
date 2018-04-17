#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum{
	INSECT = 0,
	BIRD = 1,
	MAMMAL = 2,
	FISH = 3
}class_t;

typedef struct{
	unsigned legs;
	float lifeSpan;
}insect_t;

typedef struct{
	float flightSpeed, wingLength;
	char *migrHab;
}bird_t;

typedef struct{
	float weight, height;
	char *foodType;
}mammal_t;

typedef struct{
	float weight, swimDepth, salt;
}fish_t;

typedef union{
	insect_t i;
	bird_t b;
	mammal_t m;
	fish_t f;
}traits_t;

typedef struct{
	char *name;
	class_t class;
	traits_t traits; 
}animal_t;

void read_string(char *s)
{
	int len = 0, cnt = 1;
	char c = getchar();
	while(c != '\n')
	{
		if(len == (512*cnt - 1))
			s = realloc(s, 512 * (++cnt));
		s[len++] = c;
		c = getchar();
	}
}

animal_t read_entry(void)
{
	animal_t e;
	printf("Insert the name of the animal: ");
	e.name = malloc(512);
	read_string(e.name);
	printf("Insert the class of the animal (i for insect, b for bird, ");
	printf("m for mammal, f for fish): ");
	int c = getchar();
	int ok = 1;
	switch(c)
	{
		case 'i':
			e.class = 0;
			printf("Insert the number of legs: ");
			int aux;
			if(!scanf("%d", &aux) || aux < 0) { ok = 0; goto check; }
			else e.traits.i.legs = aux;
			printf("Insert the life span (years): ");
			if(!scanf("%f", &e.traits.i.lifeSpan)) { ok = 0; goto check; }
			break;
		case 'b':
			e.class = 1;
			printf("Insert the flight speed (m/s): ");
			if(!scanf("%f", &e.traits.b.flightSpeed)) { ok = 0; goto check; }
			printf("Insert the wing length (cm): ");
			if(!scanf("%f", &e.traits.b.wingLength)) { ok = 0; goto check; }
			getchar();
			printf("Insert the migration habbits: ");
			e.traits.b.migrHab = malloc(512);
			read_string(e.traits.b.migrHab);
			break;
		case 'm':
			e.class = 2;
			printf("Insert the weight (kg): ");
			if(!scanf("%f", &e.traits.m.weight) || e.traits.m.weight <= 0)
				{ ok = 0; goto check; }
			printf("Insert the height (m): ");
			if(!scanf("%f", &e.traits.m.height) || e.traits.m.height <= 0)
				{ ok = 0; goto check; }
			getchar();
			printf("Insert the food type: ");
			e.traits.m.foodType = malloc(512);
			read_string(e.traits.m.foodType);
			break;
		case 'f':
			e.class = 3;
			printf("Insert weight (kg): ");
			if(!scanf("%f", &e.traits.f.weight) || e.traits.f.weight <= 0)
				{ ok = 0; goto check; }
			printf("Insert swimming depth (m): ");
			if(!scanf("%f", &e.traits.f.swimDepth) || e.traits.f.swimDepth <= 0)
				{ ok = 0; goto check; }
			printf("Insert water salt percentage: ");
			if(!scanf("%f", &e.traits.f.salt) || e.traits.f.salt < 0 ||
			  e.traits.f.salt > 100)
				{ ok = 0; goto check; }
			break;
		default: ok = 0;
	}
check:
	if(ok) return e;
	else
	{
		while((c = getchar()) != '\n');
		printf("\nWrong input. Please try again\n");
		return read_entry();
	}
}

void delete(animal_t a[], unsigned *n)
{
	char c;
	if((*n) == 0) {printf("There are no entries\n"); return;}
	if((*n) == 1)
	{
		printf("There is only one entry. Do you want to delete it? (Y/N) ");
		c = getchar();
		if(tolower(c) == 'y') *n = 0;
		else if(tolower(c) != 'n')
		{
			printf("Wrong input. Try again.\n");
			delete(a,n);
		}
		while((c = getchar()) != '\n');
		return;
	}
	int del;
	printf("Which entry do you want to delete? ");
	if(!scanf("%d", &del))
	{
		while((c = getchar()) != '\n');
		printf("Wrong input. Try again.\n");
		delete(a,n);
	}
	else if(del >= *n || del < 0)
	{
		printf("There is no such entry. Try again.\n");
		delete(a,n);
	}
	else
	{
		for(; del < (*n)-1; del++)
			a[del] = a[del+1];
		(*n)--;
	}
}

void print_entry(animal_t e)
{
	switch(e.class)
	{
		case 0:
			printf("%s\n\tClass: insects\n", e.name);
			printf("\tNumber of legs: %u\n", e.traits.i.legs);
			printf("\tLife span: %.2f years\n", e.traits.i.lifeSpan);
			break;
		case 1:
			printf("%s\n\tClass: birds\n", e.name);
			printf("\tFlight speed: %.2f m/s\n", e.traits.b.flightSpeed);
			printf("\tWing length: %.2f cm\n", e.traits.b.wingLength);
			printf("\tMigration habbits: %s\n", e.traits.b.migrHab);
			break;
		case 2:
			printf("%s\n\tClass: mammals\n", e.name);
			printf("\tWeight: %.2f kg\n", e.traits.m.weight);
			printf("\tHeight: %.2f m\n", e.traits.m.height);
			printf("\tFood type: %s\n", e.traits.m.foodType);
			break;
		case 3:
			printf("%s\n\tClass: fishes\n", e.name);
			printf("\tWeight: %.2f kg\n", e.traits.f.weight);
			printf("\tSwimming Depth: %.2f m\n", e.traits.f.swimDepth);
			printf("\tWater salt percentage: %.2f\n", e.traits.f.salt);
	}
}

void print_all(animal_t a[], unsigned n)
{
	if(n == 0)
	{
		printf("There are no entries\n");
		return;
	}
	for(int i = 0; i < n; ++i)
	{
		printf("%d. ", i);
		print_entry(a[i]);
	}
}

void lookup(animal_t a[], unsigned n)
{
	int c, i;
	printf("Which entry do you want to lookup? ");
	if(!scanf("%d", &i))
	{
		while((c = getchar()) != '\n');
		printf("Wrong input. Try again.\n");
		lookup(a,n);
	}
	else if(i < 0 || i >= n)
	{
		printf("There is no such entry. Try again.\n");
		lookup(a,n);
	}
	else
		print_entry(a[i]);
}

void replace(animal_t a[], unsigned n)
{
	int c, i;
	printf("Which entry do you want to replace? ");
	if(!scanf("%d", &i))
	{
		while((c = getchar()) != '\n');
		printf("Wrong input. Try again.\n");
		replace(a,n);
	}
	else if(i < 0 || i >= n)
	{
		while((c = getchar()) != '\n');
		printf("There is no such entry. Try again.\n");
		replace(a,n);
	}
	else
	{
		while((c = getchar()) != '\n');
		printf("Please introduce the data of the new animal.\n");
		animal_t e = read_entry();
		a[i] = e;
	}
}

int main(void)
{
	animal_t a[512];
	int choise;
	unsigned n = 0;
	char c;
	do
	{
		printf("\nMenu:\n");
		printf("0. Exit\n");
		printf("1. Add entry\n");
		printf("2. Delete entry\n");
		printf("3. Replace entry\n");
		printf("4. Lookup entry\n");
		printf("5. Print all entries\n");
		printf("What is your choise? ");
		if(!scanf("%d", &choise))
		{
			while((c = getchar())!='\n');
			choise = 6;
		}
		while((c = getchar()) != '\n');
		switch(choise)
		{
			case 0: return 0;
			case 1: a[n++] = read_entry(); break;
			case 2: delete(a,&n); break;
			case 3: replace(a,n); break;
			case 4: lookup(a,n); break;
			case 5: print_all(a,n); break;
			default: printf("Invalid option. Try again.\n");
		}
		if(n >= 511){ printf("Y u evil?\n"); return 0;}
	}while(choise != 0);
	return 0;
}