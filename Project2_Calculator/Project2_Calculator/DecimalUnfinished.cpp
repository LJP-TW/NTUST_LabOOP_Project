#include "Decimal.h"

const bool Decimal::operator>(const Decimal& other) const
{
	return false;
}

const bool Decimal::operator>(const Integer& other) const
{
	return false;
}

const bool Decimal::operator>=(const Decimal& other) const
{
	return false;
}

const bool Decimal::operator>=(const Integer& other) const
{
	return false;
}

const bool Decimal::operator<(const Decimal& other) const
{
	return false;
}

const bool Decimal::operator<(const Integer& other) const
{
	return false;
}

const bool Decimal::operator<=(const Decimal& other) const
{
	return false;
}

const bool Decimal::operator<=(const Integer& other) const
{
	return false;
}

const bool Decimal::operator==(const Decimal& other) const
{
	return false;
}

const bool Decimal::operator==(const Integer& other) const
{
	return false;
}

const Decimal Decimal::power(const Decimal& other) const
{
	Decimal newDecimal;

	// Write some code

	return newDecimal;
}

const Integer Decimal::dtoi() const
{
	Integer newInteger;

	// Write some code

	return newInteger;
}

void Decimal::reduceFraction()
{
	// ¬ù¤À
}

Integer Decimal::getGCD(Integer a, Integer b) const
{
	return Integer();
}

ostream& operator <<(ostream& output, Decimal& decimal)
{
	// Output to 100 decimal digit

	return output;
}