#include<iostream>
#include<vector>
#include "BinaryNode.h"

/*
  auhor: jay williamson
  date: 2/21/2025
  this is the .h fr the tree just has all the functionality change the constants for what you want
 */

class Tree
{
 private:
  //This is th aount of spaces that a umber takes up no matter it size so up this if you are using bigger numbers
  const int AMOUNT_OF_SPACES = 5;
  //when this is true it prints it in a condensed way no spaces in between less readable but smaller when it is false it prints it spread out so change it based on what u want
  const bool PRINT_CONDENSED = true;
  //gets the successor
  BinaryNode* getSuccesor(BinaryNode* node);
  //gets the parent of a node
  BinaryNode* getParent(BinaryNode* node, int i);
  int findHeight(BinaryNode* node);
  //this makes a 2d array with all the spaces and numbers
  void make2dTree(BinaryNode*** finalNodes, BinaryNode** currentNodes, int arrSize, int height, int currHeight, int lineSize, int prevSideIndent);
  //this prints the correct amount of spaces so all numbers take the same amount of space
  void printCorrectSpaces(int num);
  //this trims the top and bottom of the array so it is not too unruly when uncondensed
  void trimPrintArray(int width, int height, BinaryNode*** nodes, int* bottomTopIndicies);
  //fixing violations after adding
  void addFix(BinaryNode* node);
  //recolors after insertion
  void addRecolor(BinaryNode* node);
 public:
  //root
  BinaryNode* root;
  //this adds a numbers into the tree
  void add(int i, BinaryNode* node);
  //this tells you whether something is in the tree or not
  bool search(BinaryNode* node, int i);
  //this removes something from the tree
  BinaryNode* remove(BinaryNode* nodeParent, BinaryNode* node, int i);
  //this prints the tree
  void print();
  //rotations for red blac
  void leftRotate(BinaryNode* axis);
  void rightRotate(BinaryNode* axis);

};
