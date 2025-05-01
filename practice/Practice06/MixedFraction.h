#pragma once
#include "Fraction.h"

class MixedFraction : public Fraction
{
private:
	int whole{};
public:
	MixedFraction();
	MixedFraction(int whole, int n, int d);
	MixedFraction(const Fraction& fraction);

	friend std::ostream& operator<<(std::ostream& out, const MixedFraction& frac);
};