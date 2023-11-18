#include <iostream>
#include "Trie.h"
#include "illegal_exception.cpp"
#include <string>

Trie::Trie()
{
    TrieNode *root = new TrieNode();
    this->root = setNode();
    this->sizeTrie = 0;
}

TrieNode *Trie::setNode(void)
{
    TrieNode *newNode = new TrieNode();

    newNode->endWord = false;

    for (int i = 0; i < 26; i++)
    {
        newNode->subTree[i] = NULL;
    }

    return newNode;
}

bool Trie::insertWord(std::string word)
{
    if (searchWord(word))
    {
        return false;
    }
    TrieNode *tempRoot = this->root;

    for (int i = 0; i < word.length(); i++)
    {
        int index = word[i] - 'a';
        if (tempRoot->subTree[index] == NULL)
        {
            tempRoot->subTree[index] = setNode();
        }
        tempRoot = tempRoot->subTree[index];
    }

    tempRoot->endWord = true;
    this->sizeTrie += 1;
    return true;
}

bool Trie::searchWord(std::string word)
{
    TrieNode *tempRoot = new TrieNode();
    tempRoot = this->root;

    for (int i = 0; i < word.length(); i++)
    {
        int index = word[i] - 'a';
        if (tempRoot->subTree[index] == NULL)
        {
            return false;
        }
        tempRoot = tempRoot->subTree[index];
    }

    return (tempRoot->endWord);
}

bool Trie::emptyCallBack(TrieNode *root)
{
    for (int i = 0; i < 26; i++)
    {
        if (root->subTree[i] != NULL)
        {
            return false;
        }
    }
    return true;
}

bool Trie::empty()
{
    return emptyCallBack(this->root);
}

TrieNode *Trie::eraseWord(TrieNode *root, std::string word, int pos)
{
    // If tree is empty or word doesn't exist
    if (!root || !searchWord(word))
    {
        return NULL;
    }

    // If last character of key is being processed
    if (pos == word.size())
    {

        // This node is no longer end of a word
        if (root->endWord)
            root->endWord = false;

        // If given is not prefix of any other word
        if (emptyCallBack(root))
        {
            delete (root);
            root = NULL;
        }

        return root;
    }

    // If not last character, recur for the subtree
    int index = word[pos] - 'a';
    root->subTree[index] =
        eraseWord(root->subTree[index], word, pos + 1);

    // If root does not have any child and not end of word
    if (emptyCallBack(root) && root->endWord == false)
    {
        delete (root);
        root = NULL;
    }

    return root;
}

bool Trie::erase(std::string word)
{

    if (empty() || !searchWord(word))
    {
        return false;
    }
    TrieNode *result = new TrieNode();
    result = eraseWord(this->root, word);
    if (this->root == NULL)
    {
        this->root = setNode();
        this->sizeTrie -= 1;
        return true;
    }
    else
    {
        this->sizeTrie -= 1;
        return true;
    }
}

void Trie::printWord(char *word, int n, std::string front, bool spellCheck)
{
    if (spellCheck)
    {
        std::cout << front;
    }
    for (int i = 0; i < n; i++)
    {
        std::cout << word[i];
    }
    std::cout << " ";
}

void Trie::printAllWords(TrieNode *root, char *words, int pos)
{
    if (root == NULL)
        return;
    if (root->endWord)
    {
        printWord(words, pos, "", false);
    }
    for (int i = 0; i < 26; i++)
    {
        if (root->subTree[i] != NULL)
        {
            words[pos] = i + 'a';
            printAllWords(root->subTree[i], words, pos + 1);
        }
    }
}

void Trie::print()
{
    char words[10000];
    printAllWords(this->root, words);
    if (!empty())
    {
        std::cout << std::endl;
    }
}

void Trie::clearCallBack(TrieNode *root)
{
    for (int i = 0; i < 26; i++)
    {
        if (root->subTree[i] != NULL)
        {
            clearCallBack(root->subTree[i]);
        }
    }
    delete root;
}

void Trie::clear()
{
    if (this->sizeTrie != 0)
    {
        clearCallBack(this->root);
        this->root = setNode();
        this->sizeTrie = 0;
    }
}

int Trie::currentSize()
{
    int result = this->sizeTrie;
    return result;
}

void Trie::printSpellCheck(TrieNode *root, char *words, std::string front, int pos)
{
    if (root == NULL)
        return;
    if (root->endWord)
    {
        printWord(words, pos, front, true);
    }
    for (int i = 0; i < 26; i++)
    {
        if (root->subTree[i] != NULL)
        {
            words[pos] = i + 'a';
            printSpellCheck(root->subTree[i], words, front, pos + 1);
        }
    }
}

void Trie::spellCheckCallBack(TrieNode *root, std::string word)
{
    TrieNode *tempRoot = new TrieNode();
    tempRoot = root;
    char words[10000];
    if (searchWord(word))
    {
        std::cout << "correct";
    }
    for (int i = 0; i < word.length(); i++)
    {
        int index = word[i] - 'a';
        if (tempRoot->subTree[index] == NULL)
        {
            printSpellCheck(tempRoot, words, word.substr(0, i));
            break;
        }
        if (i == word.length() - 1)
        {
            if (tempRoot->subTree[index] != NULL && tempRoot->subTree[index]->endWord == false)
            {
                printSpellCheck(tempRoot->subTree[index], words, word);
                break;
            }
        }
        tempRoot = tempRoot->subTree[index];
    }
}

void Trie::spellCheck(std::string word)
{
    if (this->root == NULL || this->root->subTree[word[0] - 'a'] == NULL)
    {
        std::cout << std::endl;
    }
    else
    {
        spellCheckCallBack(this->root, word);
        std::cout << std::endl;
    }
}

void Trie::exception(std::string word)
{

    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] < 97 || word[i] > 122)
        {
            throw illegal_exception();
        }
    }
}

Trie::~Trie()
{
    if (this->sizeTrie != 0)
    {
        clear();
    }
}