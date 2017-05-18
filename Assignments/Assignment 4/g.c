#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const* a, char const* b)
{
  while (*a != ' ' && *b != ' ')
    {
      if ((*a^42) > (*b^42))
	return 1;
      else if ((*a^42) < (*b^42))
	return -1;
      a = a+1;
      b = b+1;
    }

  if (*a == ' ' && *b == ' ')
    return 0;
  else if (*a == ' ')
    return -1;
  return 1;  
}

int voidcmp(const void* a, const void* b)
{
  char const* aTemp = *(char const**)a;
  char const* bTemp = *(char const**)b;
  return frobcmp(aTemp, bTemp);
}

void sfrob()
{
  char* charArray = (char*) malloc(0);
  if (charArray == NULL)
    {
      fprintf(stderr, "Error: Failed to allocate memory!");
      exit(1);
    }
  int numWords = 0;
  int numChars = 0;
  int ch;

  while (1)
    {
      if (ch == EOF)
	{
	  numChars--;
	  break;
	}
      ch = getchar();
      numChars++;
      charArray = (char*) realloc(charArray, sizeof(char) * numChars);
      if (charArray == NULL)
	{
	  fprintf(stderr, "Error: Failed to reallocate memory!");
	  exit(1);
	}
      charArray[numChars-1] = ch;
      if (ch == ' ')
	numWords++;
    }
  
  if (numChars == 0)
    {
      charArray = (char*) realloc(charArray, sizeof(char));
      charArray[numChars] = ' ';
      numChars++;
      numWords++;
    }
  else if (charArray[numChars - 1] != ' ')
    {
      charArray[numChars] = ' ';
      numChars++;
      numWords++;
    }
  int i = 0;
  int j = 0;
  //for(i = 0; i < numChars ; i++)
  //  {
  //    putchar(charArray[i]);
  //  }
  
  
  char** wordArray = (char**) malloc(sizeof(char*) * numWords);
  
  if (wordArray == NULL)
    {
      fprintf(stderr, "Error: Failed to allocate memory!");
      exit(1);
    }
  
  int tempWords = 0;
  wordArray[tempWords] = charArray;
  for (i = 0; i < numChars - 1; i++)
    {
      if (charArray[i] == ' ')
	{
	  tempWords++;
  	  wordArray[tempWords] = &charArray[i+1];
  	}
    }
  
  //for(i = 0; i < numWords ; i++)
  // {
  //  for(j = 0; wordArray[i][j] != ' '; j++)
  //	{
  //	  putchar(wordArray[i][j]);
  //	}
  //  putchar(' ');
  //}
  
  qsort(wordArray, numWords, sizeof(char*), voidcmp);
  
  for(i = 0; i < numWords ; i++)
    {
      for(j = 0; wordArray[i][j] != ' '; j++)
	{
	  putchar(wordArray[i][j]);
	}
      putchar(' ');
    }
  
  free(charArray);
  free(wordArray); 
}

int main()
{
  sfrob();
}
