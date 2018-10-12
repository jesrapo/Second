//Name: Jesse Rapoport
//Date: 5/31/2018
//Class: Karla Fant's CS163 Class, Spring 2018
//Assignment: Program #4, where we add/remove concepts into a binary search tree

#include "header.h"

//take a statically allocated string and make it dynamically allocated of the appropriate size
void makeDynamicString(char * & emptyString, const char stringContents[])
{
    int length = strlen(stringContents);
    emptyString = new char[length + 1];
    strcpy(emptyString, stringContents);
}

//copy a dynamically allocated string into another one
void copyDynamicString(char * & emptyString, char * & fullString)
{
    int length = strlen(fullString);
    emptyString = new char[length + 1];
    strcpy(emptyString, fullString);
}

//copy a concept into another concept
void copyConcept(concept & emptyConcept, concept & contentConcept)
{
    copyDynamicString(emptyConcept.term, contentConcept.term);
    copyDynamicString(emptyConcept.definition, contentConcept.definition);
    copyDynamicString(emptyConcept.reference, contentConcept.reference);
    copyDynamicString(emptyConcept.citation, contentConcept.citation);
}

//load an external data file into a tree
void loadFileIntoTree(const char fileName[], tree & aTree)
{
    //open the file
    ifstream fileIn;
    fileIn.open(fileName);

    //if the file doesn't exist
    if(!fileIn)
        cout << "The file " << fileName << " was not found." << endl;

    //get the data from the file if it exists
    else
    {
        //I don't know why, but without this the root seemed to have a weird invisible character at the front
        fileIn.ignore(3, '\n');

        //add concepts to the table until it runs out
        while(!fileIn.eof())
            addConceptToTree(fileIn, aTree);
    }

    //close the file
    fileIn.close();
}

//gets a concept from the file, and adds it to the tree
void addConceptToTree(ifstream & fileIn, tree & aTree)
{
    concept aConcept;

    getConceptFromFile(fileIn, aConcept); //get a concept from the file
    aTree.insert(aConcept); //add the file to the table
    deallocateConcept(aConcept); //delete the copy of the concept from out here
}

//gets the next concept from the file
//runs assuming there is a next concept
void getConceptFromFile(ifstream & fileIn, concept & aConcept)
{
    char temp[SIZE];

    //get the term
    fileIn.get(temp, SIZE, '|');
    fileIn.ignore();
    makeDynamicString(aConcept.term, temp);

    //get the definition
    fileIn.get(temp, SIZE, '|');
    fileIn.ignore();
    makeDynamicString(aConcept.definition, temp);

    //get the reference information
    fileIn.get(temp, SIZE, '|');
    fileIn.ignore();
    makeDynamicString(aConcept.reference, temp);

    //get the citation
    fileIn.get(temp, SIZE, '\n');
    fileIn.ignore();
    makeDynamicString(aConcept.citation, temp);
}

//deallocate a concept's contents
void deallocateConcept(concept & conceptBeingDeallocated)
{
    delete conceptBeingDeallocated.term;
    delete conceptBeingDeallocated.definition;
    delete conceptBeingDeallocated.reference;
    delete conceptBeingDeallocated.citation;
}

//give the user instructions
void giveInstructions(void)
{
    cout << endl;
    cout << "Welcome to the program where you can" << endl;
    cout << "add and remove concepts about computer" << endl;
    cout << "science. Here are all the options: " << endl;
}

//tell the user the options for functions to execute
void giveUserFunctionOptions(void)
{
    cout << endl;
    cout << "To add a new concept, press 1." << endl;
    cout << "To remove a concept, press 2." << endl;
    cout << "To remove all concepts of a specific source, press 3." << endl;
    cout << "To learn all information about a specific term, press 4." << endl;
    cout << "To display all the terms alphabetically, press 5." << endl;
    cout << "To display all the terms in a tree format, press 6." << endl;
    cout << "To learn the height of that tree format, press 7." << endl;
    cout << "To exit, press 8." << endl;
    cout << endl;
}

//get the user's input
void getUserInput(int & userInput)
{
    cout << "Please enter your choice here: ";

    cin >> userInput;
    cin.ignore(SIZE, '\n');

    //if invalid input, recursively call the function again
    if(userInput < 1 || userInput > EXITNUMBER)
    {
        cout << "Error. ";
        getUserInput(userInput);
    }
    cout << endl;
}


