#ifndef WORDREADER_H
#define WORDREADER_H

#include <string>
#include <unordered_map>
#include <map>
#include <set>

// Class WordReader is designed for analyzing text files to determine the frequency of word occurrences
// and providing various outputs based on these frequencies. It also performs sentiment analysis.
class WordReader
{
public:
    // readFile: Opens and processes the specified text file, extracting words and calculating their frequencies.
    // It uses cleanWord to standardize words before counting.
    bool readFile(const std::string &filename);

    // generateFrequencyTable: Creates a table mapping each frequency to the set of words that appear that many times.
    // This facilitates efficient retrieval of words based on their frequency.
    void generateFrequencyTable();

    // getWordsByFrequency: Returns a set of words that appear with the specified frequency.
    // If no words are found for the given frequency, it returns an empty set.
    std::set<std::string> getWordsByFrequency(int frequency) const;

    // exportFrequencyTableToCSV: Exports the frequency table to a CSV file.
    // Useful for analysis in spreadsheet software.
    void exportFrequencyTableToCSV(const std::string &filename);

    // exportFrequencyTableToJson: Exports the frequency data to a JSON file, suitable for web applications
    // or data interchange with other applications.
    void exportFrequencyTableToJson(const std::string &filename);

    // searchWordOccurrences: Allows the user to search for the frequency of specific words interactively.
    // Continues until 'exit' is entered.
    void searchWordOccurrences();

    // queryFrequency: Interactive function that displays all words that occur with a specified frequency.
    void queryFrequency();

    // showAllFrequencies: Prompts the user for a maximum frequency and displays all frequencies up to that number.
    void showAllFrequencies();

    // handleExportOptions: Manages user choices for exporting data, allowing selection of the format.
    void handleExportOptions();

    // exportFrequencyTableToTxt: Exports the frequency table to a plain text file, listing frequencies and corresponding words.
    void exportFrequencyTableToTxt(const std::string &filename);

    // calculateSentiment: Calculates a sentiment score based on the frequency of words in positiveWords and negativeWords sets.
    int calculateSentiment(const std::set<std::string> &positiveWords, const std::set<std::string> &negativeWords);

    // loadWordsFromFile: Loads words from a specified file into a given set. Mainly used to load positive and negative words.
    void loadWordsFromFile(const std::string &filename, std::set<std::string> &wordSet);

    // isAlpha: Utility function to check if a character is an alphabetic letter.
    bool isAlpha(char ch) const;

    // cleanWord: Standardizes input words by converting to lowercase and removing non-alphabetic characters.
    std::string cleanWord(const std::string &word) const;

    // getfrequencyofword: Retrieves the frequency of a specific word from the wordFrequency map.
    int getfrequencyofword(const std::string &word) const;

private:
    // wordFrequency: Stores each word's frequency count using a map where the key is the word and the value is its frequency.
    std::unordered_map<std::string, int> wordFrequency;

    // frequencyTable: Organizes words into sets based on their frequency of appearance.
    // Facilitates easy access to words by their frequency.
    std::map<int, std::set<std::string>> frequencyTable;
};

#endif // WORDREADER_H