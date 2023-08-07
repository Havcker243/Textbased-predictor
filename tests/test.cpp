#include "WordReader.h"
#include <gtest/gtest.h>


// Test to check if the file is read successfully
TEST(WordReaderTest, ReadsFileSuccessfully)
{
    WordReader wordReader;
    // Here we use the Assert true function to return a pass result
    // if the object method (wordReader.readFile ) returns a true
    std::string file ;
    std:: cout << "Please input a txt file " << std:: endl;
    std::cin >> file; 
    ASSERT_TRUE(wordReader.readFile(file));
}

// Test to check if cleaned words only contain alphabetic characters
TEST(WordReaderTest, CleanWordFunctionality)
{
    WordReader wordReader;
    std::string original = "This#*^$() is a test!@$";
    std::string expected = "thisisatest";
    // Here we use the Assert function to check if they both return the same value
    // We call out the cleanword fucntion with the wordReader function and comapre the return value
    ASSERT_EQ(wordReader.cleanWord(original), expected);
}

// Test to check if getWordsByFrequency retrieves words with correct frequency
TEST(WordReaderTest, GetWordsByFrequencyFunctionality)
{
    WordReader wordReader;
     std::string file ;
    std:: cout << "Please input a txt file " << std:: endl;
    std::cin >> file; 
    wordReader.readFile(file);
    wordReader.generateFrequencyTable();

    // From prevouse test we understand that the word voyage appears a total of 99 times in the book MobyDick so 
    // this test is used to check if that is correct 
    std::set<std::string> words = wordReader.getWordsByFrequency(99);
    ASSERT_TRUE(words.find("voyage") != words.end());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
