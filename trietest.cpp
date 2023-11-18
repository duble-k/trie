#include <iostream>
#include <fstream>
#include "illegal_exception.cpp"
#include "Trie.h"

int main()
{
    Trie trie;
    std::string cmd;
    std::string addWord;
    while (std::cin >> cmd)
    {
        if (cmd == "load")
        {
            std::ifstream fin("../test_cases/corpus.txt");
            while (fin >> addWord)
            {
                trie.insertWord(addWord);
            }
            fin.close();
            std::cout << "success" << std::endl;
        }

        else if (cmd == "i")
        {
            std::cin >> addWord;
            try
            {
                trie.exception(addWord);
                if (trie.insertWord(addWord))
                {
                    std::cout << "success" << std::endl;
                }
                else
                {
                    std::cout << "failure" << std::endl;
                }
            }
            catch (illegal_exception &e)
            {
                std::cout << e.what() << '\n';
            }
        }

        else if (cmd == "s")
        {
            std::cin >> addWord;
            try
            {
                trie.exception(addWord);
                if (trie.searchWord(addWord))
                {
                    std::cout << "found " << addWord << std::endl;
                }
                else
                {
                    std::cout << "not found" << std::endl;
                }
            }
            catch (illegal_exception &e)
            {
                std::cout << e.what() << '\n';
            }
        }

        else if (cmd == "e")
        {
            std::cin >> addWord;
            try
            {
                trie.exception(addWord);
                if (trie.erase(addWord))
                {
                    std::cout << "success" << std::endl;
                }
                else
                {
                    std::cout << "failure" << std::endl;
                }
            }
            catch (illegal_exception &e)
            {
                std::cout << e.what() << '\n';
            }
        }

        else if (cmd == "p")
        {
            trie.print();
        }

        else if (cmd == "spellcheck")
        {
            std::cin >> addWord;
            trie.spellCheck(addWord);
        }

        else if (cmd == "empty")
        {
            if (trie.currentSize() == 0)
            {
                std::cout << "empty 1" << std::endl;
            }
            else
            {
                std::cout << "empty 0" << std::endl;
            }
        }

        else if (cmd == "clear")
        {
            trie.clear();
            std::cout << "success" << std::endl;
        }

        else if (cmd == "size")
        {
            std::cout << "number of words is: " << trie.currentSize() << std::endl;
        }

        else if (cmd == "exit")
        {
            return 0;
        }
    }
}