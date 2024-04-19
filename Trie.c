#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie structure
struct Trie
{	
  struct Trie *children[ALPHABET_SIZE];
  int isEndOfWord;
  int count;
};


// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
  struct Trie *current = pTrie;
  for (int i = 0; word[i] != '\0'; i++) {
    int index = word[i] - 'a';
    // if word is not found
    if (!current->children[index]) {
      return 0;
    }
      current = current->children[index];
  }
  if (current != NULL && current->isEndOfWord) {
    return current->count;
  } 
  // if word is not found
  else {
    return 0;
  }
}


// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
  if (pTrie == NULL) {
    return NULL;
  }
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    deallocateTrie(pTrie->children[i]);
  }
  free(pTrie);
  return NULL;
}


// Initializes a trie structure
struct Trie *createTrie()
{
  struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
  return pTrie;
}


// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
  struct Trie *current = pTrie;
  for (int i = 0; word[i] != '\0'; i++) {
    int index = word[i] - 'a';
    if (!current->children[index]) {
      current->children[index] = createTrie();
    }
    current = current->children[index];
  }
  current->isEndOfWord = 1;
  current->count++;
}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("Error opening file %s\n", filename);
    exit(1);
  }

  int numWords = 0;
  char word[256];
  while (fscanf(file, "%s", word) != EOF) {
    pInWords[numWords] = strdup(word);
    numWords++;
  }

  fclose(file);
  return numWords;
}


// Main function
int main(void)
{
  char *inWords[256];

  //read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  for (int i=0;i<numWords;++i) {
    printf("%s\n",inWords[i]);
  }

  struct Trie *pTrie = createTrie();
  for (int i=0;i<numWords;i++) {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i=0;i<5;i++) {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}
