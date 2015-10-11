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
std::vector<std::vector<unsigned long>> Pascal_triangle;
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
		int* size_ptr = &SetSize;
		//Create thread to start computing triangle
		FillTrianglehandle = CreateThread(0, 0, FillTriangle, size_ptr, 0, &FillTrianglethreadid);

		//Choose size
		std::cout << "Enter the number to choose from that set: ";
		std::cin >> SetChoose;

	//perform calculation
		WaitForSingleObject(FillTrianglehandle, INFINITE);
	//Output results
		//print the triangle if possible
		if (SetSize <= 20)
		{
			std::cout << std::endl << "The triangle resulting from the input of " << SetSize << " is:" << std::endl << std::endl;

			std::cout << "Interpritation: row is the set size, and the column is the number chosen (starting at Zero(0))" << std::endl;

			int row = 0;
			for (auto r : Pascal_triangle) //cycle through each row
			{
				std::cout << "[" << row << "]\t";
				for (auto c : r) //cycle through each column in that row
				{
					std::cout << c << "\t";
				}
				std::cout << std::endl;
				row++;
			}
		}
		else
		{
			std::cout << "Printing a triangle that size would make it unreadable, please use a set smaller than 20 for triangle output." << std::endl;
		}
		//out put the answer to the question

		std::cout << std::endl << "The number of distict choices you can have when picking " << SetChoose << " from " << SetSize << " is :" << std::endl;
		std::cout << (Pascal_triangle[Pascal_triangle.size() - 1])[SetChoose] << std::endl; //select the part that we want from the vector
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FillTriangle thread
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI FillTriangle(LPVOID sRow)
{
	int rows = *static_cast<int *>(sRow);
	if (rows <= 0)
	{
		return 1;
	}
	
	std::vector<unsigned long> preRow; // create a reuseable vector for the previous row
	//fill row 1
	preRow.push_back((unsigned long)1);
	Pascal_triangle.push_back(preRow);


	int count = 0; //count for while loop
	unsigned int numIdx;//column number index; must be positive

	for (count = 1; count <= rows; count++)
	{
		//create a vector for this row and put the first '1' in the row
		std::vector<unsigned long> curRow;
		curRow.push_back((unsigned long)1);//put first '1' into the line

		//fill the rest of the numbers
		for (numIdx = 0; numIdx < preRow.size() - 1; numIdx++)
		{
			curRow.push_back(preRow[numIdx] + preRow[numIdx + 1]);
			//fill the middle numbers
		}

		//finalization for next row
		curRow.push_back((unsigned long)1);//put the last number in


		
		Pascal_triangle.push_back(curRow);//push the latest row to the triangle
		preRow = curRow;//update the previous row to the current one for the next iteration
	}

	return 1;
}