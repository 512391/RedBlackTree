#include<iostream>
#include<cmath>
#include"Tree.h"

using namespace std;

/*
  author: jay williamson
  date: 2/21/2025
  this just has all the stuff the tree can do 
 */

//adds recursively
void Tree::add(int i, BinaryNode* node)
{
  //checks if the root is null and adds it as root if it is
  if(Tree::root == nullptr)
    {
      Tree::root = new BinaryNode(i);
      Tree::root->setColor('B');
      return;
    }

  BinaryNode* newNode = nullptr;
  
  //tries to recursive it by go left or right
  if(node->getData() > i)
    {
      if(node->getLeft() != nullptr)
	{
	  Tree::add(i, node->getLeft());
	}
      else//adds if null
	{
	  newNode = new BinaryNode(i);
	  node->setLeft(newNode);
	}
    }
  else//same as above just for right
    {
      if(node->getRight() != nullptr)
        {
          Tree::add(i, node->getRight());
        }
      else
        {
          newNode = new BinaryNode(i);
          node->setRight(newNode);
        }
    }
 
  if(node->getColor() == 'R')
    {
      cout << "fixing" << endl;
      addFix(newNode);
    }
  root->setColor('B');
  print();
  cout << endl << endl;
}

void Tree::addFix(BinaryNode* node)
{
  print();
  BinaryNode* uncle = nullptr;
  BinaryNode* nextFix = node->getParent();

  cout << "Node fixing: " << node->getData() << endl;
  
  if(nextFix == nullptr || nextFix->getParent() == nullptr || nextFix->getColor() != 'R')
    {
      return;
    }

  bool uncleIsLeft = false;
  
  if(node->getParent()->getParent()->getLeft() == node->getParent())
        {
          uncle = node->getParent()->getParent()->getRight();
        }
  else if(node->getParent()->getParent()->getRight() != nullptr)
        {
          uncle = node->getParent()->getParent()->getLeft();
	  uncleIsLeft=true;
        }
  char uncColor = 'A';

  if(uncle == nullptr || uncle->getColor() == 'B')
    {
      uncColor = 'B';
    }
  else
    {
      uncColor = 'R';
    }
  
  cout << "got uncle: " << uncle << endl;
  if(uncleIsLeft)
        {
	  if(uncColor == 'R')
	    {
	      if(uncle != nullptr)
		{
		 uncle->setColor('B');
		}
		 node->getParent()->setColor('B');
                 node->getParent()->getParent()->setColor('R');
		 node = node->getParent();
	    }
	  else
	    {
	      if(node == node->getParent()->getLeft())
		{
		  cout << "rotating left" << endl;
		  node=node->getParent();
		  nextFix = node->getParent();
		  rightRotate(node->getParent());
		}
	      node->getParent()->setColor('B');
             node->getParent()->getParent()->setColor('R');
	     leftRotate(node->getParent()->getParent());
	    }

	  
        }
       else
        {
          if(uncColor == 'R')
            {
	       if(uncle != nullptr)
                {
                 uncle->setColor('B');
		}
                 node->getParent()->setColor('B');
                 node->getParent()->getParent()->setColor('R');
                 nextFix = node->getParent()->getParent();
            }
          else
            {
              if(node == node->getParent()->getLeft())
                {
                  node=node->getParent();
                  nextFix = node->getParent();
                  leftRotate(node->getParent());
                }
              node->getParent()->setColor('B');
             node->getParent()->getParent()->setColor('R');
	     print();
             rightRotate(node->getParent()->getParent());
	     print();
            }
        }
  cout << "at next fix" << endl;
  addFix(nextFix);
  
}

//searches recursively
bool Tree::search(BinaryNode* node, int i)
{
  //checks if the node if null 
  if(node == nullptr)
    {
      //prins false as it did not find it where it should have been
      cout << "null" << endl;
      return false;
    }

  cout << "data: " << node->getData() << endl;

  //checks if it found it
  if(node->getData() == i)
    {
      return true;
    }

  //does recursion based on where it needs to go
  if(node->getData() < i)
    {
      Tree::search(node->getRight(), i);
    }
  else
    {
      Tree::search(node->getLeft(), i);
    }
}

//gets the successor
BinaryNode* Tree::getSuccesor(BinaryNode* node)
{
  //starts on right noe
  BinaryNode* currentNode = node->getRight();
  cout << "starting node: " << currentNode->getData() << endl;
  
  if(currentNode == nullptr)
    {
      currentNode = node->getLeft();
    }
  //goes left until it hits the end
  while(currentNode->getLeft() != nullptr)
    {
      currentNode = currentNode->getLeft();
      cout << "current node: " << currentNode->getData() << endl;
    }

  return currentNode;
}

