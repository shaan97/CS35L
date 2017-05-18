#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
  if(argc > 3){
    fprintf(stderr, "Too many arguments.\n");
    exit(1);
  }
  if(argc == 2){
    fprintf(stderr, "Too few arguments.\n");
    exit(1);
  }
  if(argc == 1){
    fprintf(stderr, "Need arguments\n");
    exit(1);
  }
  // argc == 3

  int arg_table[255];
  int i = 0;
  for(i = 0; i < 255; i++)
    arg_table[i] = 0;
  i = 0;
  long tr1_size = 0;
  while(argv[1][i] != '\0'){
    arg_table[argv[1][i]]++;
    if(arg_table[argv[1][i++]] > 1){
      fprintf(stderr, "No Duplicates Allowed in Argument 1.\n");
      exit(1);
    }
    tr1_size++;
  }
    
  i = 0;
  long tr2_size = 0;
  while(argv[2][i++] != '\0'){
    tr2_size++;
  }

  if(tr1_size != tr2_size){
    fprintf(stderr, "Both alphabets must be of same length.\n");
    exit(1);
  }

  unsigned char current;
  int j = 0;

  int debug_oc = 0;
  while(read(0,&current, 1) > 0){
    if(arg_table[current] == 0){
      write(1, &current, 1);
      continue;
    }
    for(j = 0; j < tr1_size; j++)
      if(argv[1][j] == current)
	break;

    // argv[1][j] == current || j >= tr1_size
    write(1, &(argv[2][j]), 1);
  }
  
  return 0;
}
