//********************************************************************
// ASU CSE310 Honors Project
// Name of Author: Ryder Roth
// Description: This is the huffman compression class. it is used to
//              take in the frequency of letters and then build a final
//              huffman node once the BuildFinalHuffmanNode when it is called.
//              to comrpess the given file.
//********************************************************************
#ifndef HUFFMAN_COMPRESSION_HPP
#define HUFFMAN_COMPRESSION_HPP

#include "HuffmanNode.hpp"
#include "BinaryHeap.h"
#include "LetterFrequency.hpp"
#include <iomanip>

using namespace std;


class HuffmanCompression
{
    private:
        int size;
        BinaryHeap<HuffmanNode*>* HuffmanNodeArray;
        HuffmanNode* finalHuffmanNode;

    public:
        HuffmanCompression(int size);
        ~HuffmanCompression();
        void InsertNode(char letter, int frequency);
        void BuildFinalHuffmanNode();
        string EncryptFile(ifstream &fileToEncrypt);
        void EncryptAndWriteToFile(ifstream &fileToEncrypt, ofstream &fileToWriteTo);
        void printOptimalHuffmanCodeAndCompressionRate(LetterFrequency* letterFrequencies);
        HuffmanNode* getFinalHuffmanNode();
};

// Constructor for huffman compression class,
// takes in the number of characters that are going
// to be passed to it to build the binary heap.
HuffmanCompression::HuffmanCompression(int size)
{
    this->size = size;
    this->HuffmanNodeArray = new BinaryHeap<HuffmanNode*>(size);
    this->finalHuffmanNode = NULL;
}

// destructor for huffman compression class
HuffmanCompression::~HuffmanCompression()
{
    delete this->HuffmanNodeArray;
    delete this->finalHuffmanNode;
}

// creates a node based off of the letter and its frequency,
// then inserts it into the huffman array.
void HuffmanCompression::InsertNode(char letter, int frequency)
{
    HuffmanNode *newHuffmanNode = new HuffmanNode();
    newHuffmanNode->setFrequency(frequency);
    newHuffmanNode->setLetter(letter);
    HuffmanNodeArray->insert(newHuffmanNode);
}

// builds the final huffman node, which
// will represent the huffman compression
// for the characters and the frequency
// given.
void HuffmanCompression::BuildFinalHuffmanNode()
{
    HuffmanNode *min1, *min2, *newNode;
    int frequency;

    while (size > 1)
    {
        min1 = HuffmanNodeArray->findMin();
        HuffmanNodeArray->deleteMin();
        frequency = min1->getFrequency();

        min2 = HuffmanNodeArray->findMin();
        HuffmanNodeArray->deleteMin();
        frequency += min2->getFrequency();

        size--;

        newNode = new HuffmanNode();
        newNode->setFrequency(frequency);
        newNode->setLeftChild(min1);
        newNode->setRightChild(min2);
        min1->setParent(newNode);
        min2->setParent(newNode);

        HuffmanNodeArray->insert(newNode);
    }
    finalHuffmanNode = new HuffmanNode();
    min1 = HuffmanNodeArray->findMin();
    finalHuffmanNode->setLeftChild(min1->getLeftChild());
    finalHuffmanNode->setRightChild(min1->getRightChild());
    finalHuffmanNode->setFrequency(min1->getFrequency());

}

//same as encrypt file, but writes the output to a file named "encryption.txt"
void HuffmanCompression::EncryptAndWriteToFile(ifstream &fileToEncrypt, ofstream &fileToWriteTo)
{
    HuffmanCodeVector* huffmanCodes = finalHuffmanNode->getHuffmanCodes();
    int size = huffmanCodes->size();
    HuffmanCode* currentCode;
    string line;
    bool anotherLine;
    char letterToEncrypt;

    if (fileToEncrypt.is_open())
    {
        getline(fileToEncrypt, line);
        do 
        {
            //get each character for the line
            while (line.length() > 0)
            {
                letterToEncrypt = line.at(0);
                for (int i = 0; i < size; i++)
                {
                    currentCode = huffmanCodes->at(i);
                    if (currentCode->letter == letterToEncrypt)
                    {
                        fileToWriteTo << currentCode->code;
                        i = size;
                    }
                }
                line.erase(0,1);
            }

            anotherLine = false;
            // get the next line, if it exists add a new line character
            // if not exit the loop.
            if (getline(fileToEncrypt, line))
            {
                anotherLine = true;
            }
            if (anotherLine)
            {
                letterToEncrypt = '\n';
                for (int i = 0; i < size; i++)
                {
                    currentCode = huffmanCodes->at(i);
                    if (currentCode->letter == letterToEncrypt)
                    {
                        fileToWriteTo << currentCode->code;
                        i = size;
                    }
                }
            }
        } while((anotherLine));
    }
}

