// a SLOW spell checker

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

int main(int argc, char *argv[]) {
  //int input_finish = 0;
  char word[LENGTH + 1];

  // step 1: read in the dictionary
  Trie *t = newTrie();
  while (scanf("%45s",word) && word[0] != '!') {
    addWord(t, word);
  }

  // step 2: read in text
  int counter = 0; // number of unknown words

  /*the part below adds the characters from letter to the array word, 
  and at the end of each word (any special character) it checks if the word is in the dictionary
  if it isn't it will print it, otherwise it contninues
  */
  int letter;
  int i = 0;
  while ((letter = getchar()) && letter != EOF) {
    if (isalpha(letter)){
      word[i] = tolower(letter);
        i++;
    } else {
      if (i > 0 &&!check(t, word, i)) {
        counter++;
        printf("%s\n",word);
      }
      for (int j = 0; j < LENGTH + 1; j++){
        word[j] = 0;
      }
      i = 0;
    }
  }

  // step 3: print number of unknown words
  printf("%d\n", counter);

  freeTrie(t);
  return 0;
}