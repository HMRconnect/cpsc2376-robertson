#include <iostream>
#include "Fraction.h"
#include "MixedFraction.h"

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

//overloads
Fraction operator+(const Fraction& lhs, const Fraction& rhs)
{
	int num1 = lhs.num * rhs.den;
	int num2 = rhs.num * lhs.den;
	int denTotal = lhs.den * rhs.den;
	int numTotal= num1 + num2;
	Fraction totalFrac{ numTotal, denTotal };
	totalFrac.simplify();
	return totalFrac;

}

Fraction operator-(const Fraction& lhs, const Fraction& rhs)
{
	int num1 = lhs.num * rhs.den;
	int num2 = rhs.num * lhs.den;
	int denTotal = lhs.den * rhs.den;
	int numTotal = num1 - num2;
	Fraction totalFrac{ numTotal, denTotal };
	totalFrac.simplify();
	return totalFrac;
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs)
{
	int numProd = lhs.num * rhs.num;
	int denProd = lhs.den * rhs.den;
	return { numProd, denProd };
}

Fraction operator/(const Fraction& lhs, const Fraction& rhs) // Throws exception if division by zero occurs
{
	if (rhs.num == 0)
		throw std::invalid_argument("No dividing by 0!");
	int numProd = lhs.num * rhs.den;
	int denProd = lhs.den * rhs.num;
	return { numProd, denProd };
}

std::ostream& operator<<(std::ostream& out, const Fraction& frac)
{
	out << frac.num << "/" << frac.den;
	return out;
}



std::ostream& operator<<(std::ostream& out, const MixedFraction& mixedFrac)
{
	if (mixedFrac.num == 0)
	{
		out << mixedFrac.whole;
		return out;
	}
	out << mixedFrac.whole << " " << mixedFrac.num << "/" << mixedFrac.den;
	return out;
}

Fraction enterFraction()
{
	Fraction fraction{};
	std::cout << "Enter the numerator: ";
	int num = intInputValid();
	fraction.setNumerator(num);
	std::cout << "Enter the denominator: ";
	int den = intInputValid();
	while (den == 0)
	{
		std::cout << "invalid denominator." << std::endl;
		int den = intInputValid();
	}
	fraction.setDenominator(den);
	std::cout << "Fraction set." << std::endl;
	return fraction;
}

int main()
{
	Fraction currentFraction{};
	
	while (true)
	{
		std::cout << "\nCurrent Fraction: " << currentFraction << std::endl;
		std::cout << "\nOptions:\n"
			<< "1. Enter a fraction manually\n"
			<< "2. Add a fraction to the current\n"
			<< "3. Subtract a fraction from the current\n"
			<< "4. Multiply the current by a fraction\n"
			<< "5. Divide the current by a fraction\n"
			<< "6. Display the current as a mixed fraction\n"
			<< "7. Clear the fraction\n"
			<< "8. Quit\n" << std::endl;
		std::cout << "Choice: ";
		int choice = intInputValid();
		
		switch (choice)
		{
		case 1 :
			currentFraction = enterFraction();
			break;
		case 2:
			currentFraction = currentFraction + enterFraction();
			break;
		case 3:
			currentFraction = currentFraction - enterFraction();
			break;
		case 4:
			currentFraction = currentFraction * enterFraction();
			break;
		case 5:
			currentFraction = currentFraction / enterFraction();
			break;
		case 6:
			{
			MixedFraction mixedFraction{ currentFraction };
			std::cout << mixedFraction << std::endl;
			}
			break;
		case 7:
			currentFraction.setNumerator(0);
			currentFraction.setDenominator(1);
			break;
		case 8:
			return 0;
		default:
			return 0;
		}

	}

	return 0;
}