/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
** 
** Class: 	CSC 242
** Assignment: 	Lesson #5
** File: 	SpellCheck.cpp
** Description: This program checks the spelling of all words in the file
** "CheckFile.txt" and prints all words not found in the dictionary.
**
** Author: 	Trevor Fune
** Date: 	28 Aug 2024
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main ()
{
    ifstream dictionary; // Declare input-stream variable named dictionary

    dictionary.open("/usr/share/dict/words"); // Open the dictionary file in dictionary
    if (dictionary.fail()) // If file doesn't open
    {
        cout << "Unable to open dictionary file." << endl; // Output "Unable to open dictionary file."
    }

    vector <string> words; // Define a vector of strings called words
    string word; // Define a string called word

    while (dictionary >> word) // For each word in the dictionary file:
    {
        words.push_back(word); // Append the word to the words vector
    }

    dictionary.close(); // Close the dictionary file

    ifstream words_to_check; // Declare input-stream variable named words_to_check

    words_to_check.open("WordsToCheck.txt");  // Open the file to be checked in words_to_check
    if (words_to_check.fail()) // If file doesn't open:
    {
        cout << "Unable to open file to check spelling." << endl; // Output "Unable to open file to check spelling."
    }

    while (words_to_check >> word) // For each word in words_to_check:
    {
        if (find(words.begin(), words.end(), word) == words.end()) // If the word is not contained in the words vector:
        {
            cout << word << endl; // Print the word
        }
    }

    return 0;
}