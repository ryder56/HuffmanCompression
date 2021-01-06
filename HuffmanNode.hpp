//********************************************************************
// ASU CSE310 Honors Project
// Name of Author: Ryder Roth
// Description: This is the huffman Node class where aeach huffman node stores
//              a small huffman tree, and the leaf nodes of that tree store
//              the character. It also contains the huffman code struct,
//              which stores a letter and the huffman code for the letter.
//********************************************************************
#ifndef HUFFMAN_NODE_HPP
#define HUFFMAN_NODE_HPP

#include <vector>
#include <iostream>

using namespace std;

struct HuffmanCode{
    string code;
    char letter;
};

typedef vector<HuffmanCode*> HuffmanCodeVector;

class HuffmanNode
{
    private:
        HuffmanNode* leftChild;
        HuffmanNode* rightChild;
        HuffmanNode* parent;
        int frequency;
        char letter;

        bool isLeafNode(HuffmanNode* nodeToCheck);
        void findHuffmanCodes(HuffmanNode* currentNode, HuffmanCodeVector* vectorToAddTo);
        void swap(int index1, int index2, HuffmanCodeVector* vector);
        int partition(int lowIndex, int highIndex, HuffmanCodeVector* vector);
        void quickSortHelper(int lowIndex, int highIndex, HuffmanCodeVector* vector);
    
    public:
        HuffmanNode();
        ~HuffmanNode();
        void setFrequency(int frequency);
        void setLetter(char letter);
        void setLeftChild(HuffmanNode* leftChild);
        void setRightChild(HuffmanNode* rightChild);
        void setParent(HuffmanNode* parent);
        string getCode(HuffmanNode* huffmanNode);
        int getFrequency();
        char getLetter();
        HuffmanNode* getLeftChild();
        HuffmanNode* getRightChild();
        HuffmanNode* getParent();
        HuffmanCodeVector* getHuffmanCodes();
        void sortHuffmanCodeVectorAlphabetical(HuffmanCodeVector* vectorToSort);
        bool operator<(HuffmanNode& rhs);
        bool operator>(HuffmanNode& rhs);
        bool operator==(HuffmanNode& rhs);
        bool operator<=(HuffmanNode& rhs);
        bool operator>=(HuffmanNode& rhs);
};

// constructor for huffman node class
HuffmanNode::HuffmanNode()
{
    this->leftChild = NULL;
    this->rightChild = NULL;
    this->parent = NULL;
    this->frequency = 0;
    this->letter = '\0';
}

// destructor for huffmanNode class
HuffmanNode::~HuffmanNode()
{
    if (this->leftChild != NULL)
    {
        delete this->leftChild;
    }
    if (this->rightChild != NULL)
    {
        delete this->rightChild;
    }
}

// set the frequency for the huffman node
void HuffmanNode::setFrequency(int frequency)
{
    this->frequency = frequency;
}

// sets the letter the huffman node represents 
void HuffmanNode::setLetter(char letter)
{
    this->letter = letter;
}

// sets the left child for the huffman node
void HuffmanNode::setLeftChild(HuffmanNode* leftChild)
{
    this->leftChild = leftChild;
}

// sets the right child for the huffman node
void HuffmanNode::setRightChild(HuffmanNode* rightChild)
{
    this->rightChild = rightChild;
}

// sets the parent for the hufmman node
void HuffmanNode::setParent(HuffmanNode* parent)
{
    this->parent = parent;
}

// gets the frequency of the huffman node
int HuffmanNode::getFrequency()
{
    return this->frequency;
}

// gets the letter of the huffman node
char HuffmanNode::getLetter()
{
    return this->letter;
}

// gets the left child of the huffman node
HuffmanNode* HuffmanNode::getLeftChild()
{
    return this->leftChild;
}

// gets the right child of the huffman node
HuffmanNode* HuffmanNode::getRightChild()
{
    return this->rightChild;
}

// gets the parent of the huffman node
HuffmanNode* HuffmanNode::getParent()
{
    return this->parent;
}

