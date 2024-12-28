#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <cstdlib>

#include "insultgenerator_19les5.h"

using namespace std;

//FileException class is to throw an error if the file cannot be read/accessed/created
FileException::FileException(const string& m) : message(m) {}
string FileException::what() const{
    return message;
}

/*NumInsultsOutOfBounds class is to throw an error if the given number of insults to be
 * generated is not between 1 and 10,000*/
NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& m) : message(m) {}
string NumInsultsOutOfBounds::what() const {
    return message;
}

//InsultGenerator constructor
InsultGenerator::InsultGenerator() : sourceSize (0) {
    srand(time(0));
}

//Initializer will read the txt file and split each line into three column vectors
void InsultGenerator::initialize(){
    string line;
    int counter(0);
    ifstream fileIn(sourceFile);
    if (fileIn.fail())
        //Throw error if the file cannot be read
        throw FileException("Cannot read " + sourceFile);

    sourceSize = 0;
    while (!fileIn.eof()){
        fileIn >> line;
        wordOne.push_back(line);
        fileIn >> (line);
        wordTwo.push_back(line);
        fileIn >> line;
        wordThree.push_back(line);
        counter++;
    }
    this -> sourceSize = counter;
    fileIn.close();
    return;
}

//Generates a random int below maxLim
int InsultGenerator::randNum(int max) const{
    return rand() % max;
}

//Returns one insult
string InsultGenerator::talkToMe() const{
    string oneInsult("Thou ");
    oneInsult += wordOne.at(randNum(sourceSize));
    oneInsult += " " + wordTwo.at(randNum(sourceSize))+ " ";
    oneInsult += wordThree.at(randNum(sourceSize)) + "!";
    return oneInsult;
}

//Generate method creates the given number of insults and returns a vector of strings in order
vector<string> InsultGenerator::generate(int numInsults) const {
    int max (10000);
    if (numInsults > max || numInsults < 1)
        throw NumInsultsOutOfBounds("Number out of range, the value must fall between 1 and 10,000.");

    vector<string> insults;
    int counter(0);
    int one, two, three;
    string theInsult;

    /*The method uses a bool Array to generate the specified numInsults, the dimensions
     * of the Array correspond to one of the source line sections that were split onto 3.
     * If the value of Array at this location is true, it will use this word at the
     * corresponding index location in line vector*/
    bool Array[sourceSize][sourceSize][sourceSize];

    for (one=0; one<sourceSize; one++)
        for(two=0; two<sourceSize; two++)
            for (three=0; three<sourceSize; three++)
                Array[one][two][three] = false;
    while (counter < numInsults){
        /*Generating three random numbers and ensuring Array location is set to true until
         * specified number of array locations is met*/
        one = randNum(sourceSize);
        two = randNum(sourceSize);
        three = randNum(sourceSize);
        if (!Array[one][two][three]){
            Array[one][two][three] = true;
            counter++;
        }
    }
    //Generating the insults using index location then adding them to a vector
    counter = 0;
    for (one=0; one<sourceSize && counter<numInsults; one++)
        for (two=0; two<sourceSize && counter<numInsults; two++)
            for (three=0; three<sourceSize && counter<numInsults; three++)
                if (Array[one][two][three]) {
                    theInsult = "Thou " + wordOne.at(one) + " " + wordTwo.at(two) + " " + wordThree.at(three) + "!";
                    insults.push_back(theInsult);
                    counter++;
                }
    return insults;
}

/*Method generateAndSave creates the given number of insults and returns insults
 * as a vector of strings and outputs the insults into the specified file*/
void InsultGenerator::generateAndSave(string inputFile, int numInsults) const {
    int counter (0);
    int max (10000);
    if (numInsults > max || numInsults < 1)
        throw NumInsultsOutOfBounds("Number out of range, the value must fall between 1 and 10,000.");

    vector<string> insults (generate(numInsults));
    ofstream fileOut(inputFile);

    if (fileOut.fail())
        throw FileException("Input file " + inputFile + " cannot be written.");

    while (counter < numInsults){
        fileOut << insults[counter] << endl;
        counter++;
    }
}
