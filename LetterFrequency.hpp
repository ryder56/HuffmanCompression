//********************************************************************
// ASU CSE310 Honors Project
// Name of Author: Ryder Roth
// Description: This is the letter frequency class, it is used
//              to take in a file and it will parse the file,
//              and get the characters and their frequency for
//              that particular file.
//********************************************************************
#ifndef LETTER_FREQUENCY_HPP
#define LETTER_FREQUENCY_HPP

#include <fstream>

using namespace std;

class LetterFrequency
{
    private:
        int currentSize;
        int currentMaxSize;
        int currentCharacters;
        int* frequencyArray;
        char* charArray;

        void increaseMaxSize();
        int checkDuplicate(char letter);
        void addLetter(char letter);
        
    public:
        LetterFrequency(ifstream &inFile);
        ~LetterFrequency();
        int getSize();
        char getLetterAt(int index);
        int getFrequencyAt(int index);
        int getLetterFrequency(char letter);
        int getCurrentCharacters();
};

// constructor, takes in a file and gets the frequency of every
// character in that file
LetterFrequency::LetterFrequency(ifstream &inFile)
{
    this->currentSize = 0;
    this->currentMaxSize = 5;
    this->currentCharacters = 0;
    this->frequencyArray = new int[currentMaxSize];
    this->charArray = new char[currentMaxSize];
    string line;
    bool notFirstLine = false;

    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            if (notFirstLine)
            {
                addLetter('\n');
            }
            while (line.size() > 0)
            {
                addLetter(line.at(0));
                line.erase(0,1);
            }
            notFirstLine = true;
        }
    }
}

// destructor
LetterFrequency::~LetterFrequency()
{
    delete this->frequencyArray;
    delete this->charArray;
}

// increases the size of both of arrays
void LetterFrequency::increaseMaxSize()
{
    currentMaxSize = currentMaxSize + 10;
    int* newFrequencyArray = new int[currentMaxSize];
    char* newCharArray = new char[currentMaxSize];
    
    for (int i = 0; i < currentSize; i++)
    {
        newFrequencyArray[i] = frequencyArray[i];
        newCharArray[i] = charArray[i];
    }

    this->frequencyArray = newFrequencyArray;
    this->charArray = newCharArray;
}

// checks the character list for a duplicate, if one exists
// returns the index of the where it is duplicated
int LetterFrequency::checkDuplicate(char letter)
{
    for (int i = 0; i < currentSize; i++)
    {
        if (letter == charArray[i])
        {
            return i;
        }
    }

    return -1;
}

// gets the frequency of a given letter
int LetterFrequency::getLetterFrequency(char letter)
{
    int index = checkDuplicate(letter);

    if (index == -1)
    {
        return 0;
    }
    else 
    {
        return frequencyArray[index];
    }
}

void LetterFrequency::addLetter(char letter)
{
    int index = checkDuplicate(letter);

    if (index == -1)
    {
        if (currentSize <= currentMaxSize)
        {
            increaseMaxSize();
        }
        charArray[currentSize] = letter;
        frequencyArray[currentSize] = 1;
        currentSize++;
        currentCharacters++;
    }
    else
    {
        frequencyArray[index] = frequencyArray[index] + 1;
        currentCharacters++;
    }
    
}

// returns the amount of elements currently in the array
int LetterFrequency::getSize()
{
    return this->currentSize;
}

// returns the letter at a given index
char LetterFrequency::getLetterAt(int index)
{
    return charArray[index];
}

// returns the frequency at a given index
int LetterFrequency::getFrequencyAt(int index)
{
    return frequencyArray[index];
}

int LetterFrequency::getCurrentCharacters()
{
    return this->currentCharacters;
}
#endif