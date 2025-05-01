#include <iostream>


double convertTemperature(double temp, char scale = 'F')
{
	if (scale == 'F')
	{
		temp = (temp * 1.8) + 32;
		return temp;
	}
	else if (scale == 'C')
	{
		temp = (temp - 32)/1.8;
		return temp;
	}
	else
	{
		std::cout << "error" << std::endl;
		return 1;
	}

}
//RECHANGE BACK TO MAIN BEFORE UPLOAD
int temp()
{
	while (true)
	{
		std::cout << "Choose 1 to convert Celsius to Fahrenheit.\n"
				  << "Choose 2 to convert Fahrenheit to Celsius.\n" 
				  << "Choose 3 to end the program. \n" << std::endl;
		double temperature{};
		int choice{};
		std::cin >> choice;
		if (choice == 1)
		{
			std::cout << "Your choice was 1. Please enter temperature in Celsius: ";
			std::cin >> temperature;
			temperature = convertTemperature(temperature);
			std::cout << "The temperature in Fahrenheit is: " << temperature << std::endl << std::endl;
		}
		else if (choice == 2)
		{
			std::cout << "Your choice was 2. Please enter temperature in Fahrenheit: ";
			std::cin >> temperature;
			temperature = convertTemperature(temperature, 'C');
			std::cout << "The temperature in Celsius is: " << temperature << std::endl << std::endl;
		}
		else if (choice == 3)
		{
			break;
		}
		else
		{
			std::cout << "That was not one of the options.\n" << std::endl;
			continue;
		}
	}
	
	return 0;
}