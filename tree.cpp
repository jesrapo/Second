//Name: Jesse Rapoport
//Date: 5/31/2018
//Class: Karla Fant's CS163 Class, Spring 2018
//Assignment: Program #4, where we add/remove concepts into a binary search tree

#include "header.h" 

//constructor for tree
tree::tree()
{
    root = NULL;
}

//destructor for tree
tree::~tree()
{
    //deallocate all the nodes and their contents
    deallocateTree();
}

//deallocate a tree wrapper function
void tree::deallocateTree(void)
{
    deallocateTreeUnwrapped(root);
}

//deallocate a tree recursive function
void tree::deallocateTreeUnwrapped(node * & root)
{
    //traverse till you reach a leaf
    if(root->left)
        deallocateTreeUnwrapped(root->left);
    if(root->right)
        deallocateTreeUnwrapped(root->right);

    //then delete that leaf, over and over, till the whole tree's gone
    deallocateNode(root);
}

//insert into a tree
void tree::insert(concept & someConcept)
{
    addNodeUnwrapped(root, someConcept);
}

//defines a leaf
void tree::defineLeaf(node * & root, concept & someConcept)
{
    root = new node;
    copyConcept(root->data, someConcept);
    root->left = NULL;
    root->right = NULL;
}

//adds a node recursively
void tree::addNodeUnwrapped(node * & root, concept & someConcept)
{
    int isNewConceptBigger;

    //if there's a node here, figure out if the new term is bigger or smaller than it alphabetically
    if(root)
        isNewConceptBigger = strcmp(root->data.term, someConcept.term);

    //if this is the first node in the tree, make this the root
    if(!root)
        defineLeaf(root, someConcept);

    //if this number's smaller than or equal to the root
    else if(isNewConceptBigger >= 0)
    {
        //if there is already a node to the left, traverse left
        if(root->left)
            addNodeUnwrapped(root->left, someConcept);

        //if there is nothing to the left, add the node there as a leaf
        else
            defineLeaf(root->left, someConcept);
    }

    //if this number's bigger than the root
    else if(isNewConceptBigger < 0)
    {
        //if there is already a node to the right, traverse right
        if(root->right)
            addNodeUnwrapped(root->right, someConcept);

        //if there is nothing to the right, add the node there as a leaf
        else
            defineLeaf(root->right, someConcept);
    }
}

//wrapper function for the display recursive function
void tree::display()
{
    displayUnwrapped(root);
}

//display, using in-order traversal
void tree::displayUnwrapped(node * & root)
{
    if(!root)
        return;

    if(root->left)
        displayUnwrapped(root->left);
        
    cout << root->data.term << endl;

    if(root->right)
        displayUnwrapped(root->right);
}

//deallocate a node and all its contents
void tree::deallocateNode(node * & current)
{
    deallocateConcept(current->data);
    delete current;
}

//display a tree shape
void tree::displayTreeShape(void)
{
    int currentLevel = 0;
    int totalHeight = findHeight();
    cout << endl;
    for(int i = 1; i <= totalHeight; ++i)
    {
        cout << "Level " << i << ": ";
        displayTreeRow(root, currentLevel, i);
        cout << endl << endl; //line breaks in between rows
    }
}

//displays a tree row, assuming a row at the level given exists
void tree::displayTreeRow(node * & root, int & currentLevel, int levelToPrint)
{
    if(!root)
        return;

    //update the level (row)  we're at
    ++currentLevel;

    //print the node if we're at the desired level
    if(currentLevel == levelToPrint)
        cout << root->data.term << ", ";

    //if this isn't the row desired yet, keep traversing downward
    else
    {
        if(root->left)
            displayTreeRow(root->left, currentLevel, levelToPrint);

        if(root->right)
            displayTreeRow(root->right, currentLevel, levelToPrint);
    }

    //bring the level back when you go back up
    --currentLevel;
}

int tree::findHeight()
{
    int height = 0;
    int currentLevel = 0;
    findHeightUnwrapped(root, currentLevel, height);
    return height;
}

