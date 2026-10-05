#include "vect2.hpp"

vect2::vect2()
{
	this->x = 0;
	this->y = 0;
}

vect::vect2(int num1, int num2)
{
	this->x = num1;
	this->y = num2;
}

vect2::vect2(const vect2& source)
{
	*this = source;
}

vect2& vect2::operator=(const vect2& source)
{
	if(this != &source)
	{
		this->x = source.x;
		this->y = source.y;
	}
	return(*this);
}

int vect2::operator[](int index) const
{
	if(index == 0)
		return(this->x);
	return(this->y);
}

int& vect2::operator[](int index)
{
	if(index == 0)
		return(this->x);
	return(this->y);
}
