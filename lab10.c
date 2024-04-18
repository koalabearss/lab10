#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26 // Assuming only lowercase letters

// Trie node structure
struct TrieNode {
    int wordCount; // Number of times a word ending here has been inserted
    struct TrieNode *children[ALPHABET_SIZE];
};

// Trie structure containing the root node
struct Trie {
    struct TrieNode *root;
};

// Create a new trie node
struct TrieNode *createTrieNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->wordCount = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            node->children[i] = NULL;
    }
    return node;
}

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    if (trie) {
        trie->root = createTrieNode();
    }
    return trie;
}

// Inserts the word into the trie structure
void insert(struct Trie *trie, char *word) {
    struct TrieNode *walker = trie->root;
    int index;

    for (int level = 0; level < strlen(word); level++) {
        index = word[level] - 'a'; // Convert character to index (0-25)
        if (!walker->children[index]) {
            walker->children[index] = createTrieNode();
        }
        walker = walker->children[index];
    }
    walker->wordCount++; // Mark the end of a word and increase its count
}

// Computes the number of occurrences of the word in the trie
int numberOfOccurances(struct Trie *trie, char *word) {
    struct TrieNode *walker = trie->root;
    int index;

    for (int level = 0; level < strlen(word); level++) {
        index = word[level] - 'a';
        if (!walker->children[index])
            return 0; // If node does not exist, word does not exist
        walker = walker->children[index];
    }
    return walker->wordCount;
}

// Deallocate the trie node recursively
void deallocateTrieNode(struct TrieNode *node) {
    if (node) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                deallocateTrieNode(node->children[i]);
            }
        }
        free(node);
    }
}

// Deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *trie) {
    if (trie) {
        deallocateTrieNode(trie->root);
        free(trie);
        trie = NULL;
    }
    return trie;
}

int main(void) {
    struct Trie *trie = createTrie();

    // Sample words for demonstration. Normally you would read from a file
    char *words[] = {"hello", "world", "hello", "test", "hello", "goodbye"};
    int numWords = sizeof(words) / sizeof(words[0]);

    for (int i = 0; i < numWords; i++) {
        insert(trie, words[i]);
    }

    char *testWords[] = {"hello", "world", "test"};
    for (int i = 0; i < 3; i++) {
        printf("\t%s : %d\n", testWords[i], numberOfOccurances(trie, testWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");

    return 0;
}
