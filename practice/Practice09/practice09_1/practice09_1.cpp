#include <iostream>


int main()
{
	float redPotion{ 0.0f };    // Amount of red potion in mL
	float bluePotion{ 0.0f };   // Amount of blue potion in mL
	float* flask{ nullptr };

	while (true)
	{
		std::cout << "\nThe red potion contains " << redPotion << " mL."
			<< "The blue potion contains " << bluePotion << " mL." << std::endl;
		std::cout << "\nAdd liquid to the red or blue potion? Type done to end." << std::endl;
		std::string choice{};
		std::cin >> choice;
		if (choice == "red" or choice == "Red")
		{
			flask = &redPotion;
			std::cout << "Add how many mL? ";
			int addedVolume{};
			std::cin >> addedVolume;
			*flask += addedVolume;
		}
		else if (choice == "blue" or choice == "Blue" )
		{
			flask = &bluePotion;
			std::cout << "Add how many mL? ";
			int addedVolume{};
			std::cin >> addedVolume;
			*flask += addedVolume;
		}
		else if (choice == "done" or choice == "Done")
		{
			break;
		}
		else
		{
			std::cout << "Invalid option." << std::endl;
			continue;
		}
	}
	return 0;
}