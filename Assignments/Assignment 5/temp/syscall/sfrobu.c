#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>





int frobcmp(char const * a, char const * b){

  int i = 0;
   
  while(a[i] != ' ' && b[i] != ' '){
    char a_current = a[i] ^ 42;
    char b_current = b[i] ^ 42;
    if(a_current < b_current)
      return -1;
    else if(b_current < a_current)
      return 1;
    i++;
  }

  // a[i] == ' ' || b[i] == ' '
  if( a[i] == ' ' && b[i] == ' ' )
    return 0;
  else if(a[i] == ' '){
    // a is a prefix of b
    return -1;
  }
  else{
    // b is a prefix of a
    return 1;
  }

}


int frobcmp2(unsigned char const * a, unsigned char const * b){
  int i = 0;
   
  while(a[i] != ' ' && b[i] != ' '){
    unsigned char a_current = a[i] ^ 42;
    unsigned char b_current = b[i] ^ 42;
    a_current = toupper(a_current);
    b_current = toupper(b_current);
    if(a_current < b_current)
      return -1;
    else if(b_current < a_current)
      return 1;
    i++;
  }

  // a[i] == ' ' || b[i] == ' '
  if( a[i] == ' ' && b[i] == ' ' )
    return 0;
  else if(a[i] == ' '){
    // a is a prefix of b
    return -1;
  }
  else{
    // b is a prefix of a
    return 1;
  }

}


int wrap_frobcmp(const void * a, const void * b){
  return frobcmp(*(char const **)a, *(char const **)b);
}

int wrap_frobcmp_nocase(const void * a, const void * b){
  return frobcmp2(*(unsigned char const **)a, *(unsigned char const **)b);
}

int main(int argc, char** argv){

  int use_toupper = 0;
  if(argc > 2){
    fprintf(stderr, "Improper number of arguments.");
    exit(1);
  }
  if(argc == 2){
    if(strlen(argv[1]) != 2){
      fprintf(stderr, "Invalid argument.");
      exit(1);
    }
    if(argv[1][0] != '-' || argv[1][1] != 'f'){
      fprintf(stderr, "Invalid argument.");
      exit(1);
    }
    use_toupper = 1;
  }
    
  
      


  
  char** words;
  long capacity = 1;
  long numWords = 0;
  struct stat file;

  fstat(0, &file);
  char* buffer;

  long buf_cap = 0, buf_size = 0;
  if(S_ISREG(file.st_mode)){
    // Dealing with a Regular File, so we should set up capacity
    buf_cap = file.st_size;
    if(buf_cap == 0)
      buf_cap = 1;
    buffer = (char *) malloc(buf_cap);
    if(buffer == NULL){
      fprintf(stderr, "Error: Malloc Failure");
      exit(1);
    }
    
  }else{
 
    buf_cap = 1;
    buffer = (char *) malloc(buf_cap);
    if(buffer == NULL){
      fprintf(stderr, "Error: Malloc Failure");
      exit(1);
    }
  }


  // We have a starting buffer of some size. If regular file, it is the size
  // of the file. If not, it is of size 1.

  int next_char;
  int final = 0;
  while(1){
    
    if(read(0, &next_char, 1) <= 0){
      final = 1;
      next_char = EOF;
    }
    if(buf_size >= buf_cap){
      buffer = (char *) realloc(buffer, buf_size * 2);
      buf_cap = buf_size * 2;
      if(buffer == NULL){
	fprintf(stderr, "Error: Realloc Failure");
	exit(1);
      }
    }
    // buffer can fit next character
    buffer[buf_size++] = next_char;
    
    if(final)
      break;
  }
  

  // buffer is now full of contents of file
  //  printf("ALLOCATED: %d\n", buf_cap);
  //  printf("USING:     %d\n", buf_size);

  int index_of_char = 0;
  
  words = (char **)malloc(sizeof(char*));
  if(words == NULL){
    fprintf(stderr, "Error: Malloc Failure");
    exit(1);
  }
  words[0] = (char *)malloc(sizeof(char));
  if(words[0] == NULL){
    fprintf(stderr, "Error: Malloc Failure");
    exit(1);
  }
  int nextChar;

  while(index_of_char < buf_size){
    nextChar = buffer[index_of_char];
    //printf("Accessed %d in Buffer size %d, with Capacity %d\nAnd nextchar %c\n", index_of_char, buf_size, buf_cap, nextChar);
    index_of_char++;
    //printf("No Seg Fault\n");
    if(index_of_char >= buf_size)
      break;
    // nextChar has character for next word
    numWords++;
    if(capacity <= numWords){
      // We need more bytes for array of words
      capacity = numWords * 2;
      //printf("About to realloc\n");
      words = (char **)realloc(words, capacity*sizeof(char*));
      //printf("Realloced\n");
      if(words == NULL){
	fprintf(stderr, "Error: Realloc Failure");
	exit(1);
      }
    }

    int lastChar = 0;
    // There is space to insert new word.
    //printf("Declarng word_cap\n");
    long word_cap = 0;
    //printf("Declaring numChar\n");
    long numChar = 0;
    
    //printf("Declaring lastChar\n");
    
    
    //printf("%d word with Word Capacity:\t%d", numWords, capacity);
    do{
      // Next character to insert in nextChar;
      numChar++;
      
      if(nextChar == ' ')
	lastChar = 1;
      
      
      if( word_cap <= numChar ){
	// Need more space in current word
	word_cap = numChar * 2;
	words[numWords - 1] = (char *)realloc(words[numWords - 1], word_cap*sizeof(char));
	
	if(words[numWords - 1] == NULL){
	  fprintf(stderr, "Error: Realloc Failure");
	  exit(1);
	}
      }

      // There is space to insert new character.

      words[numWords - 1][numChar - 1] = nextChar;

      if(index_of_char == buf_size)
	break;
      
      if(nextChar != ' ')
	nextChar = buffer[index_of_char++];

      if(index_of_char == buf_size)
	nextChar = ' ';

      

    
    }while(!lastChar);


    //printf("\t%d characters with Character capacity:\t%d\n", numChar, word_cap);


    }
 
  //int i, j;
    /* for(i = 0; i < numWords; i++){
    for(j = 0; words[i][j] != ' '; j++){
      printf("%c", words[i][j]);
    }
    printf("\n");
  }
  */
  /*int i;
  for(i = 0; i < numChar; i++){
    printf("%c", words[numWords - 1][i]);
    }*/

  // Now we have an array of words, so we need to sort them.

  if(!use_toupper)
    qsort(words, numWords, sizeof(char*), wrap_frobcmp);
  else
    qsort(words, numWords, sizeof(char*), wrap_frobcmp_nocase);
  const char space = ' ';
  int i, j;
  for(i = 0; i < numWords; i++){
    j = 0;
    char next;
    for(j = 0; words[i][j] != ' '; j++);
    write(1, words[i], j);
    write(1, &space, 1);
      
  }

  for(i = 0; i < numWords; i++){
    free(words[i]);
  }
  free(words);

  free(buffer);

  return 0;
}