// takes in a file and encrypts it all into the huffman code 
// and returns a string that is what it would be encrypted as
string HuffmanCompression::EncryptFile(ifstream &fileToEncrypt)
{
    HuffmanCodeVector* huffmanCodes = finalHuffmanNode->getHuffmanCodes();
    int size = huffmanCodes->size();
    HuffmanCode* currentCode;
    string output = "";
    string line;
    bool anotherLine;
    char letterToEncrypt;

    if (fileToEncrypt.is_open())
    {
        getline(fileToEncrypt, line);
        do 
        {
            //get each character for the line
            while (line.length() > 0)
            {
                letterToEncrypt = line.at(0);
                for (int i = 0; i < size; i++)
                {
                    currentCode = huffmanCodes->at(i);
                    if (currentCode->letter == letterToEncrypt)
                    {
                        output = output + currentCode->code;
                        i = size;
                    }
                }
                line.erase(0,1);
            }

            anotherLine = false;
            // get the next line, if it exists add a new line character
            // if not exit the loop.
            if (getline(fileToEncrypt, line))
            {
                anotherLine = true;
            }
            if (anotherLine)
            {
                letterToEncrypt = '\n';
                for (int i = 0; i < size; i++)
                {
                    currentCode = huffmanCodes->at(i);
                    if (currentCode->letter == letterToEncrypt)
                    {
                        output = output + currentCode->code;
                        i = size;
                    }
                }
            }
        } while((anotherLine));
    }
    return output;
}

// prints the optimal huffman code for the given frequencies of each letter
void HuffmanCompression::printOptimalHuffmanCodeAndCompressionRate(LetterFrequency* letterFrequencies)
{
    BuildFinalHuffmanNode();
    HuffmanCodeVector* huffmanCodes = finalHuffmanNode->getHuffmanCodes();
    finalHuffmanNode->sortHuffmanCodeVectorAlphabetical(huffmanCodes);
    HuffmanCode* currentHuffmanCode;
    int size = huffmanCodes->size();

    // print huffman codes
    for (int i = 0; i < size; i++)
    {
        currentHuffmanCode = huffmanCodes->at(i);

        if (currentHuffmanCode->letter == '\n')
        {
            cout << setw(3) << "\\n" << setw(15) << currentHuffmanCode->code << endl;
        }
        else
        {
            cout << setw(3) << currentHuffmanCode->letter << setw(15) << currentHuffmanCode->code << endl;
        }
    }

    //print compression rate
    double compressionBits = 0;
    double noCompressionBytes = 0;
    int letterFrequency;

    for (int i = 0; i < size; i++)
    {
        currentHuffmanCode = huffmanCodes->at(i);
        letterFrequency = letterFrequencies->getLetterFrequency(currentHuffmanCode->letter);
        noCompressionBytes += letterFrequency;
        compressionBits += letterFrequency * currentHuffmanCode->code.length();
    }

    // compression rate = noCompression bits divided by compression,
    // here it is multiplied by 8 because the nocompression is in bytes,
    // and there are 8 bits in a single byte.
    double compressionRate = (noCompressionBytes/compressionBits) * 8;

    cout << "The compression ratio is: " << fixed << setprecision(2) << compressionRate << endl;


}

// returns a pointer to the final huffman node
HuffmanNode* HuffmanCompression::getFinalHuffmanNode()
{
    return this->finalHuffmanNode;
}

#endif
