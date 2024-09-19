/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**              
** Class: 	CSC 242
** Assignment: 	Lesson #5
** File: 	KeywordCipher.cpp
** Description: This program encrypts or decrypts an input file into an output
** file using a keyword cipher.
**
** Author: 	Trevor Fune
** Date: 	28 Aug 2024
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <algorithm>

using namespace std;

// Create constant string variable with alphabet
const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 

/**
 * Creates encrypted alphabet using a keyword and remaining letters in reverse order
 * @param keyword the word used to create cipher
 * @return a string containing the encrypted alphabet
 */

string create_encrypted_alphabet(const string& keyword)
{
    string encrypted_alphabet; // Create string named encrypted_alphabet
    bool used[26] = { false }; // Create boolean array of size 26 named used to hold used letters
    
    // For every character in keyword
    char ch;
    for (int i = 0; i < keyword.length(); i++)
    {
        ch = toupper(keyword[i]); // Convert character to uppercase

        if (isalpha(ch) && !used[ch - 'A']) // If character is a letter and has not been used
        {
            encrypted_alphabet += ch; // Append character to encrypted_alphabet
            used[ch - 'A'] = true; // Update element representing character in used to true
        }
    }

    string remaining_letters; // Create string named remaining_letters

    for (int i = 0; i < ALPHABET.length(); i++) // For every character in ALPHABET
    {
        ch = ALPHABET[i];
        if (!used[ch - 'A']) // If character hasn't been used yet
        {
            remaining_letters += ch; // Append character to remaining_letters
        }
    }

    reverse(remaining_letters.begin(), remaining_letters.end()); // reverse remaining_letters
    encrypted_alphabet += remaining_letters; // Append remaining_letters to encrypted_alphabet

    return encrypted_alphabet; // Return encrypted_alphabet
}

/**
 * Encrypts a file using an encrypted alphabet
 * @param input ifstream of input file
 * @param output ofstream of output file
 * @param encrypted_alphabet string containing encrypted alphabet
 */
void encrypt_file (ifstream& input, ofstream& output, const string& encrypted_alphabet)
{
    string line; // Create string named line
    while (getline(input, line)) // For every line in input
    {
        char ch;
        string encrypted_line; // Create string named encrypted_line
        for (int i = 0; i < line.length(); i++) // For every character in line
        {
            char ch = line[i]; 
            if (isalpha(ch)) // If character is a letter
            {
                ch = toupper(ch); // Convert character to uppercase
                int pos = ALPHABET.find(ch); // Find position of character in ALPHABET
                encrypted_line += encrypted_alphabet[pos]; // Append encrypted_alphabet[pos] to encrypted_line
             }

            else // If character is not a letter
            {
                encrypted_line += ch; // Append character to encrypted_line
            }
        }
        output << encrypted_line << endl; // Send encrypted line to output
    }
}

/**
 * Decrypts a file using an encrypted alphabet
 * @param input ifstream of input file
 * @param output ofstream of output file
 * @param encrypted_alphabet string containing encrypted alphabet
 */
void decrypt_file (ifstream& input, ofstream& output, const string& encrypted_alphabet)
{
    string line; // Create string named line
    while (getline(input, line)) // For every line in input
    {
        char ch;
        string decrypted_line; // Create string named decrypted_line
        for (int i = 0; i < line.length(); i++) // For every character in line
        {
            char ch = line[i];
            if (isalpha(ch)) // If character is a letter
            {
                ch = toupper(ch); // Convert character to uppercase
                int pos = encrypted_alphabet.find(ch); // Find position of character in encrypted_alphabet
                decrypted_line += ALPHABET[pos]; // Append ALPHABET[pos] to decrypted_line
             }

            else // If character is not a letter
            {
                decrypted_line += ch; // Append character to decrypted_line
            }
        }
        output << decrypted_line << endl; // Send decrypted_line to output
    }
}

int main (int argc, char* argv[])
{
    if (argc != 5) // If number of command line arguments does not equal 5
    {
        cout << "Usage: ./keywordcipher <-e|-d> -k<keyword> <input_file> <output_file>" << endl; // Output error message
        return 1; // Exit program
    }

    string mode = argv[1]; // Create string variable named mode and set equal to argv[1]
    bool encryption_mode = true; // Create boolean variable named encryption_mode and set equal to true

    if (mode == "-e") // If mode is "-e"
    {
        encryption_mode = true; // Keep encryption_mode equal to true
    }

    else if (mode == "-d") // If mode is "-d"
    {
        encryption_mode = false; // Set encryption_mode to false
    }

    else // If neither "-e" or "-d"
    {
        cout << "Invalid mode: use '-e' or '-d'" << endl; // Output error message
        return 1; // Exit program
    }

    string keyword_arg = argv[2]; // Create string named keyword_arg and set equal to argv[2]
    string keyword = keyword_arg.substr(2); // Create string named keyword that holds substring after "-k"

    if (!(keyword_arg.substr(0, 2) == "-k") || keyword.empty()) // If keyword_arg doesn't have "-k" or a keyword
    {
        cout << "Invalid keyword: use -k<keyword>" << endl; // Output error message
        return 1; // Exit program
    }

    ifstream in_file; // Create ifstream named in_file
    in_file.open(argv[3]); // Open argv[3] in in_file
    if (in_file.fail()) // If in_file fails to open
    {
        cout << "Unable to open input file." << endl; // Output error message
        return 1; // Exit program
    }

    ofstream out_file; // Create ofstream named out_file
    out_file.open(argv[4]); // Open argv[4] in out_file
    if (out_file.fail()) // If out_file fails to open
    {
        cout << "Unable to open output file." << endl; // Output error message
        return 1; // Exit program
    }

    // Create string named encrypted_alphabet using the function create_encrypted_alphabet
    string encrypted_alphabet = create_encrypted_alphabet(keyword);

    if (encryption_mode == true) // If encryption_mode is true
    {
        encrypt_file(in_file, out_file, encrypted_alphabet); // Use the function encrypt_file
    }

    else // If encryption_mode is false
    {
        decrypt_file(in_file, out_file, encrypted_alphabet); // Use the function decrypt_file
    }

    return 0;
}