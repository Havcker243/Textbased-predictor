#include "WordReader.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <../nlohmann/json.hpp>
#include <vector>
#include <set>
#include <string>
#include <iomanip>
#include <algorithm> // For max_element
#include <iterator>  // For back_inserter

/*Pseudocode*/
/*function readFile(filename) returns boolean:
    // Attempt to open the file
    open file with given filename
    // Check if file is opened successfully
    if file is not open then
        display "Error: Could not open file"
        return false
    end if

    // Iterate through each word in the file
    for each word in file
        // Clean the word and increment its frequency in wordFrequency
        word = cleanWord(word)
        increment wordFrequency[word]
    end for

    // Return true to indicate success
    return true
end function
*/

// This function is used to open and read through the file
// it also add noth it words and the amount of words into a map
bool WordReader::readFile(const std::string &filename)
{
    // Attempt to open the file
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string word;
    // Iterate through each word in the file
    while (file >> word)
    {
        // Clean the word and increment its frequency in wordFrequency

        wordFrequency[cleanWord(word)]++;
    }
    // Return true to indicate success

    return true;
}

/*Pseudocode*/
/*function generateFrequencyTable():
    // Iterate through each word and its frequency in wordFrequency
    for each pair (word, freq) in wordFrequency
        // Insert the word into the set associated with its frequency in frequencyTable
        insert word into frequencyTable[freq]
    end for
end function
*/
void WordReader::generateFrequencyTable()
{
    // loop through it element in the wordFrequency map
    // use the iterator to point tot he current pair element (word, frequency)
    for (auto it = wordFrequency.begin(); it != wordFrequency.end(); ++it)
    {
        // extract the key value from the pair
        const std::string &word = it->first;
        // extract the value that comes with the key from the pair ( the value
        // is the frequency while the key is the word)
        int freq = it->second;
        // insert the word into the set associated with its frequency in the fequancy table
        // The frequncy table is a map where keys are frequancies and values are sets of words
        frequencyTable[freq].insert(word);
    }
}

int WordReader::calculateSentiment(const std::set<std::string> &positiveWords, const std::set<std::string> &negativeWords)
{
    int sentimentScore = 0;

    for (const auto &word : wordFrequency)
    {
        if (positiveWords.find(word.first) != positiveWords.end())
        {
            sentimentScore += word.second; // Increment score by frequency of positive word
        }
        if (negativeWords.find(word.first) != negativeWords.end())
        {
            sentimentScore -= word.second; // Decrement score by frequency of negative word
        }
    }

    return sentimentScore;
}

void WordReader::loadWordsFromFile(const std::string &filename, std::set<std::string> &wordSet)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open " << filename << std::endl;
        return;
    }

    std::string word;
    while (getline(file, word))
    {
        // Convert word to lowercase before inserting into the set
        std::transform(word.begin(), word.end(), word.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });
        wordSet.insert(word);
    }

    file.close();
}

void WordReader::exportFrequencyTableToJson(const std::string &filename)
{
    nlohmann::json jsonOutput;

    // Constructing the JSON object
    for (const auto &freqPair : frequencyTable)
    {
        std::string freqKey = std::to_string(freqPair.first) + " times";
        // Initialize an empty array for words at this frequency
        nlohmann::json wordArray = nlohmann::json::array();

        // Populate the array with words
        for (const auto &word : freqPair.second)
        {
            wordArray.push_back(word);
        }

        // Assign the array to the corresponding frequency key in the JSON output
        jsonOutput[freqKey] = wordArray;
    }

    // Write the JSON to a file
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Failed to create the JSON file." << std::endl;
        return;
    }

    outFile << jsonOutput.dump(4); // Write JSON data to file without extra indentation for compactness
    outFile.close();
    std::cout << "Data exported to " << filename << ".json" << std::endl;
}

void WordReader::exportFrequencyTableToTxt(const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Failed to create the text file." << std::endl;
        return;
    }

    for (const auto &freqPair : frequencyTable)
    {
        outFile << "Frequency " << freqPair.first << " times:\n";
        for (const auto &word : freqPair.second)
        {
            outFile << word << "\n";
        }
        outFile << "\n";
    }

    outFile.close();
}

// Function to export the frequency table to a specified file.
// This function takes a filename as a parameter and writes the frequency data to this file.
void WordReader::exportFrequencyTableToCSV(const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Failed to create the CSV file." << std::endl;
        return;
    }

    // Finding the maximum frequency to determine the number of columns
    int maxFrequency = 0;
    if (!frequencyTable.empty())
    {
        auto lastItem = frequencyTable.rbegin(); // Last item in the map
        maxFrequency = lastItem->first;
    }

    // Write frequency headers
    for (int i = 1; i <= maxFrequency; ++i)
    {
        outFile << "Appeared " << i << " times,";
    }
    outFile << "\n";

    // Prepare to fill the columns: vector of vectors to store columns
    std::vector<std::vector<std::string>> columns(maxFrequency);

    // Distribute words into columns based on their frequency
    for (const auto &pair : frequencyTable)
    {
        int index = pair.first - 1; // Frequency of 1 goes to index 0
        std::copy(pair.second.begin(), pair.second.end(), std::back_inserter(columns[index]));
    }

    // Determine the maximum number of rows needed by finding the longest column
    size_t maxRows = 0;
    for (const auto &col : columns)
    {
        if (col.size() > maxRows)
        {
            maxRows = col.size();
        }
    }

    // Write rows
    for (size_t i = 0; i < maxRows; ++i)
    {
        for (int j = 0; j < maxFrequency; ++j)
        {
            if (i < columns[j].size())
            {
                outFile << columns[j][i];
            }
            outFile << ",";
        }
        outFile << "\n";
    }

    outFile.close();
    std::cout << "Data exported to " << filename << ".csv" << std::endl;
}

