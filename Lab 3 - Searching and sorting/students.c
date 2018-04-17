#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct{
	char name[35];
	unsigned grade;
}student_t;

void readstud(student_t *s, int N)
{
	for(int i = 0; i < N; ++i)
	{
		scanf("%s", s[i].name);
		scanf("%d", &s[i].grade);
	}
}

void display_alpha(student_t *s, int N)
{
	int j;
	student_t current;
	for(int i = 1; i < N; ++i)
	{
		current = s[i];
		for(j = i-1; j >= 0 && strcmp(s[j].name, current.name)>0; --j)
			s[j+1] = s[j];
		s[j+1] = current;
	}
	for(int i = 0; i < N; ++i)
		printf("%s %d\n", s[i].name, s[i].grade);
}

void display_grades(student_t *s, int N)
{
	int j;
	student_t current;
	for(int i = 1; i < N; ++i)
	{
		current = s[i];
		for(j = i-1; j >= 0 && s[j].grade < current.grade; --j)
			s[j+1] = s[j];
		s[j+1] = current;
	}
	for(int i = 0; i < N; ++i)
		printf("%s %d\n", s[i].name, s[i].grade);
}

void display_first3(student_t *s, int N)
{
	int j;
	student_t current;
	for(int i = 1; i < N; ++i)
	{
		current = s[i];
		for(j = i-1; j >= 0 && s[j].grade < current.grade; --j)
			s[j+1] = s[j];
		s[j+1] = current;
	}
	for(int i = 0; i < 3; ++i)
		printf("%s %d\n", s[i].name, s[i].grade);
}

int main(void)
{
	int choise;
	int N = 0;
	student_t *s = malloc(sizeof(student_t));
	do
	{
		do
		{
			printf("\nMenu:\n");
			printf("0. Exit program\n");
			printf("1. Give N, number of students\n");
			printf("2. Enter the students\n");
			printf("3. Display class in alphabetic order\n");
			printf("4. Display class creating a top based on grades\n");
			printf("5. Display the first 3 students according to their grades\n");
			printf("Choose an option: ");
			scanf("%d", &choise);
		}while(choise < 0 || choise > 5);
		switch(choise)
		{
			case 0 : break;
			case 1 :
				if(scanf("%d", &N))
					s = realloc(s, sizeof(student_t) * N);
				else printf("Not a number\n");
				break;
			case 2 :
				if(N == 0) printf("You have to give the number of students first\n");
				else readstud(s, N);
				break;
			case 3 : 
				if(N == 0) printf("You have to give the number of students first\n");
				else display_alpha(s, N);
				break;
			case 4 :
				if(N == 0) printf("You have to give the number of students first\n");
				else display_grades(s, N);
				break;
			case 5 :
				if(N == 0) printf("You have to give the number of students first\n");
				else display_first3(s, N);
				break;
			default : printf("Invalid option. Try again\n");
		}
	}while(choise != 0);
	return 0;
}
