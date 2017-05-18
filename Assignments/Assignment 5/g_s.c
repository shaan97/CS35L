#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int comparisons = 0;
int frobcmp(char const* a, char const* b)
{
  comparisons++;
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

int main()
{  
  int numWords = 0;
  int numChars = 0;
  int ch;  
  int n;
  char* charArray;
  struct stat fs;
  fstat(STDIN_FILENO,&fs);

  if (S_ISREG(fs.st_mode))
    {
      if (fs.st_size == 0)
	{
	  charArray = (char*) malloc(sizeof(char));
	  if (charArray == NULL)
	    {
	      fprintf(stderr, "Error: Failed to allocate memory");
	      exit(1);
	    }
	  numChars++;
	  charArray[0] = ' ';
	}
      else
	{
	  charArray = (char*) malloc(sizeof(char)*fs.st_size);
	  if (charArray == NULL)
	    {
	      fprintf(stderr, "Error: Failed to allocate memory");
	      exit(1);
	    }
	  while (read(0,&ch,1)>0 && numChars < fs.st_size)
	    {
	      if (ch == EOF)
		break;
	      numChars++;
	      charArray = (char*) realloc(charArray, sizeof(char) * numChars);
	      if (charArray == NULL)
		{
		  fprintf(stderr, "Error: Failed to reallocate memory!");
		  exit(1);
		}
	      charArray[numChars-1] = ch;
	    }
	}
    }
  else
    {
      charArray = (char*) malloc(0);
      if (charArray == NULL)
	{
	  fprintf(stderr, "Error: Failed to allocate memory!");
	  exit(1);
	}
    }
  
  while (read(0,&ch,1)>0)
    { 
      if (ch == EOF)
	break;
      numChars++;
      charArray = (char*) realloc(charArray, sizeof(char) * numChars);
      if (charArray == NULL)
	{
	  fprintf(stderr, "Error: Failed to reallocate memory!");
	  exit(1);
	}
      charArray[numChars-1] = ch;
    }
  
  if (numChars == 0)
    {
      charArray = (char*) realloc(charArray, sizeof(char));
      charArray[numChars] = ' ';
      numChars++;
    }
  else if (charArray[numChars-1] != ' ')
    {
      charArray = (char*) realloc(charArray, sizeof(char)*(numChars+1));
      charArray[numChars] = ' ';
      numChars++;
    }
  
  int i = 0;
  int abc=0;
  int j = 0;
  
  char** wordArray = malloc(sizeof(char*));
  
  if (wordArray == NULL)
    {
      fprintf(stderr, "Error: Failed to allocate memory!");
      exit(1);
    }  
  
  int tempWords = 0;
  wordArray[tempWords] = charArray;
  tempWords++;
  
  const char space = ' ';
  
  for (i = 0; i < numChars-1; i++)
    {
      if (charArray[i] == ' ')
	{
	  tempWords++;
	  wordArray = realloc(wordArray,sizeof(char*)*(tempWords));
  	  wordArray[tempWords-1] = &charArray[i+1];
	}
    }
  
  qsort(wordArray, tempWords, sizeof(char*), voidcmp);


  for(i = 0; i < tempWords ; i++)
    {
      for(j = 0; wordArray[i][j]!=' '; j++);
      write(1,wordArray[i],j);
      write(1,&space,1);
    }
  
  free(charArray);
  free(wordArray); 
  exit(0);
}
