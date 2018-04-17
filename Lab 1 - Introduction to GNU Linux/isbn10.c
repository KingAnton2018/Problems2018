#include <stdio.h>

int valid10(char s[10])
{
  unsigned sum = 0;
  for(int i = 0; i <= 8; ++i)
    sum += (i+1) * (s[i] - '0');
  if(sum % 11 == s[9] - '0') return 1;
  if(sum % 11 == 10 && s[9] == 'X') return 1;
  return 0;
}

int main(void)
{
  char isbn10[] = "0521396549";
  printf("isbn10 = %s\n", isbn10);
  if(valid10(isbn10)) printf("Valid\n");
  else printf("Invalid\n");
  return 0;
}
