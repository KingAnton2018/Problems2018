#include <stdio.h>
#include <stdlib.h>

void insert_sort(int v[], int n)
{
  int current, j;
  for(int i = 1; i < n; ++i)
    {
      current = v[i];
      for(j = i-1; j >= 0 && v[j] > current; --j)
	v[j+1] = v[j];
      v[j+1] = current;
    }
}

int main(void)
{
  printf("Insert the number of elements \n");
  int N = 0;
  if(!scanf("%d", &N))
    {
      printf("Not a number\n");
      return 1;
    }
  int v[N+1];
  for(int i = 0; i < N; ++i)
    v[i] = rand();
  printf("Before sort:\n");
  for(int i = 0; i < N; ++i)
    printf("%d ", v[i]);
  insert_sort(v, N);
  printf("\nAfter sort:\n");
  for(int i = 0; i < N; ++i)
    printf("%d ", v[i]);
  putchar('\n');
  return 0;
}
