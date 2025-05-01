#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <numeric>

int intInputValid()
{
	int num{};
	while (true)
	{
		std::cin >> num;
		if (std::cin.fail())
		{
			std::cout << "Invalid. ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		break;
	}
	return num;
}

void populateVector(std::vector<int>& vec)
{
	std::cout << "Please input 5 numbers to be stored." << std::endl;
	int userInput{};
	for (int i{ 0 }; i < 5; i++)
	{
		std::cout << "Enter #" << i + 1 << ": ";
		userInput = intInputValid();
		vec.push_back(userInput);
	}
}

void vectorPrint(const std::vector<int>& vec)
{
	for (auto i{ vec.begin() }; i != vec.end(); i++)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}

void elementsSquared(std::vector <int>& vec)
{
	auto squared
	{
		[](int& i) 
		{
			return i *= i;
		}
	};
	std::cout << "The elements squared: ";
	std::for_each(vec.begin(), vec.end(), squared);
	vectorPrint(vec);
	std::cout << std::endl; 

	std::cout << "The sum: " << std::accumulate(vec.begin(), vec.end(), 0);
	std::cout << std::endl;
}

int vecSum(std::vector<int>& vec)
{
	return std::accumulate(vec.begin(), vec.end(), 0);
}

int main()
{
	std::vector<int> userVec{};
	populateVector(userVec);
	
	elementsSquared(userVec);
	std::cout << std::endl;

	return 0;
}