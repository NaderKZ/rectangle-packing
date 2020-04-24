#include "Rect.h"



Rect::Rect()
{
}

/*The constructor creates a new Rect object and assigns it 
an ID and sets the given points, p1 is the top left corner 
and p2 is the bottom right corner, it also calls the 
function calculateLWS() that calculates all other needed measurements.*/
Rect::Rect(int id, Point p1, Point p2)
{
	this->rectId = id;
	this->rectTopLeftCorner = p1;
	this->rectBottomRightCorner = p2;
	this->calculateLWS();
}


Rect::~Rect()
{
}

int Rect::getId() 
{
	return this->rectId;
}

Point Rect::getTopLeftCorner()
{
	return this->rectTopLeftCorner;
}

Point Rect::getBottomRightCorner()
{
	return this->rectBottomRightCorner;
}

int Rect::getLength()
{
	return this->length;
}

int Rect::getWidth()
{
	return this->width;
}

int Rect::getSize()
{
	return this->area;
}

/* This function calculates the length, width
and size of the Rect object*/
void Rect::calculateLWS()
{
	int length, width;

	width = abs(this->rectTopLeftCorner.y - this->rectBottomRightCorner.y);
	length = abs(this->rectBottomRightCorner.x - this->rectTopLeftCorner.x);
	if (width > length)
	{
		int temp = length;
		length = width;
		width = temp;
	}
	this->length = length;
	this->width = width;
	this->area = length * width;
}

void Rect::setTopLeftCorner(Point tlCorner)
{
	this->rectTopLeftCorner = tlCorner;
}

void Rect::setBottomRightCorner(Point brCorner)
{
	this->rectBottomRightCorner = brCorner;
}

