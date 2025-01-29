#include <iostream>
#include <vector>
#include <limits>

int intValidator() //prevent bad input for the numbers
{
	int x{};
	std::cin >> x;
	while (!std::cin)
	{
		std::cout << "Invalid input.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> x;
	}
	return x;
}

void addToVector(std::vector<int>& numVector)
{
	std::cout << "What number would you like to add to the vector? " << std::endl;
	int toVector = intValidator();
	numVector.push_back(toVector);
	std::cout << "Number added. \n" << std::endl;
}

void printVector(const std::vector<int>& numVector)
{
	std::cout << "Printing vector: \n" << std::endl;
	for (int i{}; i < numVector.size(); i++)
	{
		std::cout << numVector.at(i) << std::endl;
	}
	std::cout << "\nCompleted. \n" << std::endl;
}

void doubleVector(std::vector<int>& numVector)
{
	std::cout << "Doubling elements... \n" << std::endl;
	for (int i{}; i < numVector.size(); i++)
	{
		numVector.at(i) *= 2;
	}
	std::cout << "Done. \n" << std::endl;
}

void sumVector(const std::vector<int>& numVector)
{
	int vectorSum{};
	for (int i{}; i < numVector.size(); i++)
	{
		vectorSum += numVector.at(i);
	}
	std::cout << "The sum of the numbers is: " << vectorSum << "\n" << std::endl;
}

void findMultiples(const std::vector<int>& numVector)
{
	std::cout << "What number would you like to check for multiples of?" << std::endl;
	int multiplesBase = intValidator();
	std::cout << "The multiples present in this vector are: ";
	for (int i{}; i < numVector.size(); i++)
	{
		if (numVector.at(i) % multiplesBase == 0)
		{
			std::cout << " " << numVector.at(i) << " ";
		}
	}
	std::cout << "\n\n";
}

int main()
{
	std::vector <int> numVector{2, 10, 17, 33}; //random starting values to give some numbers to manipulate
	std::cout << "Welcome." << std::endl;
	while (true)
	{
		std::cout << "-- What action would you like to take? --\n"
			<< "1: Add a number to the vector. \n"
			<< "2: Print the contents of the vector. \n"
			<< "3: Double the contents of the vector. \n"
			<< "4: Find the sum of the items in the vector. \n"
			<< "5: Print vector elements which are a multiple of a number. \n"
			<< "6+: Exit the program. \n" << std::endl;
		int userChoice = intValidator();
		switch (userChoice)
		{
		case 1:
			addToVector(numVector);
			break;
		case 2:
			printVector(numVector);
			break;
		case 3:
			doubleVector(numVector);
			break;
		case 4: 
			sumVector(numVector);
			break;
		case 5:
			findMultiples(numVector);
			break;
		case 6:
			std::cout << "Exiting." << std::endl;
			return 0;
		default:
			std::cout << "Exiting." << std::endl;
			return 0;
		}
		
	}
	
	return 0;
}
