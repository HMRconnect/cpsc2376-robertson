#include <iostream>
#include <vector>
#include <limits>

int intValid()
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
	int userInput{};
	for (int i{ 0 }; i < 5; i++)
	{
		std::cout << "Enter #" << i + 1 << ": ";
		userInput = intValid();
		vec.push_back(userInput);
	}
}

void reversePrint(const std::vector<int>& vec)
{
	for (auto i{ vec.rbegin() }; i != vec.rend() ; i++)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}

int main()
{
	std::vector<int> userVec{};
	std::cout << "Please input 5 numbers to be stored." << std::endl;
	populateVector(userVec);
	std::cout << "The numbers in reverse order: ";
	reversePrint(userVec);

	return 0;
}