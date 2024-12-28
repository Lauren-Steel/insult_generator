#pragma once

#include <string>
#include <vector>
using namespace std;

//This exception is thrown if the given source file cannot be accessed/read/created
class FileException {
public:
    //FileException constructor
    FileException(const string& message);
    string what() const;
private:
    string message;
};

//This exception is thrown if the given number of insults to be generated is not between 1 and 10,000
class NumInsultsOutOfBounds{
public:
    //NumInsultsOutOfBounds constructor
    NumInsultsOutOfBounds(const string&);
    string what() const;
private:
    string message;
};

//Class that generates the insults
class InsultGenerator {
public:

    //Empty constructor
    InsultGenerator();

    //Loading contents from the given source file
    void initialize();

    //Returns one insult
    string talkToMe() const;

    //Returns multiple different insults
    vector<string> generate(int numInsults) const;

    //Generates and saves multiple different insults in alphabetical order
    void generateAndSave(string filename, int numInsults) const;

    //Number of lines in the source file
    int sourceSize;

    //Words in the first column
    vector<string> wordOne;

    //Words in the second column
    vector<string> wordTwo;

    //Words in teh third column
    vector<string> wordThree;

    //Method that generates a random int below the maximum limit
    int randNum(int max) const;

    //The name for the given txt file containing all the strings is referred to as "sourceFile"
private:
    std::string sourceFile = "insultsSource.txt";
};
