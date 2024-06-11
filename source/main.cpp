#include <iostream>
#include <iomanip>
#include <fstream>
#include <../nlohmann/json.hpp>
#include "WordReader.h"

int main()
{
    WordReader wordReader;

    // Step 1: Ask user for file name
    std::cout << "Enter the name of the text file: ";
    std::string filename;
    std::cin >> filename;

    // Step 2: Read and process the text file
    if (!wordReader.readFile(filename))
    {
        // Print out failed message if the txt file could not be opened
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    // Here we generate the frequency table
    wordReader.generateFrequencyTable();
   // Ask if the user wants to export the frequency data
    std::cout << "Do you want to export the frequency table to a CSV file? (yes/no): ";
    std::string response;
    std::cin >> response;

    // Ask if the user wants to export the frequency data and in which format
    std::cout << "Do you want to export the frequency table? Enter 'CSV' for CSV file, 'JSON' for JSON file, 'TXT' for text file, or 'NO' to skip: ";
    std::string exportChoice;
    std::cin >> exportChoice;

    if (exportChoice == "CSV" || exportChoice == "JSON" || exportChoice == "TXT")
    {
        std::cout << "Enter the filename for the export (without extension): ";
        std::string exportFilename;
        std::cin >> exportFilename;

        if (exportChoice == "CSV")
        {
            wordReader.exportFrequencyTableToCSV(exportFilename + ".csv");
        }
        else if (exportChoice == "JSON")
        {
            wordReader.exportFrequencyTableToJson(exportFilename + ".json");
        }
        else if (exportChoice == "TXT")
        {
            wordReader.exportFrequencyTableToTxt(exportFilename + ".txt");
        }
    }

    // Step 3: Display table of word frequencies
    std::cout << "Please enter the a number, this number would serve as the top requency, this means that we would show you all the words that appear from at a frewqucny of 1 to the frequncy  of the amount chosen (or -1 to exit): ";
    int maxFrequency;
    std::cin >> maxFrequency;
    if (maxFrequency != -1)
    {
        for (int i = 1; i <= maxFrequency; ++i)
        {
            std::set<std::string> words = wordReader.getWordsByFrequency(i);
            if (!words.empty())
            {
                std::cout << "Words that occur " << i << " times:\n";
                for (const auto &word : words)
                {
                    std::cout << word << " ";
                }
                std::cout << "\n\n";
            }
        }
    }

    // Step 4: Query words by frequency
    // Here we give the user the opportunity to know the words that
    // appear at a certain frequency , the user would be asked to input a number and
    // the words that appeared that number of times would be printed out
    // Query specific frequency
    std::cout << "Enter a frequency to find words (or -1 to exit): ";
    int queryFrequency;
    while (std::cin >> queryFrequency && queryFrequency != -1)
    {
        std::set<std::string> words = wordReader.getWordsByFrequency(queryFrequency);
        if (!words.empty())
        {
            std::cout << "Words that occur " << queryFrequency << " times:\n";
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
        std::cout << "Enter another frequency (or -1 to exit): ";
    }

    // Step 5: Search for word occurrences
    std::cout << "Enter a word to search for its frequency (or 'exit' to finish): ";
    std::string searchWord;
    while (std::cin >> searchWord && searchWord != "exit")
    {
        int wordFrequency = wordReader.getfrequencyofword(searchWord);
        std::cout << "The word '" << searchWord << "' occurs " << wordFrequency << " times.\n";
        std::cout << "Enter another word to search for (or 'exit' to exit): ";
    }

    return 0;
}