//do the requested function
void doRequestedFunction(const int userInput, tree & myTree)
{
    switch(userInput)
    {
        case 1:
            addConcept(myTree);
            break;
        case 2:
            removeConcept(myTree);
            break;
        case 3: 
            removeSource(myTree);
            break;
        case 4: 
            retrieveInfo(myTree);
            break;
        case 5:
            displayAlphabetically(myTree);
            break;
        case 6:
            displayTree(myTree);
            break;
        case 7:
            seeHeight(myTree);
            break;
        case 8:
            thankUser();
    }
}

//use the insert method to add a new concept from the user
void addConcept(tree & myTree)
{
    concept newConcept;

    cout << "Time to add a new concept. Please provide the following information:" << endl << endl;

    //get the concept from the user
    getDataFromUser("term", newConcept.term);
    getDataFromUser("definition", newConcept.definition);
    getDataFromUser("reference", newConcept.reference);
    getDataFromUser("citation", newConcept.citation);

    //add the new concept to into the tree
    myTree.insert(newConcept);

    //deallocate the concept out here, just leaving the one inside the tree
    deallocateConcept(newConcept);

    cout << "Your data has been entered successfully!" << endl;
}

//use the remove method to remove a term the user chooses
void removeConcept(tree & myTree)
{
    bool didItWork;
    char termBeingRemoved[SIZE];

    //get the name of the term being removed
    cout << "Please enter the term being removed: ";
    cin.get(termBeingRemoved, SIZE, '\n');
    cin.ignore(SIZE, '\n');

    //try to remove that term
    didItWork = myTree.remove(termBeingRemoved);

    //tell the user whether or not it worked
    if(didItWork)
        cout << endl << termBeingRemoved << " was successfully removed." << endl;
    else
        cout << endl << "Sorry, but no term with the name " << termBeingRemoved << " was found." << endl;
}

//use the removeSource method to remove all data from a specific source chosen by the user
void removeSource(tree & myTree)
{
    bool didItWork;
    char sourceName[SIZE];

    //give the instructions
    cout << "Please enter the name of the source whose terms you'd like removed: ";

    //get the name of the source to be removed
    cin.get(sourceName, SIZE, '\n');

    //try to remove all sources of that concept, and check if it worked
    didItWork = myTree.removeAllConceptsWithSource(sourceName);

    //if it worked, tell the user
    if(didItWork)
        cout << endl << "All sources of name " << sourceName << " successfully removed!" << endl;

    //otherwise, tell the user it didn't work
    else
        cout << endl << "Error. There are no sources of the name " << sourceName << "." << endl;
}

//display the information about a specific term as chosen by the user
void retrieveInfo(tree & myTree)
{
    bool didItWork;
    char termBeingRetrieved[SIZE];
    concept retrievedConcept;

    //get the name of the term being retrieved
    cout << "Please enter the term you'd like to read about: ";
    cin.get(termBeingRetrieved, SIZE, '\n');
    cin.ignore(SIZE, '\n');

    //try to retrieve that term
    didItWork = myTree.retrieve(termBeingRetrieved, retrievedConcept);

    //if it didn't work, tell the user
    if(!didItWork)
        cout << endl << "Sorry, but no term with the name " << termBeingRetrieved << " was found." << endl;

    //if it did work, display all the information about the term
    else
        displayConcept(retrievedConcept);
}

//display all of the terms alphabetically
void displayAlphabetically(tree & myTree)
{
    cout << "Here is the tree displayed alphabetically: " << endl << endl;
    myTree.display();
}

//display the tree in its actual form
void displayTree(tree & myTree)
{
    cout << "Here is the data in tree-format: " << endl << endl;
    myTree.displayTreeShape();
}

//tell the user what the height of the tree is
void seeHeight(tree & myTree)
{
    int height = myTree.findHeight();
    cout << "The height is " << height << "." << endl;
}

//thank the user for using the program
void thankUser()
{
    cout << "Thanks for using the program!" << endl << endl;
}

//get information from the user
void getDataFromUser(const char nameOfData[], char * & dataArray)
{
    char dataTemp[SIZE];

    //get user's data into statically allocated array
    cout << "Please enter the " << nameOfData << ": ";
    cin.get(dataTemp, SIZE, '\n');
    cin.ignore(SIZE, '\n');

    //turn that statically allocated array into a dynamically allocated arrat
    makeDynamicString(dataArray, dataTemp);
}

//display a concept
void displayConcept(const concept & retrievedConcept)
{
    cout << endl << "Here is information about " << retrievedConcept.term << ":" << endl;
    cout << endl;
    cout << "Definition: " << retrievedConcept.definition << endl;
    cout << "Reference: " << retrievedConcept.reference << endl;
    cout << "Citation: " << retrievedConcept.citation << endl;
}

