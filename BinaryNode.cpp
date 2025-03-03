#include<iostream>
#include"BinaryNode.h"

BinaryNode::BinaryNode(int i)
{
  //sets data in constructot
  BinaryNode::data = i;
  BinaryNode::color = 'R';
  BinaryNode::left = nullptr;
  BinaryNode::right = nullptr;
  BinaryNode::parent = nullptr;
}
void BinaryNode::setData(int i)
{
  //sets the data
  BinaryNode::data = i;
}
int BinaryNode::getData()
{
  //returns the data
  return BinaryNode::data;
}
char BinaryNode::getColor()
{
  return BinaryNode::color;
}
void BinaryNode::setColor(char color)
{
  BinaryNode::color = color;
}
void BinaryNode::setLeft(BinaryNode* node)
{
  //sets the left
  BinaryNode::left = node;
  BinaryNode::left->setParent(this);
}
void BinaryNode::setRight(BinaryNode* node)
{
  //sets the right
  BinaryNode::right = node;
  BinaryNode::right->setParent(this);
}
BinaryNode* BinaryNode::getRight()
{
  //gets the right
  return BinaryNode::right;
}
BinaryNode* BinaryNode::getLeft()
{
  //gets the left
  return BinaryNode::left;
}

BinaryNode* BinaryNode::getParent()
{
  return BinaryNode::parent;
}

void BinaryNode::setParent(BinaryNode* node)
{
  BinaryNode::parent = node;
}
