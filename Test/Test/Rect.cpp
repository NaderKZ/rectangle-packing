#include "Rect.h"



Rect::Rect(int id, Point p1, Point p2)
{
	this->rectId = id;
	this->rectCorner1 = p1;
	this->rectCorner2 = p2;
}


Rect::~Rect()
{
}

int Rect::getId() 
{
	return this->rectId;
}

Point Rect::getRectCorner1()
{
	return this->rectCorner1;
}

Point Rect::getRectCorner2()
{
	return this->rectCorner2;
}