// In this function I used the frequencyTable ( a map which using takes in both a set and a string)
// This function main function is to access the number of words based on the number of times that they apeared
// When the number is ttaken in it would first look for the frequency in the frequency table map
// if it is there it would use the iterator to return the set of words which
// serve as the value part of the map for that frequency
std::set<std::string> WordReader::getWordsByFrequency(int frequency) const
{
    auto it = frequencyTable.find(frequency);
    // Check if the frequency was found in the map.
    if (it != frequencyTable.end())
    {
        return it->second;
    }
    return std::set<std::string>();
}

/*Pseudocode*/
/*function getWordsByFrequency(frequency) returns set of strings
    iterator = frequencyTable.find(frequency)
    if iterator is not at the end of frequencyTable then
        return iterator's second element (set of words)
    end if
    return an empty set of strings
end function
*/

// The cleanword function is used to clean out the words/string or in somple words to remove
// the presence of white spaces or special characters in our word search
// we would first collect the word or string from the document
// and then go through each character
// we then add the charcater to a string and return it as a cleaned word

std::string WordReader::cleanWord(const std::string &word) const
{
    std::string cleanedWord;
    for (auto it = word.begin(); it != word.end(); ++it)
    {
        char ch = *it;
        if (isAlpha(ch))
        {
            cleanedWord.push_back(std::tolower(ch));
        }
    }
    return cleanedWord;
}
/*pseudocode*/
/*function cleanWord(word) returns string
    declare cleanedWord as empty string
        for each character in word do
        if isAlpha(character) then
            cleanedWord = cleanedWord + toLowercase(character)
        end if
    end for
        return cleanedWord
end function
*/

// This function is used to in coinjuction with the cleanword function
// This is used to check if the world is a capital or lower case
bool WordReader::isAlpha(char ch) const
{
    return std::isupper(ch) || std::islower(ch);
}
/*Pseudocode*/
/*
function isAlpha(character) returns boolean
    if character is uppercase or character is lowercase then
        return true
    end if
        return false
end function
*/

// The function uses an iterator to point to the location
// of the word in the unordered map ic word in the unordered map
int WordReader::getfrequencyofword(const std::string &word) const
{
    // use an iterator to point to the word
    auto it = wordFrequency.find(word);
    if (it != wordFrequency.end())
    {
        return it->second;
    }
    return 0;
}

void WordReader::searchWordOccurrences()
{
    std::string searchWord;
    std::cout << "Enter a word to search for its frequency (or 'exit' to finish): ";
    while (std::cin >> searchWord && searchWord != "exit")
    {
        int freq = getfrequencyofword(searchWord);
        std::cout << "The word '" << searchWord << "' occurs " << freq << " times.\n";
        std::cout << "Enter another word to search for (or 'exit' to exit): ";
    }
}

void WordReader::queryFrequency()
{
    std::cout << "Enter a frequency to find words or -1 to exit: ";
    int frequency;
    std::cin >> frequency;

    while (frequency != -1)
    {
        auto words = getWordsByFrequency(frequency);
        if (!words.empty())
        {
            std::cout << "Words that occur " << frequency << " times:\n";
            for (const auto &word : words)
            {
                std::cout << word << " ";
            }
            std::cout << "\n";
        }
        else
        {
            std::cout << "No words found for this frequency.\n";
        }
        std::cout << "Enter another frequency or -1 to exit: ";
        std::cin >> frequency;
    }
}

void WordReader::showAllFrequencies()
{
    std::cout << "Enter the maximum frequency to display or -1 to exit: ";
    int maxFrequency;
    std::cin >> maxFrequency;

    if (maxFrequency != -1)
    {
        for (int i = 1; i <= maxFrequency; ++i)
        {
            auto words = getWordsByFrequency(i);
            if (!words.empty())
            {
                std::cout << "Words that occur " << i << " times:\n";
                for (const auto &word : words)
                {
                    std::cout << word << " ";
                }
                std::cout << "\n";
            }
        }
    }
}

void WordReader::handleExportOptions()
{
    std::cout << "Choose the number to represent the format to export :\n";
    std::cout << "1. CSV\n";
    std::cout << "2. JSON\n";
    std::cout << "3. TXT\n";
    std::cout << "Enter choice: ";

    int formatChoice;
    std::cin >> formatChoice;

    std::cout << "Enter the filename for the export (without extension): ";
    std::string exportFilename;
    std::cin >> exportFilename;

    switch (formatChoice)
    {
    case 1:
        exportFrequencyTableToCSV(exportFilename + ".csv");
        std::cout << "Data exported to " << exportFilename << ".csv successfully.\n";
        break;
    case 2:
        exportFrequencyTableToJson(exportFilename + ".json");
        std::cout << "Data exported to " << exportFilename << ".json successfully.\n";
        break;
    case 3:
        exportFrequencyTableToTxt(exportFilename + ".txt");
        std::cout << "Data exported to " << exportFilename << ".txt successfully.\n";
        break;
    default:
        std::cout << "Invalid option. No export performed.\n";
    }
}
