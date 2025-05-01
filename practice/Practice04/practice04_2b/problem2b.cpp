#include <iostream>
#include <string>

template <typename T>
T findMax(T a, T b, T c)
{
	T max = (a < b) ? b : a;
	max = (max < c) ? c : max;
	return max;
}

int main()
{
	while (true)
	{
		std::cout << "\nWould you like to compare integers(1), or strings(2)? Anything else to stop." << std::endl;
		int choice{};
		std::cin >> choice;
		if (choice == 1)
		{
			std::cout << "\nPlease input 3 integers." << std::endl;
			int x{};
			int y{};
			int z{};
			std::cin >> x >> y >> z;
			int max = findMax(x, y, z);
			std::cout << "The maximum is: " << max << std::endl;
		}
		else if (choice == 2)
		{
			std::cout << "\nPlease input 3 strings." << std::endl;
			std::string x{};
			std::string y{};
			std::string z{};
			std::cin >> x >> y >> z;
			std::string max = findMax(x, y, z);
			std::cout << "The maximum is: " << max << std::endl;
		}
		else
		{
			std::cout << "Quitting..." << std::endl;
			break;
		}
	}
	

	return 0;
}