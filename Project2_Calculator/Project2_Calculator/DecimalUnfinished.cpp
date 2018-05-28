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