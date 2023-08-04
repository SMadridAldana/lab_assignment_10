#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie * children[26];
    int status;
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie * temp = (struct Trie *) malloc(sizeof(struct Trie));
    temp->status = 0;
	for(int i=0; i < 26; i++) temp->children[i] = NULL;

    return temp;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	struct Trie *temp = pTrie; 
	for(int i = 0; i < strlen(word); i++){
		int index = (int) word[i] - 'a';
		if(temp->children[index] == NULL) temp->children[index] = createTrie();
		temp = temp->children[index];
	}
	temp->status ++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	struct Trie *temp = pTrie; 
	for(int i = 0; i < strlen(word); i++){
		int index = (int) word[i] - 'a';
		if(temp->children[index] == NULL) return 0;
		temp = temp->children[index];
	}
	return temp->status;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	for(int i = 0; i < 26; i ++){
		if(pTrie->children[i] != NULL) 
			pTrie->children[i] = deallocateTrie(pTrie->children[i]);
	}
	free(pTrie);
	return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE * myFile = fopen(filename, "r");
    int size = 0;
	fscanf(myFile, "%i\n", &size);
	
    for(int i = 0; i < size; i++){

        char buffer[50] = "";
		fscanf(myFile, "%s\n", &buffer);
		pInWords[i] = (char *) malloc(sizeof(char)*(strlen(buffer)+1));
		strcpy(pInWords[i], buffer);

    }
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}