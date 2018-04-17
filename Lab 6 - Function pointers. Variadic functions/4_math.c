#include <stdio.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
	char *func_name[8] = {"sin","cos","ceil","floor","fabs","log","sqrt"};
	double(*fp[7])(double x);
	fp[0] = sin;
	fp[1] = cos;
	fp[2] = ceil;
	fp[3] = floor;
	fp[4] = fabs;
	fp[5] = log;
	fp[6] = sqrt;
	
	int choise = -1, ok;
	double x;
	do{
		ok = 1;
		printf("\nInsert a real number: ");
		if(!scanf("%lf", &x)) { ok = 0; goto check;}
		printf("Menu:\n");
		for(int i = 0; i < 7; i++)
			printf("%d. %s\n", i, func_name[i]);
		printf("7. Exit\n");
		printf("Insert an option: ");
		if(!scanf("%d", &choise)){ ok = 0; goto check;}
		if(choise == 7) return 0;
		if(choise >= 0 && choise < 7)
			printf("%s(%lf) = %lf\n", func_name[choise], x, fp[choise](x));
	check:
		if(ok == 0)
			printf("Wrong input. Try again\n");
		while(!isspace(getchar()));
	}while(choise != 7);
	
	return 0;
}