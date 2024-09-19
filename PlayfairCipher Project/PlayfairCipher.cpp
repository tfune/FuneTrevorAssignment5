/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**              
** Class: 	CSC 242
** Assignment: 	Lesson #5
** File: 	PlayfairCipher.cpp
** Description: This program encrypts or decrypts an input text using a playfair 
**              cipher created using a keyword.
**
** Author: 	Trevor Fune
** Date: 	28 Aug 2024
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>

using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Create constant string variable ALPHABET with all uppercase letters
const int SIZE = 5; // Create constant integer variable SIZE equal to 5

/**
 * Creates encrypted alphabet using keyword and remaining letters excluding 'J'
 * @param keyword the word used for playfair cipher
 * @return a string containing the encrypted alphabet
 * 
 */
string create_encrypted_alphabet(const string& keyword)
{
    string encrypted_alphabet; // Create string named encrypted_alphabet
    bool used[26] = { false }; // Create boolean array that holds used letters
    
    // For every character in keyword
    for (int i = 0; i < keyword.length(); i++)
    {
        char ch = toupper(keyword[i]); // Convert character to uppercase
        if (ch == 'J') { ch = 'I'; } // If character is J convert to I

        if (isalpha(ch) && !used[ch - 'A']) // If character is a letter and has not been used
        {
            encrypted_alphabet += ch; // Append character to encrypted_alphabet
            used[ch - 'A'] = true; // Update element representing character in used to true
        }
    }

    for (int i = 0; i < ALPHABET.length(); i++) // For every character in ALPHABET
    {
        char ch = ALPHABET[i];
        if (!used[ch - 'A'] && ch != 'J') // If character hasn't been used yet and is not J
        {
            encrypted_alphabet += ch; // Append character to remaining_letters
        }
    }

    return encrypted_alphabet; // Return encrypted_alphabet
}

/**
 * Creates a 5x5 vector matrix and fills with encrypted alphabet
 * @param encrypted_alphabet string containing encrypted alphabet
 * @return 5x5 matrix filled with encrypted alphabet
 */
vector< vector<char> > create_playfair_matrix(const string& encrypted_alphabet)
{
    vector< vector<char> > matrix(SIZE, vector<char> (SIZE)); // Initialize a 5x5 vector named matrix
    int index = 0; // Create integer variable named index

    for (int i = 0; i < SIZE; i++) // For every row in matrix
    {
        for (int j = 0; j < SIZE; j++) // For every column in matrix
        {
            matrix[i][j] = encrypted_alphabet[index]; // Update matrix[i][j] to corresponding character in encrypted alphabet
            index++; // Increment index
        }
    }

    return matrix; // Return matrix
}

/**
 * Finds position of a character within matrix
 * @param ch the character we are finding the position of
 * @param matrix the 5x5 matrix that contains encrypted alphabet
 * @param row the row the character is found in
 * @param col the column the character is found in
 */
void find_position (char ch, vector< vector<char> > matrix, int& row, int& col)
{
    for (int i = 0; i < SIZE; i++) // For every row in matrix
    {
        for (int j = 0; j < SIZE; j++) // For every column in matrix
        {
            if (matrix[i][j] == ch) // If we find the character we are looking for
            {
                row = i; // Set row equal to i
                col = j; // Set column equal to j
            }
        }
    }
}

/**
 * Encrypts/decrypts a pair of letters using playfair matrix
 * @param input_pair the pair of letters being encrypted/decrypted
 * @param matrix the 5x5 matrix that contains encrypted alphabet
 * @return a string that contains encrypted pair of letters
 */
