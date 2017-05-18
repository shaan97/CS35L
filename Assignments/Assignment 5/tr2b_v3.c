#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
  if (argc > 3){
    fprintf(stderr, "Error: more than 2 arguments");
    exit(1);
  }
  if (argc == 1){
    fprintf(stderr, "Error: no argument");
    exit(1);
  }
  if (argc == 2){
    fprintf(stderr, "Error: need one more argument");
    exit(1);
  }

  char * tr1 = argv[1];
  char * tr2 = argv[2];

  /*
  char temp1 = tr1[0];
  printf ("%c\n", temp1);
  char temp2 = tr2[0];
  printf ("%c\n" ,temp2);
  */

  //find out how to represent the null terminator
  /*
  if (tr1[2] == 0){
    printf("Test\n");
  }
  */

  // check whether two arguments have the same length
  int i = 0;
  while(tr1[i] != '\0' && tr2[i] != '\0'){
    i++;
  }

  if((tr1[i] != '\0' && tr2[i] == '\0') || (tr1[i] == '\0' && tr2[i] != '\0')){
    fprintf(stderr, "Error: arguments have different lengths");
    exit(1);
  }

  char buffer;
  while((buffer = getchar()) != EOF){
    int k = 0;
    while(tr1[k] != '\0'){
      if(buffer == tr1[k]){
	break;
      }
      k++;
    }
    buffer = tr2[k];
    putchar(buffer);
  }
  
  return 0;
}
