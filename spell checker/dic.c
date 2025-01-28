// implements a dictionary

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

/*the function below creates a new empty trie in memory*/
Trie *newTrie() {
  Trie *root = malloc(sizeof(Trie));
  root->endNode = 0;
  for (int i = 0; i < 26; i++){
    root->child[i] = NULL;
  }
  return root;
}

/*the function below adds a new word to the trie*/
void addWord(Trie *t, char *word) {
  Trie *temp = t;
  for (int i = 0; word[i] != '\0'; i++) {
    int index = word[i] - 'a';
    if (temp->child[index] == NULL) {
        temp->child[index] = malloc(sizeof(Trie));
      for (int j = 0; j < 26; j++) {
        temp->child[index]->child[j] = NULL;
      }
      temp->child[index]->endNode = false;
    }
    temp = temp->child[index];
  }
  temp->endNode = true;
}

/*the function below checks if a word exsists in the trie (dictionary) and returns true and false accordingly*/
bool check(Trie *t, char *word, int length) {
  int level, i;
  Trie *temp = t;
  for (level = 0; level < length; level++) {
    i = word[level] - 'a';
    if (!temp->child[i]) {
      return false;
    } else {
      temp = temp->child[i];
    }
  }
  return temp->endNode;
}


/*the function below uses recursion to free all nodes in the trie*/
void freeTrie(Trie *t) {
  if (t == NULL) {
      return;
  }
  for (int i = 0; i < 26; i++) {
      freeTrie(t->child[i]);
  }
  free(t);
}