string encrypt_pair(string input_pair, vector< vector<char> > matrix)
{
    char ch1 = input_pair[0]; // Create variable named ch1 and set equal to first letter
    char ch2 = input_pair[1]; // Create variable named ch2 and set equal to second letter

    if (!isalpha(ch1) || !isalpha(ch2)) // If ch1 or ch2 are not letters
    {
        return input_pair; // Return original pair of characters
    }

    string encrypted_pair; // Create string variable named encrypted_pair
    int row1, col1, row2, col2 = -1; // Create integer variables that hold row and column of each character

    find_position(ch1, matrix, row1, col1); // Use find_position function for ch1 to update row1 and col1
    find_position(ch2, matrix, row2, col2); // Use find_position function for ch2 to update row2 and col2

    if (row1 == row2 || col1 == col2) // If characters are in the same row or same column
    {
        reverse(input_pair.begin(), input_pair.end()); // Reverse input_pair
        encrypted_pair = input_pair; // Set encrypted_pair equal to input_pair
        return encrypted_pair; // Return encrypted_pair
    }

    else // If characters form a rectangle
    {
        ch1 = matrix[row1][col2]; // Change ch1 to opposite corner in same row
        ch2 = matrix[row2][col1]; // Change ch2 to opposite corner in same row
        encrypted_pair += ch1; // Append ch1 to encrypted_pair
        encrypted_pair += ch2; // Append ch2 to encrypted_pair
        return encrypted_pair; // Return encrypted_pair
    }
}

/**
 * converts line to uppercase and removes any 'J' characters
 * @param line the line that is being processed
 * @return a string with letters in uppercase and no 'J'
 */
string process_line(string line)
{
    string processed_line; // Create string named processed_line
    for(int i = 0; i < line.length(); i++) // For every character in line
    {
        char ch = line[i];
        if (isalpha(ch)) // If character is a letter
        {
            ch = toupper(ch); // Convert character to uppercase
            if (ch == 'J') // If character is 'J'
            {
                ch = 'I'; // Set character equal to 'I'
                processed_line += ch; // Append character to processed_line
            }
            else // If character is not 'J'
            {
                processed_line += ch; // Append character to processed_line
            }
        }
        else // If character is not a letter
        {
            processed_line += ch; // Append character to processed_line
        }
    }

    return processed_line; // Return processed_line
}

/**
 * Encrypts/decrypts a line using a keyword
 * @param keyword the keyword used to create playfair cipher
 * @param input_line the line being encrypted/decrypted
 * @return a string containing the encrypted line
 */
string encrypt_line(string keyword, string input_line)
{
    // Create encrypted alphabet using the function create_encrypted_alphabet
    string encrypted_alphabet = create_encrypted_alphabet(keyword);

    // Create matrix using the function create_playfair_matrix
    vector< vector<char> > matrix = create_playfair_matrix(encrypted_alphabet);

    // Process the input line using the function process_line
    string processed_line = process_line(input_line);

    // Create string named encrypted_line
    string encrypted_line;

    for (int i = 0; i < processed_line.length(); i += 2) // For every 2 characters in line
    {
        string input_pair = processed_line.substr(i, 2); // Extract the 2 characters into variable named input_pair
        string encrypted_pair = encrypt_pair(input_pair, matrix); // Encrypt the pair using the function encrypt_pair
        encrypted_line += encrypted_pair; // Append encrypted_pair to encrypted_line
    }

    return encrypted_line; // Return encrypted_line

}


int main()
{
    string keyword; // Create string variable named keyword
    string input_text; // Create string variable named input_text

    cout << "Please enter keyword: " << endl; // Prompt user to enter keyword
    cin >> keyword; // Store user input into keyword

    // Clear the newline character left after cin >> keyword
    string remainder;
    getline(cin, remainder);

    // Prompt user to enter text that will be encrypted/decrypted
    cout << "Please enter the text you would like to encrypt/decrypt: " << endl;
    getline(cin, input_text); // Store user input into input_text

    // Encrypt/decrypt the input text using the function encrypt_line and keyword
    string encrypted_text = encrypt_line(keyword, input_text);
  
    // Output the encrypted text
    cout << encrypted_text << endl;

    return 0;
}