void tree::findHeightUnwrapped(node * & root, int & currentLevel, int & biggestHeight)
{
    //if the whole tree is empty
    if(!root)
        return;

    //add 1 to the current level
    ++currentLevel;

    //traverse left if you can
    if(root->left)
        findHeightUnwrapped(root->left, currentLevel, biggestHeight);

    //traverse right if you can
    if(root->right)
        findHeightUnwrapped(root->right, currentLevel, biggestHeight);

    //if this is the biggest height found so far, record it
    if(currentLevel > biggestHeight)
        biggestHeight = currentLevel;

    //put the current level back as you go back up
    --currentLevel;
}

bool tree::remove(const char termBeingRemoved[])
{
    bool doesNodeExist;
    node * parentNode;
    node * childNode;
    bool leftOrRight;

    //find out whether the node exists, and find the parent of it at the same time
    doesNodeExist = findNodeAndParent(termBeingRemoved, parentNode, childNode, leftOrRight);

    //if the term doesn't exist, return false
    if(!doesNodeExist)
        return false;

    //otherwise, delete that node and return true
    deleteNode(parentNode, childNode, leftOrRight);
    return true;
}

void tree::deleteNode(node * & parentNode, node * & childNode, bool & leftOrRight)
{
    int howManyChildren = findHowManyChildren(childNode);

    if(howManyChildren == 0)
        deleteLeaf(parentNode, childNode, leftOrRight);
    if(howManyChildren == 1)
        deleteOneChildNode(parentNode, childNode, leftOrRight);
    if(howManyChildren == 2)
        deleteTwoChildNode(parentNode, childNode, leftOrRight);
}

int tree::findHowManyChildren(node * & currentNode)
{
    if(currentNode->left && currentNode->right)
        return 2;
    else if (!currentNode->left && !currentNode->right)
        return 0;
    else
        return 1;
}

void tree::deleteLeaf(node * & parentNode, node * & childNode, bool & leftOrRight)
{

    //delete the child
    deallocateNode(childNode);

    //if this is the root, set it to NULL
    if(!parentNode)
        root = NULL;
    
    //if it's not the root, set the parent's appropriate child to NULL
    else
    {
        //set the appropriate child of the parent node to NULL
        if(leftOrRight == 0)
            parentNode->left = NULL;
        else
            parentNode->right = NULL;
    }
}

void tree::deleteOneChildNode(node * & parentNode, node * & childNode, bool & leftOrRight)
{
    node * childsChild;

    //figure out if the child's child is left or right
    if(childNode->left)
        childsChild = childNode->left;
    else
        childsChild = childNode->right;

    //delete the node being deleted
    deallocateNode(childNode);

    //if this is the root, delete it and set it to the root's child
    if(!parentNode)
        root = childsChild;

    //if this isn't the root, set the parent's left or right child to the grandchild
    else
    {
        //set the parent's left or right child to the new child accordingly
        if(leftOrRight == 0)
            parentNode->left = childsChild;
        else
            parentNode->right = childsChild;
    }
}

void tree::deleteTwoChildNode(node * & parentNode, node * & childNode, bool & leftOrRight)
{
    concept tempConcept;

    getDataFromRelevantDescendant(childNode, tempConcept);

    replaceNodeConcept(childNode, tempConcept);
}

//go to the furthest left descendant in the node's right subtree, and get the data there and bring it back, also deleting the leaf
void tree::getDataFromRelevantDescendant(node * & childNode, concept & tempConcept)
{
    bool isItFirst = true; //this will be the first run at the beginning
    getDataFromFurthestLeftDescendant(childNode, childNode->right, tempConcept, isItFirst);
}

//get the data from the furthest left descendant of a node
void tree::getDataFromFurthestLeftDescendant(node * & parentNode, node * & childNode, concept & tempConcept, bool & isItFirst)
{
    //if we haven't reached the furthest left, keep traversing
    if(childNode->left)
    {
        isItFirst = false; //now, if a node is reached it won't be the first one
        getDataFromFurthestLeftDescendant(childNode, childNode->left, tempConcept, isItFirst);
    }

    //if we have reached the furthest left, get the concept and delete the leaf and go back up with the concept
    else
    {
        //get a copy of the concept here to bring back up
        copyConcept(tempConcept, childNode->data);


        //deallocate this leaf
        deallocateNode(childNode);

        //if this is the top descendant, then the child is the parent's right child
        if(isItFirst)
            parentNode->right = NULL;

        //otherwise it's the parent's left child
        else
            parentNode->left = NULL;
    }
}

