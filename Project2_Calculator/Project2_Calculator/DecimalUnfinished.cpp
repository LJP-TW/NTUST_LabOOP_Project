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
	// ����
}

Integer Decimal::getGCD(Integer a, Integer b) const
{
	return Integer();
}

Decimal operator+(const Integer & lva, const Decimal & rva)
{
	return Decimal();
}

Decimal operator-(const Integer & lva, const Decimal & rva)
{
	return Decimal();
}

Decimal operator*(const Integer & lva, const Decimal & rva)
{
	return Decimal();
}

Decimal operator/(const Integer & lva, const Decimal & rva)
{
	return Decimal();
}
