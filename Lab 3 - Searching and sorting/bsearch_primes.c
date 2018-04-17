#include <stdio.h>

int isprime(unsigned n)
{
	for(int d = 3; d*d <= n; d+=2)
		if(n % d == 0) return 0;
	return 1;
}

void fillvector(unsigned v[], unsigned n)
{
	v[0] = 2;
	if(n < 2) return;
	int p = 3;
	for(int i = 1; i < n; p+=2)
		if(isprime(p))
		{
			v[i] = p;
			++i;
		}
}

int binary_search(unsigned v[], unsigned n, unsigned x, unsigned lo, unsigned hi)
{
	if(lo > hi) return 0;
	unsigned mid = (lo + hi) / 2;
	if(x == v[mid]) return 1;
	if(x < v[mid]) return binary_search(v,n,x,lo,mid-1);
	return binary_search(v,n,x,mid+1,hi);
}

int main(void)
{
	unsigned N;
	printf("How many prime numbers do you want? ");
	if(!scanf("%d", &N))
	{
		printf("Not a number\n");
		return 1;
	}
	unsigned v[N+1];
	fillvector(v, N);
	printf("The vector is: ");
	for(int i = 0; i < N; ++i)
		printf("%d ",v[i]);
	putchar('\n');
	int X;
	printf("What number do you want to search for? ");
	if(!scanf("%d", &X))
	{
		printf("Not a number\n");
		return 1;
	}
	if(X < 2 || !isprime(X) || !binary_search(v,N,X,0,N))
		printf("The number %d is NOT present in the array\n", X);
	else
		printf("The number %d is present in the array\n", X);
	return 0;
}