//replace the concept of the node with that of the descendant's data
void tree::replaceNodeConcept(node * & childNode, concept & tempConcept)
{
    //delete the current data
    deallocateConcept(childNode->data);

    //replace it with the one from the deleted descendant
    copyConcept(childNode->data, tempConcept);

    //delete the temp concept used to transport it
    deallocateConcept(tempConcept);
}

//find a node and its parent (wrapper function)
bool tree::findNodeAndParent(const char termBeingRemoved[], node * & parentNode, node * & childNode, bool & leftOrRight)
{
    bool wasNodeFound = 0; //set to 0 unless found otherwise
    int isThisTheOne; 
    node * currentNode = root;

    findNode(termBeingRemoved, currentNode, parentNode, childNode, leftOrRight, wasNodeFound);

    if(wasNodeFound == 0)
        return false;
    else
        return true;
}

//find a node given the name
void tree::findNode(const char termBeingRemoved[], node * & currentNode, node * & parentNode, node * & childNode, bool & leftOrRight, bool & wasNodeFound)
{
    int isLeftTheOne = 1;
    int isRightTheOne = 1;
    int isCurrentTheOne = 1; //only possible if root is the one

    //traverse back up to root if the node was found
    if(wasNodeFound)
        return;

    //this will only occur if this is the root, otherwise the current one will never be matching
    isCurrentTheOne = strcmp(termBeingRemoved, currentNode->data.term);

    //if there's a left child, check if it's the term being removed
    if(currentNode->left)
        isLeftTheOne = strcmp(termBeingRemoved, currentNode->left->data.term);

    //if there's a right child, check if it's the term being removed
    if(currentNode->right)
        isRightTheOne = strcmp(termBeingRemoved, currentNode->right->data.term);

    //if the left child is a match, describe the appropriate information and traverse back up
    if(isLeftTheOne == 0)
    {
        parentNode = currentNode;
        childNode = currentNode->left;
        wasNodeFound = 1;
        leftOrRight = 0;
        return;
    }

    //if the right child is a match, describe the appropriate information and traverse back up
    else if(isRightTheOne == 0)
    {
        parentNode = currentNode;
        childNode = currentNode->right;
        wasNodeFound = 1;
        leftOrRight = 1;
        return;
    }

    //if the current one is a match, then this is the root and do the appropriate actions
    else if(isCurrentTheOne == 0)
    {
        parentNode = NULL;
        childNode = currentNode;
        wasNodeFound = 1;
    }

    //if this node is not matching, traverse down
    else
    {
        //if there's a left node, traverse left
        if(currentNode->left)
            findNode(termBeingRemoved, currentNode->left, parentNode, childNode, leftOrRight, wasNodeFound);

        //if there's a right node, traverse right
        if(currentNode->right)
            findNode(termBeingRemoved, currentNode->right, parentNode, childNode, leftOrRight, wasNodeFound);
    }
}

void tree::findNodeWithSource(const char sourceBeingRemoved[], node * & currentNode, node * & parentNode, node * & childNode, bool & leftOrRight, bool & wasNodeFound)
{
    int isLeftTheOne = 1;
    int isRightTheOne = 1;
    int isCurrentTheOne = 1; //only possible if root is the one

    //traverse back up to root if the node was found
    if(wasNodeFound)
        return;

    //this will only occur if this is the root, otherwise the current one will never be matching
    isCurrentTheOne = strcmp(sourceBeingRemoved, currentNode->data.reference);

    //if there's a left child, check if it's the term being removed
    if(currentNode->left)
        isLeftTheOne = strcmp(sourceBeingRemoved, currentNode->left->data.reference);

    //if there's a right child, check if it's the term being removed
    if(currentNode->right)
        isRightTheOne = strcmp(sourceBeingRemoved, currentNode->right->data.reference);

    //if the left child is a match, describe the appropriate information and traverse back up
    if(isLeftTheOne == 0)
    {
        parentNode = currentNode;
        childNode = currentNode->left;
        wasNodeFound = 1;
        leftOrRight = 0;
        return;
    }

    //if the right child is a match, describe the appropriate information and traverse back up
    else if(isRightTheOne == 0)
    {
        parentNode = currentNode;
        childNode = currentNode->right;
        wasNodeFound = 1;
        leftOrRight = 1;
        return;
    }

    //if the current one is a match, then this is the root and do the appropriate actions
    else if(isCurrentTheOne == 0)
    {
        parentNode = NULL;
        childNode = currentNode;
        wasNodeFound = 1;
    }

    //if this node is not matching, traverse down
    else
    {
        //if there's a left node, traverse left
        if(currentNode->left)
            findNodeWithSource(sourceBeingRemoved, currentNode->left, parentNode, childNode, leftOrRight, wasNodeFound);

        //if there's a right node, traverse right
        if(currentNode->right)
            findNodeWithSource(sourceBeingRemoved, currentNode->right, parentNode, childNode, leftOrRight, wasNodeFound);
    }
}