//recursibely gets the parent of a node
BinaryNode* Tree::getParent(BinaryNode* node, int i)
{
  //if null it did not find the parent
  if(node == nullptr)
    {
      cout << "null" << endl;
      return nullptr;
    }

  cout << "data: " << node->getData() << endl;

  //checks if children are it if so return the parent
  if(node->getLeft() != nullptr)
    {
      if(node->getLeft()->getData() == i)
      {
        return node;
      }
    }
  if(node->getRight() != nullptr)
    {
      if(node->getRight()->getData() == i)
      {
        return node;
      }
    }

  //keep going recursively
  if(node->getData() < i)
    {
      Tree::getParent(node->getRight(), i);
    }
  else
    {
      Tree::getParent(node->getLeft(), i);
    }
}

//removes a node recrsivley
BinaryNode* Tree::remove(BinaryNode* nodeParent, BinaryNode* node, int i)
{
  //its null if it got to the end or the root is null
  if(Tree::root == nullptr || node == nullptr)
    {
      return nullptr;
    }

  cout << "Current number: " << node->getData() << endl;
  
  if(node->getData() == i)
    {
      cout << "removing something: " << i << endl;
      
      BinaryNode* toReturn  = new BinaryNode(node->getData());
      //checks if root
      if(nodeParent == nullptr)
	{
	  //checks if it has both childen
	  if(node->getLeft() != nullptr && node->getRight() != nullptr)
	    {
	      //set right as root
	  BinaryNode* left = Tree::root->getLeft();
	  Tree::root = Tree::root->getRight();
	  Tree::root->setLeft(left);
	    }//just set root if only one child
	  else if(node->getLeft() != nullptr)
	    {
	    Tree:root = node->getLeft();
	    }
	  else if(node->getRight() != nullptr)
	    {
	      Tree::root = node->getRight();
	    }
	  else
	    {
	      Tree::root = nullptr;
	    }
	}//checks if has both children
      else if(node->getLeft() != nullptr && node->getRight() != nullptr)
	{
	  //get the successor and parent
	  BinaryNode* success = getSuccesor(node);
	  BinaryNode* parent  = getParent(Tree::root, success->getData());
	  cout << "Parent: " << parent->getData() << endl;
	  //set success parets children
	  if(parent != node)
            {
              parent->setLeft(success->getRight());
            }
	  //sets the success into new spot
	  if(nodeParent->getRight() == node)
	    {
	      nodeParent->setRight(success);
	    }
	  else
	    {
	      nodeParent->setLeft(success);
	    }
	  //gives successor new children
	  if(node->getLeft() != success)
	    {
	      success->setLeft(node->getLeft());
	    }
	  else
	    {
	      success->setLeft(nullptr);
	    }
	  if(node->getRight() != success)
            {
	      success->setRight(node->getRight());
	    }
	  else
	    {
	      success->setLeft(nullptr);
	    }
	}//checks if only has right child
      else if(node->getRight() != nullptr)
	{
	  //remove correct node and replaces with only child
	  if(nodeParent->getRight() == node)
            {
              nodeParent->setRight(node->getRight());
            }
          else
            {
              nodeParent->setLeft(node->getRight());
            }
	}//same as right but left
     else if(node->getLeft() != nullptr)
        {
	  if(nodeParent->getRight() == node)
            {
              nodeParent->setRight(node->getLeft());
            }
          else
            {
              nodeParent->setLeft(node->getLeft());
            }
        }
     else //if no children just set as null
	{
	  if(nodeParent->getRight() == node)
            {
              nodeParent->setRight(nullptr);
            }
          else
            {
              nodeParent->setLeft(nullptr);
            }
	}
      
      delete node;
      return toReturn;
    }

  //moves down recursively if nt found
  if(node->getData() < i)
    {
      Tree::remove(node, node->getRight(), i);
    }
  else
    {
      Tree::remove(node, node->getLeft(), i);
    }
}

//gets the height
int Tree::findHeight(BinaryNode* node)
{
  if(node == nullptr)
    {
      return -1;
    }
  
  //gets it recursively
  int left = findHeight(node->getLeft());
  int right = findHeight(node->getRight());
 
  return max(left, right)+1;
}

//prints the right amount of spaces for length of number
void Tree::printCorrectSpaces(int num)
{
  int digits = 0;

  //-1 means just spaces
  if(num == -1 || num == 0)
    {
      cout << ' ';
    }
  else
    {//prints for each missing digit in max spaces
  while(num != 0)
    {
      num = num/10;

      digits++;
    }
    }
  
  int spaces = AMOUNT_OF_SPACES-digits-1;

  for(int i = 0; i < spaces; i++)
    {
      cout << ' ';
    }
}

