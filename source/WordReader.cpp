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

// readFile: Opens and reads the content of a text file, storing the frequency of each word.
//  This function is crucial as it populates the wordFrequency map, which is the foundation for all other analyses.
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

// generateFrequencyTable: Processes the wordFrequency map to organize words into sets grouped by their frequency.
// This allows for quick retrieval of all words that appear with the same frequency, aiding in analysis and reporting.
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

// calculateSentiment: Calculates a sentiment score based on the frequencies of positive and negative words.
// This function helps in determining the overall emotional tone of the text.
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

// loadWordsFromFile: Loads words from a specified file into a set. This is used primarily to load positive and negative words for sentiment analysis.
// It ensures all words are in lowercase to maintain case insensitivity.
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

// exportFrequencyTableToJson: Exports the frequency table to a JSON file.
// This method is particularly useful for users who need to process or visualize the data in applications that accept JSON format.
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

// exportFrequencyTableToTxt: Exports the frequency table to a plain text file, listing each frequency and the corresponding words.
// This is useful for users who prefer a simple textual representation of the data.
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

// exportFrequencyTableToCSV: Exports the frequency data to a CSV file, which is useful for further analysis in spreadsheet applications like Microsoft Excel.
// This method organizes the data into columns corresponding to each frequency, facilitating easy analysis of word occurrence patterns.
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
// isAlpha: Checks if the given character 'ch' is an alphabetic character, either uppercase or lowercase.
// This function is essential for the text cleaning process, ensuring that only alphabetic characters are considered in the analysis.
// It is used extensively by the cleanWord function to validate each character of a word.
bool WordReader::isAlpha(char ch) const
{
    return std::isupper(ch) || std::islower(ch); // Checks if the character is either uppercase or lowercase.
}

// getfrequencyofword: Retrieves the frequency of a specific word from the wordFrequency map.
// This function is critical for various features where understanding the occurrence of a particular word is needed, such as during queries or detailed analysis.
// It utilizes a map iterator to find the word in the wordFrequency map and returns its associated frequency.
int WordReader::getfrequencyofword(const std::string &word) const
{
    auto it = wordFrequency.find(word); // Attempts to find the word in the map.
    if (it != wordFrequency.end())
    {
        return it->second; // If found, returns the frequency of the word.
    }
    return 0; // Returns 0 if the word is not found, indicating no occurrences.
}

// searchWordOccurrences: Provides an interactive way for users to search for the frequency of specific words.
// This function prompts the user to enter words and displays how many times each entered word appears in the text.
void WordReader::searchWordOccurrences()
{
    std::string searchWord;
    std::cout << "Enter a word to search for its frequency (or 'exit' to finish): ";
    while (std::cin >> searchWord && searchWord != "exit")
    {                                                                                  // Continues to prompt for words until the user types 'exit'.
        int freq = getfrequencyofword(searchWord);                                     // Retrieves the frequency of the entered word.
        std::cout << "The word '" << searchWord << "' occurs " << freq << " times.\n"; // Displays the frequency.
        std::cout << "Enter another word to search for (or 'exit' to exit): ";         // Prompts for another word or to exit.
    }
}

// queryFrequency: Prompts the user to enter a frequency and displays all words that occur with that frequency.
// It allows repeated queries until the user decides to exit by entering -1.
void WordReader::queryFrequency()
{
    std::cout << "Enter a frequency to find words or -1 to exit: ";
    int frequency;
    std::cin >> frequency;

    while (frequency != -1)
    {
        auto words = getWordsByFrequency(frequency); // Retrieves the set of words that match the entered frequency.
        if (!words.empty())
        {
            std::cout << "Words that occur " << frequency << " times:\n";
            for (const auto &word : words)
            {
                std::cout << word << " "; // Display each word on the same line.
            }
            std::cout << "\n";
        }
        else
        {
            std::cout << "No words found for this frequency.\n"; // Informs the user if no words are found at the specified frequency.
        }
        std::cout << "Enter another frequency or -1 to exit: "; // Allows the user to continuously query different frequencies.
        std::cin >> frequency;
    }
}

// showAllFrequencies: Allows the user to specify a maximum frequency and then displays all words up to that frequency.
// This function is useful for analyzing the spread and commonality of word usage within the text.
void WordReader::showAllFrequencies()
{
    std::cout << "Enter the maximum frequency to display or -1 to exit: ";
    int maxFrequency;
    std::cin >> maxFrequency;

    if (maxFrequency != -1)
    {
        for (int i = 1; i <= maxFrequency; ++i)
        {
            auto words = getWordsByFrequency(i); // Retrieves words for each frequency from 1 to maxFrequency.
            if (!words.empty())
            {
                std::cout << "Words that occur " << i << " times:\n";
                for (const auto &word : words)
                {
                    std::cout << word << " "; // Lists all words at the current frequency.
                }
                std::cout << "\n";
            }
        }
    }
}

// handleExportOptions: Provides a user interface for exporting the frequency table in various formats.
// It guides the user through selecting the file format and entering a filename, enhancing user interaction.
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
        exportFrequencyTableToCSV(exportFilename + ".csv"); // Exports to CSV.
        std::cout << "Data exported to " << exportFilename << ".csv successfully.\n";
        break;
    case 2:
        exportFrequencyTableToJson(exportFilename + ".json"); // Exports to JSON.
        std::cout << "Data exported to " << exportFilename << ".json successfully.\n";
        break;
    case 3:
        exportFrequencyTableToTxt(exportFilename + ".txt"); // Exports to TXT.
        std::cout << "Data exported to " << exportFilename << ".txt successfully.\n";
        break;
    default:
        std::cout << "Invalid option. No export performed.\n"; // Handles user input errors.
    }
}
