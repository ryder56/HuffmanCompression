//********************************************************************
// ASU CSE310 Honors Project
// Name of Author: Ryder Roth
// Description: This is the driver for the HuffmanCompression Class
//              it creates a letter frequency object to get the 
//              letter frequency of the file given by the user,
//              then feeds that information into a huffman compression
//              object and prints out the huffman compression and the
//              compression rate for that file, and then gives the option
//              to output the compression into a string or into a file
//              (will not give the option for a string into console
//              for large files to prevent crashes).
//********************************************************************
#include "HuffmanCompression.hpp"

void getFileName(string &fileName);


int main(int argc, char** argv)
{
    HuffmanCompression* compression;
    LetterFrequency* frequency;
    string fileName;
    string line;
    int size;
    bool validInput = false;
    char option;

    //get file name
    do{
        getFileName(fileName);
        ifstream test(fileName);
        if (test)
        {
            validInput = true;
        }
        if (!validInput)
        {
            cout << "\n Please enter a valid file Name" << endl;
        }
    } while(!validInput);
    
    // setup file and variables
    ifstream stream(fileName);
    frequency = new LetterFrequency(stream);
    size = frequency->getSize();
    compression = new HuffmanCompression(size);

    // insert frequencies into compression algorithm
    for (int i = 0; i < size; i++)
    {
        compression->InsertNode(frequency->getLetterAt(i), frequency->getFrequencyAt(i));
    }
    
    //print compression
    compression->printOptimalHuffmanCodeAndCompressionRate(frequency);

    //additional options below
    //------------------------
    cout << "Would you like to write the encryption to a file? (y/n)";
    do{
        cin >> line;
        option = line.at(0);
        if (option != 'y' && option != 'n')
        {
            cout << "Invalid entry!, try again" << endl;
        }
    } while (option != 'y' && option != 'n');

    if (option == 'y')
    {
        ifstream inFile(fileName);
        ofstream outFile("compression.txt");
        compression->EncryptAndWriteToFile(inFile, outFile);
    }

    //only do output into console for not huge strings, otherwise it will crash
    if (frequency->getCurrentCharacters() < 1000)
    {
        cout << "Would you like to print the encryption as a string?" << endl;
        do{
            cin >> line;
            option = line.at(0);

            if (option != 'y' && option != 'n')
            {
                cout << "Invalid entry!, try again" << endl;
            }
        } while (option != 'y' && option != 'n');

        if (option == 'y')
        {
            ifstream newStream(fileName);
            cout << compression->EncryptFile(newStream) << endl;
        }
    }
    
}

void getFileName(string &fileName)
{
    cout << "Enter the name of the file" << endl;
    cin >> fileName;
}