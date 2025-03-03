#ifndef BINARY_H
#define BINARYNODE_H

#include<iostream>

class BinaryNode
{
  private:
  int data;
  BinaryNode* left;
  BinaryNode* right;
  BinaryNode* parent;
  char color;
public:
  BinaryNode(int i);
  //sets the data
  void setData(int i);
  //gets the data
  int getData();
  //gets color
  char getColor();
  //sets color
  void setColor(char color);
  //sets the left
  void setLeft(BinaryNode* node);
  //sets the right
  void setRight(BinaryNode* node);
  //gets the left
  BinaryNode* getLeft();
  //gets the right
  BinaryNode* getRight();
  //gets parent
  BinaryNode* getParent();
  //sets parent
  void setParent(BinaryNode* node);
};

#endif
