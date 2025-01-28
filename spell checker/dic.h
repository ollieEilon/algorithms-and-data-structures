// declares a dictionary

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdbool.h>
#define LENGTH 45

/*below is the struct for a trie*/
typedef struct TrieNode Trie;
struct TrieNode {
  int endNode;
  Trie *child[26];
};

Trie *newTrie();
void addWord(Trie *t, char *word);
bool check(Trie *t, char *word, int length);
void freeTrie(Trie *node);


#endif 