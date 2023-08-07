#include "WordReader.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <iomanip>

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
    //use an iterator to point to the word 
    auto it = wordFrequency.find(word);
    if (it != wordFrequency.end())
    {
        return it->second;
    }
    return 0;
}