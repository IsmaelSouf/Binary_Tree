//Spell checker created by Ismael Souf, last modification 17/04/2018
//
//Implementation of a spell checker in order to inserts all of the words from the dictionary file into the binary search tree from Part A. This program read in files and check for each word of those files whether or not the word occurs in the dictionary.
// If it does not then the word is misspelt, in which case the program should output the misspelt word to the console.

#include <iostream>
#include <fstream>
#include "bst.h"
#include <cctype>
#include <string>
#include <algorithm>
#include <locale>

using namespace std;

void spell_check(string infile, BinarySearchTree *tree)
{
    ifstream file(infile);
    string word;
    while(file >> word)
    {
        //Transform every words to lowercase
        transform(word.begin(),word.end(),word.begin(),::tolower);
        //Removes punctuation from words
        word.erase(std::remove_if(word.begin(),word.end(),::ispunct),word.end());
        if(!tree->exists(word))
        {
            cout << word << endl;
        }
    }
}

int main()
{
    BinarySearchTree *tree = new BinarySearchTree();
    //Reads into the dictionary
    ifstream dictionary("dictionary.txt");
    dictionary >> *tree;
    //Test on single_words_test.txt
    cout << "\nMisspelled words in single_words_test.txt:\n" << endl;
    spell_check("single_words_test.txt",tree);
    //Test on sentences_test.txt
    cout << "\nMisspelled words in sentences_test.txt:\n" << endl;
    spell_check("sentences_test.txt",tree);
}
