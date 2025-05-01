#include <iostream>
#include "Fraction.h"


	Fraction::Fraction() : num{ 0 }, den{ 1 } {};

	Fraction::Fraction(int num_, int den_) : num{ num_ }, den{ den_ } {};

	//Getters
	int Fraction::getNum() const
	{
		return num;
	}
	int Fraction::getDen() const
	{
		return den;
	}

	//Setters
	void Fraction::setNumerator(int n)
	{
		num = n;
	}
	void Fraction::setDenominator(int d) // Throws exception if d == 0
	{
		if (d == 0)
			throw std::invalid_argument("Denominator cannot be zero");
		den = d;
	}

	void Fraction::simplify()
	{
		if (den == 0)
			throw std::invalid_argument("Denominator cannot be zero");
		int a = { num };
		int b = { den };
		while (b != 0)
		{
			int temp = b;
			b = a % b;
			a = temp;
		}
		int gcd = a;
		num /= gcd;
		den /= gcd;
	}

