/*
 * Include the provided hashtable library
 */
#include "hashtable.h"

/*
 * Include the header file
 */
#include "philspel.h"

/*
 * Standard IO and file routines
 */
#include <stdio.h>

/*
 * General utility routines (including malloc())
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines
 */
#include <string.h>

/*
 * this hashtable stores the dictionary
 */
HashTable *dictionary;

/*
 * the MAIN routine.  You can safely print debugging information
 * to standard error (stderr) and it will be ignored in the grading
 * process, in the same way which this does.
 */
int main(int argc, char **argv){
  if(argc != 2){
    fprintf(stderr, "Specify a dictionary\n");
    return 0;
  }
  /*
   * Allocate a hash table to store the dictionary
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(2255, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /* main in C should always return 0 as a way of telling
     whatever program invoked this that everything went OK
     */
  return 0;
}

/*
 * You need to define this function. void *s can be safely casted
 * to a char * (null terminated string) which is done for you here for
 * convenience.
 */
unsigned int stringHash(void *s){
  char *string = (char *) s;
  int r = 0;
  while (*string != '\0'){
    r = (r<<5) - r + *string;
    string++;
  }
  return r;

  fprintf(stderr,"Need to define stringHash\n");
  exit(0);
}

/*
 * You need to define this function.  It should return a nonzero
 * value if the two strings are identical (case sensitive comparison)
 * and 0 otherwise.
 */
int stringEquals(void *s1, void *s2){
  char *string1 = (char *) s1;
  char *string2 = (char *) s2;

  if (strcmp(string1, string2) == 0) {
    return 1;
  } else {
    return 0;
  }
  fprintf(stderr,"Need to define stringEquals\n");
  exit(0);
}

/*
 * this function should read in every word in the dictionary and
 * store it in the dictionary.  You should first open the file specified,
 * then read the words one at a time and insert them into the dictionary.
 * Once the file is read in completely, exit.  You will need to allocate
 * (using malloc()) space for each word.  As described in the specs, you
 * can initially assume that no word is longer than 60 characters.  However,
 * for the final 20% of your grade, you cannot assumed that words have a bounded
 * length You can NOT assume that the specified file exists.  If the file does
 * NOT exist, you should print some message to standard error and call exit(0)
 * to cleanly exit the program. Since the format is one word at a time, with
 * returns in between, you can
 * safely use fscanf() to read in the strings.
 */
void readDictionary(char *filename){
  FILE *file = fopen(filename, "r");
  int counter = 0;
  int malloc_size = 60;
  char* char_of_word = (char*) malloc (60);
  int character;
  if (file == NULL) {
    fprintf(stderr, "This file does not exist!!!!!\n");
    exit(0);
  }
  character = fgetc(file);
  while (character != EOF || counter != 0) {
    if (counter > malloc_size) {
      malloc_size *= 2;
    }
    if (character == '\n' || character == EOF) {
      char_of_word[counter] = '\0';
      insertData(dictionary, char_of_word, char_of_word);
      // free(char_of_word);
      char_of_word = (char*) malloc (60);
      counter = 0;
      character = fgetc(file);
    } else {
      char_of_word[counter] = character;
      character = fgetc(file);
      counter++;
    }
  }
  if (char_of_word != NULL) {
    char_of_word[counter] = '\0';
    insertData(dictionary, char_of_word, char_of_word);
  }
  fclose(file);
  // fclose(second_run);
 // fprintf(stderr,"Need to define readDictionary\n");
}



/*
 * This should process standard input and copy it to standard output
 * as specified in specs.  EG, if a standard dictionary was used
 * and the string "this is a taest of  this-proGram" was given to
 * standard input, the output to standard output (stdout) should be
 * "this is a teast [sic] of  this-proGram".  All words should be checked
 * against the dictionary as they are input, again with all but the first
 * letter converted to lowercase, and finally with all letters converted
 * to lowercase.  Only if all 3 cases are not in the dictionary should it
 * be reported as not being found, by appending " [sic]" after the
 * error.
 *
 * Since we care about preserving whitespace, and pass on all non alphabet
 * characters untouched, and with all non alphabet characters acting as
 * word breaks, scanf() is probably insufficent (since it only considers
 * whitespace as breaking strings), so you will probably have
 * to get characters from standard input one at a time.
 *
 * As stated in the specs, you can initially assume that no word is longer than
 * 60 characters, but you may have strings of non-alphabetic characters (eg,
 * numbers, punctuation) which are longer than 60 characters. For the final 20%
 * of your grade, you can no longer assume words have a bounded length.
 */
void processInput(){
  int c = fgetc(stdin);
  char *copy = NULL;
  char *temp = (char*) malloc(60 * sizeof(char));
  int i = 0;
 // while(c != EOF || temp != NULL){
  while (0) {
    if (temp == NULL) {
      temp = (char*) malloc(60 * sizeof(char));
    }
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
      temp[i] = c;
      i++;
    } else {
      if (findData(dictionary, temp) != NULL) { // if it is a word in dict
        printf("%s ", temp);
        //free(temp);
        i = 0;
      } else { // need to check if it is the same as all lower or with first one upper
        copy = (char*) malloc(60 * sizeof(char));
        strcpy(copy, temp);
        int j;
        char d;
        int lower;
        for (j = 0; j <= i; j++) {
          d = copy[j];
          lower = tolower(d);
          copy[j] = lower;
        }
        if (findData(dictionary, copy) != NULL) {
          printf("%s ", temp);
          free(copy);
          //free(temp);
          i = 0;
        } else { //need to change the first one in copy to upper
          int e = toupper(*copy);
          copy[0] = (char) e;
          if (findData(dictionary, copy) != NULL) {
            printf("%s ", temp);
            free(copy);
            //free(temp);
            i = 0;
          } else {
            printf("%s [sic] ", temp);
            free(copy);
            free(temp);
            i = 0;
          }
        }
      }
    }
    c = fgetc(stdin);
  }
//  exit(0);
}
