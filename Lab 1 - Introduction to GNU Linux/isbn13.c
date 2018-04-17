#include <stdio.h>

int valid13(char s[13])
{
  unsigned sum = 0;
  for(int i = 0; i <= 10; i+=2)
    sum += s[i] - '0' + (s[i+1] - '0') * 3;
  if((10 - sum % 10) == s[12] - '0') return 1;
  return 0;
}

int main(void)
{
  char isbn13[] = "9781435704572";
  printf("isbn13 = %s\n", isbn13);
  if(valid13(isbn13)) printf("Valid\n");
  else printf("Invalid\n");
  return 0;
}
