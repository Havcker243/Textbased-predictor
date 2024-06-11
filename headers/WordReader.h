#ifndef WORDREADER_H
#define WORDREADER_H

#include <string>
#include <unordered_map>
#include <map>
#include <set>

class WordReader
{
public:
    // Here it reads the file with the given filename , cleans the words in the filename
    // it then stors them along with thier frequencoes in a wordFrequency map
    bool readFile(const std::string &filename);

    // This generates a frequency table that maps each frequency to set of words (The words have to have appared the amount of times in the frequency )
    void generateFrequencyTable();

    // Returns a set of words that have appeared the number of times (frequency ) and if no words have the
    // given frequency an enpty set would be released
    std::set<std::string> getWordsByFrequency(int frequency) const;

    // This function is to try and return the values and the results into a csv file or pdf file for student to be able to use 
   void exportFrequencyTableToCSV(const std::string &filename);

    // This is used to checks if this is an alphabet
    bool isAlpha(char ch) const;

    // This is used to clean out the input word by removing non-word characters
    // and changing it to lowercase
    std::string cleanWord(const std::string &word) const;

    // So if we want to get the number of times the word comes up in a word we would use this function
    int getfrequencyofword(const std::string &word) const;

private:
    // A map to store the frequency of each word. The key is the word and
    // the value is its frequency.
    std::unordered_map<std::string, int> wordFrequency;

    // A map to store sets of words for each frequency. The key is the frequency
    // and the value is a set of words having that frequency.
    std::map<int, std::set<std::string>> frequencyTable;
};

#endif // WORDREADER_H