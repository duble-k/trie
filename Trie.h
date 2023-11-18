#include <iostream>

class TrieNode
{
public:
    TrieNode *subTree[26];
    bool endWord;
};

class Trie
{
private:
    TrieNode *root;
    int sizeTrie;
    void printWord(char *word, int n, std::string front = NULL, bool spellCheck = false);
    void printAllWords(TrieNode *root, char *words, int pos = 0);
    TrieNode *eraseWord(TrieNode *root, std::string word, int pos = 0);
    bool emptyCallBack(TrieNode *root);
    void clearCallBack(TrieNode *root);
    void spellCheckCallBack(TrieNode *root, std::string word);
    void printSpellCheck(TrieNode *root, char *words, std::string front, int pos = 0);
    TrieNode *setNode();

public:
    Trie();
    ~Trie();
    void exception(std::string word);
    bool insertWord(std::string word);
    bool searchWord(std::string word);
    bool erase(std::string word);
    void print();
    bool empty();
    void clear();
    int currentSize();
    void spellCheck(std::string word);
};