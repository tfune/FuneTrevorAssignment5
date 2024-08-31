/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**              
** Class: 	CSC 242
** Assignment: 	Lesson #5
** File: 	WorldPop.cpp
** Description: This program reads a file containing country data and 
** prints the total of all country populations (except EU)
**
** Author: 	Trevor Fune
** Date: 	28 Aug 2024
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

/**
 * Processes line containing country name and population into separate variables
 * @param line the string being processed
 * @param country name of country in line
 * @param population population of country
 */

void process_line(const string& line, string& country, int& population) // Create void function named process_line
{
    istringstream strm(line); // Create istringstream named strm that contains line

    char ch; // Create char variable named ch

    while (strm.get(ch)) // For every character in strm
    {
        if (!isspace(ch)) // If character is not a white space
        {
            country += ch; // Append character to country
        }
        else // If character is a white space
        {
            while (strm.get(ch) && isspace(ch)); // Skip to next non-white space character
            if (!isdigit(ch)) // If character is not a digit
            {
                country += ' '; // Append a space to country
                country += ch; // Append character to country
            }

            else // If character is a digit
            {
                strm.unget(); // Unget the character
                strm >> population; // Place the whole number into population
                break; // Break out of function
            }
        }
    }    
}

int main ()
{
    ifstream input_file; // Declare input-stream variable named input_file
    input_file.open("worldpop.txt"); // Open "worldpop.txt" in input_file

    if (input_file.fail()) // If the file doesn't open
    {
        cout << "Unable to open world population file." << endl; // Output error message
    }

    string line; // Create a string variable named line
    double total_population = 0; // Create a floating-point variable named total_population

    while (getline(input_file, line)) // For every line in input_file
    {
        string country; // Create a string variable named line
        int population = 0; // Create an integer variable named population

        process_line(line, country, population); // Make function call to process_line

        if (country != "European Union") // If country is not the EU
        {
            total_population = total_population + population; // Add population to total_population
        }
    }

    input_file.close(); // Close the file

    cout << "Total Population (Excluding EU): " << total_population << endl; // Output total_population excluding EU

    return 0;
}