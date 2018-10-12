//Name: Jesse Rapoport
//Date: 5/31/2018
//Class: Karla Fant's CS163 Class, Spring 2018
//Assignment: Program #4, where we add/remove concepts into a binary search tree

#include "header.h"

int main()
{
    tree myTree; //tree everything is happening in
    int userInput; //the user input of which function to execute

    loadFileIntoTree(FILENAME, myTree); //load the file into myTree

    giveInstructions(); //give the instructions of what the program is

    do
    {
        giveUserFunctionOptions(); //tell the user the options
        getUserInput(userInput); //get the user's choice
        doRequestedFunction(userInput, myTree); //do the requested choice
    }
    while(userInput != EXITNUMBER); //do this on loop until the user wants to exit
}
