#include <iostream>
#include <iomanip>

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

    int number;
    // We asked the user to input a number, whcih would serve as the maxiumman range for the amount of frequency that would
    // be printed out
    std ::cout << " Please choose the frequency of words that you want to see " << std::endl;
    std::cin >> number;

    // Here we try to print out all the words that appear at a certain frequancy
    // I wanted to see if I can print it out in a literal table but I do not know if it is possible especially
    // with the large amount of words espeically when going through a book
    // Step 3: Display table of word frequencies
    for (int i = 1; i <= number; ++i)
    {
        // Here we take the set which would be returned by the object function
        std::set<std::string> words = wordReader.getWordsByFrequency(i);
        std::cout << "Words that occur " << i << " times:\n";
        // We use a for loop and an iterator to go through the set and print out all the words
        for (auto it = words.begin(); it != words.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << "\n\n";
    }

    // Step 4: Query words by frequency
    // Here we give the user the opportunity to know the words that
    // appear at a certain frequency , the user would be asked to input a number and
    // the words that appeared that number of times would be printed out
    int frequency;
    std::cout << "Enter a frequency to find words (or -1 to exit): ";
    while (std::cin >> frequency && frequency != -1)
    {
        // Transfer the set wigth a specific frequency
        std::set<std::string> words = wordReader.getWordsByFrequency(frequency);
        // Print out the frequancy  or the amount of times that this words come out
        std::cout << "Words that occur " << frequency << " times:\n";
        for (auto it = words.begin(); it != words.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << "\n\n";
        std::cout << "Enter another frequency (or -1 to exit): ";
    }

    std::cout << "Hey now you can check the number of times a word is found in the book, but do not forget this program is not case senstive " << std::endl;
    std::cout << "So please type in all your words in lower case letters " << std ::endl;
    // Here we ask the user to input words to look up in the book to get the number of times they appear in the book as whole
    std::string searchWord;
    std::cout << "Enter a word to search for (or type 'exit' to exit): ";
    while (std::cin >> searchWord && searchWord != "exit")
    {
        int frequency = wordReader.getfrequencyofword(searchWord);
        std::cout << "The word '" << searchWord << "' occurs " << frequency << " times.\n";
        std::cout << "Enter another word to search for (or type 'exit' to exit): ";
    }

    return 0;
}
