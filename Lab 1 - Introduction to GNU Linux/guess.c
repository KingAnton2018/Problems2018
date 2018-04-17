/*
Write a C program that tells the user to think
about a number between 1 and 100 and then tries
to guess the number by asking questions of the
form "Is your number greater than ...?" and "Is
your number smaller than ...?". Save the program
in a file called "guess.c". Compile and link the file
with GCC(1). Run the program.
 */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

int guess (int l,int r) // function that devides: takes l_bound and r_bound
{
  int m = (l+r)/2; // arithmetic mean 
  char *s;
  s = malloc(4*sizeof(char)); // memery allocation
  printf("is your number greater than %d ? (yes/no) \n", m);
  scanf("%s",s);
    if(!strcmp(s,"yes"))
    {
      l=m;
      return guess (l,r); // recursive call
    }
  printf("is your number smaller than %d ? (yes/no) \n", m);
  scanf("%s",s);
  if(!strcmp(s,"yes"))
    {
      r=m;
      return guess (l,r); // recursive call
    }
  return m; //base case
}

int main(void)
{
  printf("think about a number between 0 and 100 \n");
  printf("your number is %d",guess(0,100));
}
