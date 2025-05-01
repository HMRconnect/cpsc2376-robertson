#pragma once

class Fraction
{
protected:
	int num{};
	int den{};

public:
	Fraction();
	Fraction(int num_, int den_);

	//Getters
	int getNum() const;
	int getDen() const;

	//Setters
	void setNumerator(int n);
	void setDenominator(int d);

	void simplify();

	friend Fraction operator+(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator-(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator*(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator/(const Fraction& lhs, const Fraction& rhs);
	friend std::ostream& operator<<(std::ostream& out, const Fraction& frac);
	friend class MixedFraction;
};
