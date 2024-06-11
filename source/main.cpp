#include <iostream>
#include <iomanip>
#include <fstream>
#include <../nlohmann/json.hpp>
#include "WordReader.h"

// Function to display the main menu
void showMenu()
{
    std::cout << "\n---- Main Menu ----\n";
    std::cout << "1. Load and Analyze Text File (Recommended as first option )\n";
    std::cout << "2. Export Frequency Table\n";
    std::cout << "3. Show Word Frequencies\n";
    std::cout << "4. Query Specific Frequency\n";
    std::cout << "5. Perform Sentiment Analysis\n";
    std::cout << "6. Search for Word Occurrences\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

int main()
{

    WordReader wordReader;               // Instance of WordReader to handle text analysis
    std::set<std::string> positiveWords; // Set to store positive words for sentiment analysis
    std::set<std::string> negativeWords; // Set to store negative words for sentiment analysis
    std::string filename;                // Variable to store the filename input by the user
    int Score;                           // Variable to store the sentiment score
    bool running = true;                 // Control variable for the main menu loop
    int choice;                          // Variable to store user menu choice

    while (running)
    {
        showMenu();// Display the menu options to the user

        std::cin >> choice;// Read user choice

        switch (choice)
        {
        case 1:
            std::cout << "Enter the name of the text file: ";

            std::cin >> filename;
            if (!wordReader.readFile(filename))
            {
                std::cerr << "Failed to open the file." << std::endl;
            }
            else
            {
                wordReader.loadWordsFromFile("positive_words.txt", positiveWords);
                wordReader.loadWordsFromFile("negative_words.txt", negativeWords);
                wordReader.generateFrequencyTable();
                std::cout << "File loaded and analyzed successfully.\n";
            }
            break;
        case 2:
            wordReader.handleExportOptions(); // Handle different export options
            break;
        case 3:
            wordReader.showAllFrequencies();// Display all frequencies up to a user-defined limit
            break;
        case 4:
            wordReader.queryFrequency();// Allow the user to query the frequency of specific words
            break;
        case 5:
            Score = wordReader.calculateSentiment(positiveWords, negativeWords);
            std::cout << "Sentiment Score: " << Score << std::endl;
            if (Score > 0)
            {
                std::cout << "Overall sentiment is positive.\n";
            }
            else if (Score < 0)
            {
                std::cout << "Overall sentiment is negative.\n";
            }
            else
            {
                std::cout << "Overall sentiment is neutral.\n";
            }
            break;
        case 6:
            wordReader.searchWordOccurrences();// Search for occurrences of a specific word
            break;
        case 7:
            running = false;
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
