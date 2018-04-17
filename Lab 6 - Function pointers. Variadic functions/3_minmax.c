//3. Write a program which takes an arbitrary number of arguments
//and determines the minimum and the maximum value from the list

#include <stdio.h>
#include <stdarg.h>

void min_max(unsigned nr_arg, ...)
{
	va_list list;
	double min, max, current;
	va_start(list, nr_arg);
	min = max = va_arg(list, double);
	printf("The list is: %f ", min);
	for(int i = 1; i < nr_arg; i++)
	{
		current = va_arg(list, double);
		printf("%f ", current);
		if(current > max) max = current;
		if(current < min) min = current;
	}
	va_end(list);
	printf("\nThe minimum value is %f\nThe maximum value is %f\n",min,max);
}

int main(void)
{
	min_max(5, 2.3, 15.3, 4.0, -3.0, 9.0);
	//daca nu pui . nu merge (gen in loc de 4 tre sa pui 4.0)
	return 0;
}