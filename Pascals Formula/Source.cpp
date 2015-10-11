//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Gary Muller
// Fall 2015
// MA 225 Assignment 4
//
// Copyright 2015 Gary Muller
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Use the theorem of Pascals Triangle to solve N choose R/K problems
//ask the user to input a size of the set and the number to choose
//output the result of the calculation
//NOTE ***due to the includes this program will only compile on windows***
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Header files - Standard libraries and classes
#ifndef CORE_DEPENDENCIES_H_
#include <iostream> //default include for functionality
#include <string> //get working string functionality
#include <iomanip> //included to make pretty output
#include <vector> //use vector functionality
#include <Windows.h>//windows threads
#endif


//Global variables and defines
std::vector<std::vector<int>> Pascal_triangle;
//

//Function Prototypes
DWORD WINAPI FillTriangle(LPVOID);
//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//Main Declaration
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	// Create variables 
	int SetSize;
	int SetChoose;

	HANDLE FillTrianglehandle;
	DWORD FillTrianglethreadid;

	//query user for input
		//Set size
		std::cout << "Enter the size of the set: ";
		std::cin >> SetSize;

		//Create thread to start computing triangle
		FillTrianglehandle = CreateThread(0, 0, FillTriangle, &SetSize, 0, &FillTrianglethreadid);

		//Choose size
		std::cout << "Enter the number to choose from that set: ";
		std::cin >> SetChoose;

	//perform calculation
		WaitForSingleObject(FillTrianglehandle, INFINITE);
	//Output results
		
		std::cout << std::endl << "The triangle resulting from the input of " << SetSize << " is:" << std::endl << std::endl;

		//print the triangle
		for ( auto r : Pascal_triangle) //cycle through each row
		{
			for (auto c : r) //cycle through each column in that row
			{
				std::cout << c << "\t";
			}
			std::cout << std::endl;
		}

		//out put the answer to the question

		std::cout << std::endl << "The number of distict choices you can have when picking " << SetChoose << " from " << SetSize << "is :" << std::endl;
		std::cout << (Pascal_triangle[Pascal_triangle.size() - 1])[SetChoose - 1]; //select the part that we want from the vector
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FillTriangle Declaration
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI FillTriangle(LPVOID row)
{
	int rows = (int)row;
	if (rows <= 0)
	{
		return 1;
	}
	
	std::vector<int> row1; // create a reuseable vector for current row
	//fill row 1
	row1.push_back(1);
	Pascal_triangle.push_back(row1);


	int count = 0; //count for while loop
	unsigned int rowNum = 2;//start at two because rows one and two were manually filled; must be positive
	unsigned int numIdx;//column number index; must be positive

	for (count = 2; count <= rows; count++)
	{
		std::vector<int> curRow;
		curRow.push_back(1);//put first '1' into the line

		for (numIdx = 0; numIdx < ((Pascal_triangle[rowNum]).size() - 1); numIdx++)
		{
			curRow.push_back((Pascal_triangle[rowNum])[numIdx] + (Pascal_triangle[rowNum])[numIdx + 1]);
			//fill the middle numbers
		}


		curRow.push_back(1);//put the last number in
		count++;//increase count
		rowNum++;//increase row
	}

	return 1;
}