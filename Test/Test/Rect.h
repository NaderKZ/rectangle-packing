#pragma once

struct Point {
	int x, y;
};

class Rect
{
public:
	

	Rect(int,Point,Point);
	~Rect();

	
	int getId();

	Point getRectCorner1();
	Point getRectCorner2();


private:
	int rectId;
	Point rectCorner1;
	Point rectCorner2;
};

