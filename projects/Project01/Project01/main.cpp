#include <iostream>
#include <limits>
#include <vector>

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

void printRules()
{
	std::cout << "OTHELLO/n"
		<< "-----------------------------------------------------\n"
		<< "Rules: Players must take turns moving their pieces each round,";
}


int main()
{

	return 0;
}