//makes the tree as a 2d array
void Tree::make2dTree(BinaryNode*** finalNodes, BinaryNode** nodes, int arrSize, int height, int currHeight, int lineSize, int prevSideIndent)
{
  //checks if at end
  if(height == currHeight)
    {
      bool shouldPrint = true;
      //just print every other if at end
      for(int i = 0; i < lineSize/2; i++)
        {
          if(shouldPrint)
            {
              if(nodes[i/2] != nullptr)
                {
                  finalNodes[i][currHeight] = nodes[i/2];
                }
              else
                {
                  finalNodes[i][currHeight] = nullptr;
                }
              shouldPrint = false;
            }
          else
            {
              shouldPrint = true;
            }
	}
      return;
    }

  //gets the indentation for the sides of the tree and the middle seperations betwee the numbers in this line
  int midIndent = prevSideIndent;
  int sideIndent = floor(prevSideIndent/2);

  //array for next nodes in line
  BinaryNode** newNodeArray = new BinaryNode*[arrSize*2];

  for(int i = 0; i < arrSize*2; i++)
    {
      newNodeArray[i] = nullptr;
    }
  
  int newNodeArrayIndex = 0;
  int finalNodesIndex = 0;

  //makes side indent
  for(int i = 0; i < sideIndent; i++)
    {
      finalNodesIndex++;
    }

  //goes through each mid indents size then places a number
  for(int i = 0; i < arrSize; i++)
    {
      if(nodes[i] != nullptr)
        {
          finalNodes[finalNodesIndex][currHeight] = nodes[i];
	  finalNodesIndex++;
      	  for(int i = 0; i < midIndent; i++)
	    {
	      finalNodesIndex++;
	    }
	  
          if(nodes[i]->getLeft() != nullptr)
            {
              newNodeArray[newNodeArrayIndex] = nodes[i]->getLeft();
            }
          newNodeArrayIndex++;
          if(nodes[i]->getRight() != nullptr)
            {
              newNodeArray[newNodeArrayIndex] = nodes[i]->getRight();
            }
          newNodeArrayIndex++;
        }
      else
        {
          finalNodes[finalNodesIndex][currHeight] = nodes[i];
	  finalNodesIndex++;
          for(int i = 0; i < midIndent; i++)
            {
              finalNodesIndex++;
            }

          newNodeArrayIndex += 2;
        }
    }

  delete[] nodes;
  cout << "Level: " << currHeight << endl;

  for(int i  = 0; i < arrSize*2; i++)
    {
      if(newNodeArray[i] != nullptr)
	{
	  cout << newNodeArray[i]->getData() << endl;
	}
    }
  //goes recursively
  make2dTree(finalNodes, newNodeArray, arrSize*2, height, currHeight+1, lineSize, sideIndent);
}

void Tree::leftRotate(BinaryNode* axis)
{
  
}

void Tree::rightRotate(BinaryNode* axis)
{
  
}


//actually prints the tree
void Tree::print()
{
  BinaryNode** rootArr = new BinaryNode*[1];
  rootArr[0] = Tree::root;
  cout << "finding height" << endl;
  //gets the sizes of the width and height
  int height = findHeight(Tree::root)+2;
  int lineSize = pow(2,height)-1;
  int topDownSize = pow(2,height);
  cout << "found sized" << endl;
  //makes array of nodes for 2d array
  BinaryNode*** finalNodes = new BinaryNode**[topDownSize];
  for(int i = 0; i < topDownSize; i++)
    {
      finalNodes[i] = new BinaryNode*[height];
      for(int j = 0; j < height; j++)
	{
	  finalNodes[i][j] = nullptr;
	}
    }
  cout << "making tree" << endl;
  //makes array
  make2dTree(finalNodes, rootArr, 1, height, 1, lineSize, floor(lineSize/2));

  int* indicies = new int[2];

  //trims the fat off the sides of the array
  trimPrintArray(topDownSize, height, finalNodes, indicies);
  cout << "made tree" << endl;
  //prints and does diffrent depending on if condensed or not
  for(int i = indicies[0]; i <= indicies[1]; i++)
    {
      bool isEmpty = true;
      for(int j = 0; j < height; j++)
        {
	  if(finalNodes[i][j] != nullptr)
	    {
	      isEmpty = false;
	    }
	}

      if(!isEmpty || !Tree::PRINT_CONDENSED)
	{
	  for(int j = 0; j < height; j++)
	    {
	      if(finalNodes[i][j] == nullptr)
		{
		  printCorrectSpaces(-1);
		}
	      else
		{
	      
		  cout << finalNodes[i][j]->getData()<<finalNodes[i][j]->getColor();
		  printCorrectSpaces(finalNodes[i][j]->getData());
		}
	    }	
	  cout << endl;
	}
    }
   
  delete[] finalNodes;
}

//trims the array to print
void Tree::trimPrintArray(int width, int height, BinaryNode*** nodes, int* bottomTopIndicies)
{
  int lastIndex = 0;
  int firstIndex = 0;
  bool lookingForFirst = true;
  //gets first and last index of actual info and returns them
   for(int i = 0; i < width; i++)
    {
      for(int j = 0; j < height; j++)
        {
          if(nodes[i][j] != nullptr)
            {
	      if(lookingForFirst)
		{
		  firstIndex = i;
		  lookingForFirst = false;
		}
	      lastIndex = i;
            }
        }
    }

   bottomTopIndicies[0] = firstIndex;
   bottomTopIndicies[1] = lastIndex;
}
