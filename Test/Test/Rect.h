#pragma once
#include <cstdlib>

/** Decided to use Struct in order to save the coordinates of the 
top left corner and the bottom right corner of each Rectangle.*/
struct Point {
	int x, y;
};

/* Class Rect: an Object of this class is created for each line 
in the ascii file (for the rectangles).
*/
class Rect
{
public:
	
	Rect();
	Rect(int,Point,Point);
	~Rect();

	
	int getId();

	Point getTopLeftCorner();
	Point getBottomRightCorner();

	int getLength();
	int getWidth();
	int getSize();

	void calculateLWS();
	
	void setTopLeftCorner(Point);
	void setBottomRightCorner(Point);

private:
	int rectId;
	int length;
	int width;
	int area;
	Point rectTopLeftCorner;
	Point rectBottomRightCorner;
};

