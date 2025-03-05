#include<iostream>
#include "Tree.h"
#include<fstream>
#include<cmath>
using namespace std;
/*
     author: jay williamson
     date: 2/21/2025
     this si the main it just gets input and does stuff to the tree
 */
int* getFileNums()
{
  char* input = new char[20];

        cout << "What file name \n";

	//gets a file name
	//cin.ignore();
        cin.getline(input, 20);

	cout << input;
	
	//gets the file you asked for
        ifstream inputFile(input);

	//this is a holder for the numbers being taken out of the file to be added after
        int* nums = new int[1000];
	//gets the current index nums
        int currentIndex = 0;
	//gets the current index in the current number array
        int currentNumberIndex = 0;
	//the numbers in the current number it is reading
        int currentNumber[4];
	//this is a holder for the final number read out
        int finalNumber = 0;
	//this is the amount of places in the number
        int amountOfPlaces = 0;
	//place holder for the char being read
        char currentChar;

	for(int i = 0; i < 1000; i++)
	  {
	    nums[i] = -1;
	  }
	
        while (inputFile.get(currentChar)) 
        {
	//checks if it should start calculating the number it just read
            if (currentChar == ' ') 
            {
		//this starts adding up the current number
                for (int i = 0; i < amountOfPlaces; i++) 
                {
		//adds it by multiplying it by the place it is in and the number
                    finalNumber += currentNumber[i] * pow(10, amountOfPlaces - 1 - i);
		//resets the number
                    currentNumber[i] = -1;
                }

		//resets all the variables
                amountOfPlaces = 0;
                nums[currentIndex] = finalNumber;
                finalNumber = 0;
                currentIndex++;
                currentNumberIndex = 0;
            } //skips end line characters in case there is one
            else if (currentChar != '\n') 
            {
		//adds the current number to the array and goes to the next
                currentNumber[currentNumberIndex] = (int)currentChar - 48;
                amountOfPlaces++;
                currentNumberIndex++;
            }
	}
	
	return nums;
}

int main()
{
  Tree* tree = new Tree();
   int* numbers = getFileNums();

  int currentNum = numbers[0];
  int index = 0;

  cout << currentNum;
  //adds all the numbers
  while(currentNum != -1)
   {
     tree->add(currentNum, tree->root);
      index++;
      currentNum = numbers[index];
    }

  cout << endl << endl;

 tree->print();
 cout << endl << endl;
 tree->print();
  /*  int input = 0;
  cout << "1 for input from console or 2 from file\n";
  cin >> input;


  //makes new tree
  Tree* tree= new Tree();
  if(input == 2)
    {
      //gets the numbers as an array
  int* numbers = getFileNums();

  int currentNum = numbers[0];
  int index = 0;

  //adds ass the numbers
  while(currentNum != -1)
    {
      tree->add(currentNum, tree->root);
      index++;
      currentNum = numbers[index];
    }

  cout << endl << endl;
  
 tree->print();
    }

  //gets input
  cout << "-1 to quit, -2 to print, -3 to delete, -4 for find, -5 for input number \n";
  cin >> input;
  while(input != -1)
    {
      if(input == -2)
	{
	  tree->print();
	}
      else if(input == -3)
	{
	  int toDelete;
	  cout << "what do you want to delete\n";
	  cin >> toDelete;
	  tree->remove(nullptr, tree->root, toDelete);
        }
      else if(input == -4)
	{
	  int toFind;
          cout << "what do you want to find\n";
          cin >> toFind;
          if(tree->search(tree->root, toFind))
	    {
	      cout << "found: " << toFind << endl;
	    }
	  else
	    {
	      cout << "not found" << endl;
	    }
	}
      else if(input == -5)
	{
	  int toInput;
          cout << "what do you want to input\n";
          cin >> toInput;
          tree->add(toInput, tree->root);
	}
      cout << "-1 to quit, -2 to print, -3 to delete, -4 for find, -5 for input number \n";
      cin >> input;
      }*/
}
