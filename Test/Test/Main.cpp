#pragma once
#include "RectLoader.h"

using namespace std;

// Returns true if two rectangles (l1, r1) and (l2, r2) overlap 
bool doOverlap(Point l1, Point r1, vector<Rect> rectsPlaced )
{
	for (int i = 0; i < rectsPlaced.size(); i++)
	{
		// If one rectangle is on left side of other 
		if (l1.x >= rectsPlaced[i].getBottomRightCorner().x || rectsPlaced[i].getTopLeftCorner().x >= r1.x) 
		{
		}// If one rectangle is above other 
		else if (l1.y <= rectsPlaced[i].getBottomRightCorner().y || rectsPlaced[i].getTopLeftCorner().y <= r1.y)
		{
		}
		else
		{
			return true;
		}

	}

	return false;
	
}

void packRectangles(vector<Rect> rectanglesVector) {
	int totalArea = 0;


	sort(rectanglesVector.begin(), rectanglesVector.end(), [](Rect lhs, Rect rhs) 
	{
		if (lhs.getLength() == rhs.getLength())
		{
			return lhs.getWidth() > rhs.getWidth();
		}
		return lhs.getLength() > rhs.getLength();
	});
	for (int i = 0; i < rectanglesVector.size(); i++)
	{
		/*cout << "Rectangle ID: " << rectanglesVector[i].getId() << endl;
		cout << "Rectangle Length: " << rectanglesVector[i].getLength() << endl;
		cout << "Rectangle Width: " << rectanglesVector[i].getWidth() << endl;
		cout << "Rectangle Area: " << rectanglesVector[i].getArea() << endl << endl;*/
		totalArea += rectanglesVector[i].getSize();
	}
	

	for (int i = 0; i < rectanglesVector.size(); i++)
	{
		cout << "Rectangle ID: " << rectanglesVector[i].getId() << endl;
		cout << "Rectangle Length: " << rectanglesVector[i].getLength() << endl;
		cout << "Rectangle Width: " << rectanglesVector[i].getWidth() << endl;
		cout << "Rectangle Area: " << rectanglesVector[i].getSize() << endl << endl;
		totalArea += rectanglesVector[i].getSize();
	}

	
	double squareRoot = sqrt(totalArea);
	int xMax = ceil(squareRoot);
	int yMax = ceil(squareRoot);
	int yMin = 0;

	vector<Rect> tempVector = rectanglesVector;
	
	vector<Rect> rectsPlaced;
	vector<Rect> rectsToSkip;
	for (int i = 0; i < rectanglesVector.size(); i++)
	{
		if (rectanglesVector[i].getWidth() <= (yMax-yMin))
		{
			Point temp;
			rectanglesVector[i].setTopLeftCorner(temp = { 0,(rectanglesVector[i].getWidth() + yMin) });
			rectanglesVector[i].setBottomRightCorner(temp = { rectanglesVector[i].getLength(), yMin });
			yMin += rectanglesVector[i].getWidth();
			rectsPlaced.push_back(rectanglesVector[i]);
		}
		else
		{
			rectsToSkip.push_back(rectanglesVector[i]);
		}

	}

	vector<Rect> rectsToPlace = rectsToSkip;
	rectsToSkip = {};
	
	for (int i = 0; i < rectsToPlace.size(); i++)
	{
		bool placed = false;
		for (int j = 0; j < rectsPlaced.size(); j++)
		{
			if (rectsToPlace[i].getWidth() <= (xMax - rectsPlaced[j].getBottomRightCorner().x))
			{
				if (rectsToPlace[i].getLength() <= yMax - (rectsPlaced[j].getBottomRightCorner().y))
				{
					Point tlPoint = { rectsPlaced[j].getBottomRightCorner().x, (rectsToPlace[i].getLength() + rectsPlaced[j].getBottomRightCorner().y) };
					Point brPoint = { (rectsToPlace[i].getWidth() + rectsPlaced[j].getBottomRightCorner().x), rectsPlaced[j].getBottomRightCorner().y };
					
					if (!doOverlap(tlPoint, brPoint, rectsPlaced))
					{
						rectsToPlace[i].setTopLeftCorner(tlPoint);
						rectsToPlace[i].setBottomRightCorner(brPoint);
						rectsPlaced.push_back(rectsToPlace[i]);
						
						placed = true;
					}
				}
			}
			if (placed == true)
			{
				break;
			}
		}
		if (placed == false)
		{
			rectsToSkip.push_back(rectsToPlace[i]);
		}
		
		
	}

	rectsToPlace = {};
	for (int i = 0; i < rectsToSkip.size(); i++)
	{
		bool placed = false;
		for (int j = 0; j < rectsPlaced.size(); j++)
		{
			if (rectsToSkip[i].getLength() <= yMax - rectsPlaced[j].getTopLeftCorner().y)
			{
				Point tlPoint = {rectsPlaced[j].getBottomRightCorner().x-rectsToSkip[i].getWidth(), rectsToSkip[i].getLength() + rectsPlaced[j].getTopLeftCorner().y  };
				
				Point brPoint = { rectsPlaced[j].getBottomRightCorner().x,rectsPlaced[j].getTopLeftCorner().y};

				if (!doOverlap(tlPoint, brPoint, rectsPlaced))
				{
					rectsToSkip[i].setTopLeftCorner(tlPoint);
					rectsToSkip[i].setBottomRightCorner(brPoint);
					rectsPlaced.push_back(rectsToSkip[i]);

					placed = true;
				}
				

			}
			if (placed == true)
			{
				break;
			}
			else
			{
				rectsToPlace.push_back(rectsToSkip[i]);

			}
		}
		if (placed == false)
		{
			rectsToPlace.push_back(rectsToSkip[i]);

		}
	}

	cout << "The minimum square to pack the rectangles in has the total area of : "<<(xMax*yMax) << " (" << xMax << " * " << yMax << ")	\n";
	cout << "All Rectangles have been placed and the new coordinates for each rectangles are: \n" << endl;
	for (int i = 0; i < rectsPlaced.size(); i++)
	{
		cout << "Rectangle ID: " << rectsPlaced[i].getId() << endl;
		cout << "Top left corner coordinates: (" << rectsPlaced[i].getTopLeftCorner().x << " , " << rectsPlaced[i].getTopLeftCorner().y << ")" << endl;
		cout << "Bottom right corner coordinates: (" << rectsPlaced[i].getBottomRightCorner().x << " , " << rectsPlaced[i].getBottomRightCorner().y << ")" << endl << endl;
	}
};

int main() {
	RectLoader rLoader("text4.ascii");

	packRectangles(rLoader.load());


	

	system("pause");
	return 0;
}