// returns true if the node is a leaf
// node
bool HuffmanNode::isLeafNode(HuffmanNode* nodeToCheck)
{
    if (nodeToCheck->getLeftChild() == NULL && nodeToCheck->getRightChild() == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

// gets the huffman code for a given node
string HuffmanNode::getCode(HuffmanNode* huffmanNode)
{
    if (!isLeafNode(huffmanNode))
    {
        return "ERROR NOT A LEAF NODE, NO VALID CODE";
    }
    else
    {
        HuffmanNode* currentNode = huffmanNode;
        HuffmanNode* currentParent = currentNode->getParent();
        string huffmanCode = "";

        while (currentParent != NULL)
        {
            if (currentParent->getLeftChild() != NULL && currentParent->getLeftChild() == currentNode)
            {
                huffmanCode = "0" + huffmanCode;
            }
            else
            {
                huffmanCode = "1" + huffmanCode;
            }

            currentNode = currentParent;
            currentParent = currentNode->getParent();
        }
        return huffmanCode;
    }  
}
//TODO: go ahead and switch this to return a binary heap of a new object class that is called huffman codes and has comparable based on the character aka a first,...

// gets the huffmanCodes for each leaf node and adds it to the vector
void HuffmanNode::findHuffmanCodes(HuffmanNode* currentNode, HuffmanCodeVector* vectorToAddTo)
{
    if (isLeafNode(currentNode))
    {
        HuffmanCode* huffmanCodeToInsert = new HuffmanCode();
        huffmanCodeToInsert->code = currentNode->getCode(currentNode);
        huffmanCodeToInsert->letter = currentNode->getLetter();
        vectorToAddTo->insert(vectorToAddTo->end(), huffmanCodeToInsert); //insert at end
    }
    else 
    {
        if (currentNode->getLeftChild() != NULL)
        {
            findHuffmanCodes(currentNode->getLeftChild(), vectorToAddTo);
        }
        if (currentNode->getRightChild() != NULL)
        {
            findHuffmanCodes(currentNode->getRightChild(), vectorToAddTo);
        }
    }
}

//returns an array for the huffman codes of each letter in the tree
HuffmanCodeVector* HuffmanNode::getHuffmanCodes()
{
    HuffmanCodeVector* huffmanCodes = new HuffmanCodeVector();
    findHuffmanCodes(this, huffmanCodes);
    return huffmanCodes;
}

// ovverrides the < operator to compare huffman nodes
// based on frequency
bool HuffmanNode::operator<(HuffmanNode& rhs)
{
    if (this->frequency < rhs.frequency)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// overrides the > operator to compare huffman nodes
// based on frequency
bool HuffmanNode::operator>(HuffmanNode& rhs)
{
    if (this->frequency > rhs.frequency)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

// overrides the == operator to compare huffman nodes
// based on frequency
bool HuffmanNode::operator==(HuffmanNode& rhs)
{
    if (this->frequency == rhs.frequency)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// overrides the <= operator to compare huffman nodes
// based on frequency
bool HuffmanNode::operator<=(HuffmanNode& rhs)
{
    if (this->frequency <= rhs.frequency)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// overrides the >= operator to compare huffman nodes
// based on frequency
bool HuffmanNode::operator>=(HuffmanNode& rhs)
{
    if (this->frequency >= rhs.frequency)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

// sorts a huffman code vector into alphabetical order using quicksort
void HuffmanNode::sortHuffmanCodeVectorAlphabetical(HuffmanCodeVector* vectorToSort)
{
    int size = vectorToSort->size();
    quickSortHelper(0, size - 1, vectorToSort);
}

// swaps Huffman nodes at two indexes
void HuffmanNode::swap(int index1, int index2, HuffmanCodeVector* vector)
{
    HuffmanCode* temp = vector->at(index1);
    vector->at(index1) = vector->at(index2);
    vector->at(index2) = temp;
}

// partition algorithm for quicksort
int HuffmanNode::partition(int lowIndex, int highIndex, HuffmanCodeVector* vector)
{
    swap(lowIndex, highIndex, vector);

    int pivot = highIndex;
    int storeIndex = lowIndex;
    char char1, char2;
    
    for (int i = lowIndex; i <= highIndex; i++)
    {
        char1 = vector->at(i)->letter;
        char2 = vector->at(pivot)->letter;

        if (char1 < char2)
        {
            swap(i, storeIndex, vector);
            storeIndex++;
        }
    }

    swap(storeIndex, pivot, vector);
    pivot = storeIndex;
    return pivot;
}

// helper method to recursively call partition
void HuffmanNode::quickSortHelper(int lowIndex, int highIndex, HuffmanCodeVector* vector)
{
    int pivot = partition(lowIndex, highIndex, vector);
    
    if (pivot - 1 > lowIndex)
    {
        quickSortHelper(lowIndex, pivot-1, vector);
    }
    if (pivot + 1 < highIndex)
    {
        quickSortHelper(pivot + 1, highIndex, vector);
    }
}



#endif


