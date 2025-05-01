#include <iostream>
#include "MixedFraction.h"


	MixedFraction::MixedFraction() {};
	MixedFraction::MixedFraction(int whole, int n, int d) : whole{ whole }, Fraction{ n,d } {};
	MixedFraction::MixedFraction(const Fraction& fraction)
		: whole{ fraction.num / fraction.den }, Fraction{ (fraction.num % fraction.den), fraction.den } {};

	
