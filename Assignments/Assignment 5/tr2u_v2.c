#include <stdio.h>
#include <stdlib.h>

void tr2u(const char* from, const char* to)
{
  if (strlen(from) != strlen(to))
    {
      fprintf(stderr, "Error: from and to are different sizes");
      exit(1);
    }
  
  int* check = (int*) malloc(255*sizeof(int));
  int count = 0;
  for (count = 0; count < strlen(from); count++)
    {
      check[from[count]]++;
      if (check[from[count]] > 1)
	{
	  fprintf(stderr, "Error: from has multiple characters");
	  exit(1);
	}
    }
  free(check);
  
  char* charArray = (char*) malloc(0);
  char* find = (char*)malloc(sizeof(char));
  if (charArray==NULL)
    exit(1);
  int numChar = 0;
  int ch;
  while (read(0,&ch,1))
    {
      if (ch == EOF)
	break;
      if (ch == '\0')
	break;
      numChar++;
      charArray = realloc(charArray, sizeof(char)*numChar);
      if (charArray == NULL)
	exit(1);
      find = strchr(from,ch);
      if (find == NULL)
	write(1,&ch,1);
      else
	write(1,&to[find-from],1);
    }
  free(charArray);
}

int main( int argc, char *argv[] )
{
  if (argc != 3)
    {
      fprintf(stderr, "Wrong number of arguments");
      exit(1);
    }
  tr2u(argv[1],argv[2]);
  return 0;
}
