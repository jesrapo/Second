//Name: Jesse Rapoport
//Date: 5/31/2018
//Class: Karla Fant's CS163 Class, Spring 2018
//Assignment: Program #4, where we add/remove concepts into a binary search tree

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

const int EXITNUMBER = 8;
const int SIZE = 1000;
const char FILENAME[13] = "CS_Terms.txt";

struct concept
{
    char * term;
    char * definition;
    char * reference;
    char * citation;
};

struct node
{
    concept data;
    node * left;
    node * right;
};

class tree
{
    public:
        tree();
        ~tree();
        void insert(concept & someConcept);
        void display(void);
        int findHeight(void);
        void displayTreeShape(void);
        bool remove(const char termBeingRemoved[]);
        bool removeAllConceptsWithSource(const char sourceName[]);
        bool retrieve(const char termBeingRetrieved[], concept & receivedConcept);
    private:
        void displayTreeRow(node * & root, int & currentLevel, int levelToPrint);
        void displayUnwrapped(node * & root);
        void addNodeUnwrapped(node * & root, concept & someConcept);
        void defineLeaf(node * & root, concept & someConcept);
        void deallocateTree(void);
        void deallocateTreeUnwrapped(node * & root);
        void deallocateNode(node * & current);
        void findHeightUnwrapped(node * & root, int & currentLevel, int & biggestHeight);
        void deleteNode(node * & parentNode, node * & childNode, bool & leftOrRight);
        int findHowManyChildren(node * & currentNode);
        void deleteLeaf(node * & parentNode, node * & childNode, bool & leftOrRight);
        void deleteOneChildNode(node * & parentNode, node * & childNode, bool & leftOrRight);
        void deleteTwoChildNode(node * & parentNode, node * & childNode, bool & leftOrRight);
        bool findNodeAndParent(const char termBeingRemoved[], node * & parentNode, node * & childNode, bool & leftOrRight);
        void findNode(const char termBeingRemoved[], node * & currentNode, node * & parentNode, node * & childNode, bool & leftOrRight, bool & wasNodeFound);
        void getDataFromRelevantDescendant(node * & childNode, concept & tempConcept);
        void replaceNodeConcept(node * & childNode, concept & tempConcept);
        void getDataFromFurthestLeftDescendant(node * & parentNode, node * & childNode, concept & tempConcept, bool & isItFirst);
        void removeAllConceptsWithSourceUnwrapped(const char sourceName[]);
        void findNodeWithSource(const char sourceBeingRemoved[], node * & currentNode, node * & parentNode, node * & childNode, bool & leftOrRight, bool & wasNodeFound);
        void findNodeWithoutParent(const char termBeingRemoved[], node * & currentNode, node * & childNode, bool & wasNodeFound);
        int findHeight(node * & root);
        node * root;
};

void makeDynamicString(char * & emptyString, const char stringContents[]);
void copyConcept(concept & emptyConcept, concept & contentConcept);
void copyDynamicString(char * & emptyString, char * & fullString);
void loadFileIntoTree(const char fileName[], tree & aTree);
void addConceptToTree(ifstream & fileIn, tree & aTree);
void getConceptFromFile(ifstream & fileIn, concept & aConcept);
void deallocateConcept(concept & conceptBeingDeallocated);
void giveInstructions(void);
void giveUserFunctionOptions(void);
void getUserInput(int & userInput);
void doRequestedFunction(const int userInput, tree & myTree);
void addConcept(tree & myTree);
void removeConcept(tree & myTree);
void removeSource(tree & myTree);
void retrieveInfo(tree & myTree);
void displayAlphabetically(tree & myTree);
void displayTree(tree & myTree);
void seeHeight(tree & myTree);
void thankUser();
void getDataFromUser(const char nameOfData[], char * & dataArray);
void displayConcept(const concept & retrievedConcept);
