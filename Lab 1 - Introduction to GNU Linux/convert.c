#include <stdio.h>

void isbn13to10(char isbn13[13])
{
  char isbn10[10];
  unsigned sum = 0;
  for(int i = 3, j = 0; i <= 12; ++i, ++j)
    {
      isbn10[j] = isbn13[i];
      sum += (j+1) * (isbn10[j] - '0');
    }
  sum = sum % 11;
  if(sum == 10) isbn10[9] = 'X';
  else isbn10[9] = sum + '0';
  printf("isbn10 = %s\n", isbn10);
}

void isbn10to13(char isbn10[10])
{
  char isbn13[13] = "978";
  unsigned sum = 0;
  for(int i = 0, j = 3; i <= 8; ++i, ++j)
      isbn13[j] = isbn10[i];
  for(int i = 0; i <= 10; i+=2)
    sum += isbn13[i] - '0' + (isbn13[i+1] - '0') * 3;
  isbn13[12] = 10 - sum % 10;
  printf("isbn13 = %s\n", isbn13);
}

int main(void)
{
  char isbn13[] = "9781435704572";
  isbn13to10(isbn13);
  char isbn10[] = "0521396549";
  isbn10to13(isbn10);
  return 0;
}