//deletes all nodes that have a specific source, and returns true if successful
bool tree::removeAllConceptsWithSource(const char sourceName[])
{
    bool wasNodeFound = false; //COULD BE WRONG
    bool leftOrRight;
    node * currentNode = root;
    node * parentNode;
    node * childNode;


    //simply check if a node exists with the given source name
    findNodeWithSource(sourceName, currentNode, parentNode, childNode, leftOrRight, wasNodeFound);

    //if it exists, execute the recursive function that will delete all nodes with the source name, and return true
    if(wasNodeFound)
    {
        wasNodeFound = false;
        removeAllConceptsWithSourceUnwrapped(sourceName);
        return true;
    }

    //if there is no node with the given source name, just return false
    else
        return false;
}

void tree::removeAllConceptsWithSourceUnwrapped(const char sourceName[])
{
    bool wasNodeFound = false;
    bool leftOrRight;
    node * currentNode = root;
    node * parentNode;
    node * childNode;

    //on a loop, go through the whole tree looking for nodes with the given source
    do
    {
        //set this to false unless changed by findNodeWithSource()
        wasNodeFound = false; 

        //try to find a node with the source name given
        findNodeWithSource(sourceName, currentNode, parentNode, childNode, leftOrRight, wasNodeFound);

        //if that node exists, delete that node
        if(wasNodeFound)
            deleteNode(parentNode, childNode, leftOrRight);

    }
    while(wasNodeFound);
}

bool tree::retrieve(const char termBeingRetrieved[], concept & receivedConcept)
{
    node * relevantNode;
    bool wasNodeFound;

    //try to find a node with the given term name
    findNodeWithoutParent(termBeingRetrieved, root, relevantNode, wasNodeFound);

    //if there is no node of the given name, return false
    if(!wasNodeFound)
        return false;

    //if there is a node of the given name, copy that node's concept into the received concept, and return true

    copyConcept(receivedConcept, relevantNode->data);
    return true;
}

void tree::findNodeWithoutParent(const char termBeingRemoved[], node * & currentNode, node * & childNode, bool & wasNodeFound)
{
    int isLeftTheOne = 1;
    int isRightTheOne = 1;
    int isCurrentTheOne = 1; //only possible if root is the one

    //traverse back up to root if the node was found
    if(wasNodeFound)
        return;

    //this will only occur if this is the root, otherwise the current one will never be matching
    isCurrentTheOne = strcmp(termBeingRemoved, currentNode->data.term);

    //if there's a left child, check if it's the term being removed
    if(currentNode->left)
        isLeftTheOne = strcmp(termBeingRemoved, currentNode->left->data.term);

    //if there's a right child, check if it's the term being removed
    if(currentNode->right)
        isRightTheOne = strcmp(termBeingRemoved, currentNode->right->data.term);

    //if the left child is a match, describe the appropriate information and traverse back up
    if(isLeftTheOne == 0)
    {
        childNode = currentNode->left;
        wasNodeFound = 1;
        return;
    }

    //if the right child is a match, describe the appropriate information and traverse back up
    else if(isRightTheOne == 0)
    {
        childNode = currentNode->right;
        wasNodeFound = 1;
        return;
    }

    //if the current one is a match, then this is the root and do the appropriate actions
    else if(isCurrentTheOne == 0)
    {
        childNode = currentNode;
        wasNodeFound = 1;
    }

    //if this node is not matching, traverse down
    else
    {
        //if there's a left node, traverse left
        if(currentNode->left)
            findNodeWithoutParent(termBeingRemoved, currentNode->left, childNode, wasNodeFound);

        //if there's a right node, traverse right
        if(currentNode->right)
            findNodeWithoutParent(termBeingRemoved, currentNode->right, childNode,  wasNodeFound);
    }
}
