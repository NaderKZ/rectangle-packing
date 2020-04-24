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

/* This function takes the Rectangles vector, calculates
the smallest possible square size and packs the rectangles
in that square.
*/
void packRectangles(vector<Rect> rectanglesVector) {
	int totalArea = 0;

	// Sort rectangles based on longest side first.
	sort(rectanglesVector.begin(), rectanglesVector.end(), [](Rect lhs, Rect rhs) 
	{
		if (lhs.getLength() == rhs.getLength())
		{
			return lhs.getWidth() > rhs.getWidth();
		}
		return lhs.getLength() > rhs.getLength();
	});
	
	cout << "Number of total rectangles: " << rectanglesVector.size() << "\n\n";
	cout << "Details of all rectangles: \n\n";

	// Sums up the total size of all rectangles and print out the rectangle details.
	for (int i = 0; i < rectanglesVector.size(); i++)
	{
		cout << "Rectangle ID: " << rectanglesVector[i].getId() << endl;
		cout << "Rectangle Length: " << rectanglesVector[i].getLength() << endl;
		cout << "Rectangle Width: " << rectanglesVector[i].getWidth() << endl;
		cout << "Rectangle Area: " << rectanglesVector[i].getSize() << endl << endl;
		totalArea += rectanglesVector[i].getSize();
	}

	/* We assume that the smallest square that can fit all rectangles 
	should have an area that is as close to the sum of all rectangles 
	together, therefore we take the square root of the sum of the area 
	and round it up to the next integer to get one side of the square.*/
	double squareRoot = sqrt(totalArea);
	int xMax = ceil(squareRoot);
	int yMax = ceil(squareRoot);
	int yMin = 0;

	/* This vector holds all the rectangles that have been placed 
	successfully inside the square.*/
	vector<Rect> rectsPlaced;

	// This vector hold all the rectangles that are yet to be placed.
	vector<Rect> rectsToSkip;

	/* This section places the sorted rectangles with the longest 
	side horizontally starting from the bottom up on the left side 
	of the square.*/
	for (int i = 0; i < rectanglesVector.size(); i++)
	{
		// This checks if the rectangle fits inside the square.
		if (rectanglesVector[i].getLength() <= xMax)
		{
			// This checks if there is space to fit another rectangle on top.
			if (rectanglesVector[i].getWidth() <= (yMax - yMin))
			{
				Point temp;
				rectanglesVector[i].setTopLeftCorner(temp = { 0,(rectanglesVector[i].getWidth() + yMin) });
				rectanglesVector[i].setBottomRightCorner(temp = { rectanglesVector[i].getLength(), yMin });
				yMin += rectanglesVector[i].getWidth();

				// Since this rectangle fits we give it new coordinates and push it into rectsPlaced.
				rectsPlaced.push_back(rectanglesVector[i]);
			}
			else
			{
				/* If the rectangle doesnt fit anymore we move 
				on to the next rectangle until we tried all of 
				the rectangles in this orientation at least once.*/
				rectsToSkip.push_back(rectanglesVector[i]);
			}
		}

	}

	// This vector hold all the rectangles that are yet to be placed after the first iteration.
	vector<Rect> rectsToPlace = rectsToSkip;
	rectsToSkip = {};
	

	/* This section places the leftover rectangles with the longest
	side vertically starting from the bottom up on the right side
	of the square.*/
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
					
					/* Before finalizing the placement, we check if the new 
					rectangle placement overlaps with an existing one.*/
					if (!doOverlap(tlPoint, brPoint, rectsPlaced))
					{
						rectsToPlace[i].setTopLeftCorner(tlPoint);
						rectsToPlace[i].setBottomRightCorner(brPoint);
						rectsPlaced.push_back(rectsToPlace[i]);
					
						placed = true;
					}
				}
			}
			// If we find a suitable placement for our rectangle then we move on to the next one.
			if (placed == true)
			{
				break;
			}
		}
		// if it cant fit in this orientation, then we save the rectangle in a vector and move to the next orientation.
		if (placed == false)
		{
			rectsToSkip.push_back(rectsToPlace[i]);
		}
	}

	rectsToPlace = {};
	
	/* This section places the leftover rectangles with the longest
	side horizontally starting from the right side of the square inwards.*/
	for (int i = 0; i < rectsToSkip.size(); i++)
	{
		bool placed = false;
		for (int j = 0; j < rectsPlaced.size(); j++)
		{
			if (rectsToSkip[i].getLength() <= yMax - rectsPlaced[j].getTopLeftCorner().y)
			{
				Point tlPoint = {rectsPlaced[j].getBottomRightCorner().x-rectsToSkip[i].getWidth(), rectsToSkip[i].getLength() + rectsPlaced[j].getTopLeftCorner().y  };
				Point brPoint = { rectsPlaced[j].getBottomRightCorner().x,rectsPlaced[j].getTopLeftCorner().y};

				/* Before finalizing the placement, we check if the new
				rectangle placement overlaps with an existing one.*/
				if (!doOverlap(tlPoint, brPoint, rectsPlaced))
				{
					rectsToSkip[i].setTopLeftCorner(tlPoint);
					rectsToSkip[i].setBottomRightCorner(brPoint);
					rectsPlaced.push_back(rectsToSkip[i]);

					placed = true;
				}
			}
			// If we find a suitable placement for our rectangle then we move on to the next one.
			if (placed == true)
			{
				break;
			}
		}
		// if it cant fit in this orientation, then we save the rectangle that could not be placed in a vector.
		if (placed == false)
		{
			rectsToPlace.push_back(rectsToSkip[i]);
		}
	}

	/* Print the results to the user.*/
	cout << "The minimum square to pack the rectangles in has the total area of : "<<(xMax*yMax) << " (" << xMax << " * " << yMax << ")	\n";
	cout << "The new coordinates of the Rectangles that have been placed are: \n" << endl;
	for (int i = 0; i < rectsPlaced.size(); i++)
	{
		cout << "Rectangle ID: " << rectsPlaced[i].getId() << endl;
		cout << "Top left corner coordinates: (" << rectsPlaced[i].getTopLeftCorner().x << " , " << rectsPlaced[i].getTopLeftCorner().y << ")" << endl;
		cout << "Bottom right corner coordinates: (" << rectsPlaced[i].getBottomRightCorner().x << " , " << rectsPlaced[i].getBottomRightCorner().y << ")" << endl << endl;
	}

	// Incase we could not fit all rectangles with our algorithm, then print the details.
	for (int i = 0; i < rectsToPlace.size(); i++)
	{
		cout << "These Rectangles could not be placed inside this square based on our algorithm: \n" << endl;
		cout << "Rectangle ID: " << rectsToPlace[i].getId() << endl;
		cout << "Rectangle Length: " << rectsToPlace[i].getLength() << endl;
		cout << "Rectangle Width: " << rectsToPlace[i].getWidth() << endl;
		cout << "Rectangle Area: " << rectsToPlace[i].getSize() << endl << endl;
	}
};

//-------------------------------------------------------------------------------------------------------------------------------------------

int main() {

	// Creates a RectLoader Object and sets the file path or name.
	RectLoader rLoader("Examples/Sample3.ascii");

	// This function packs rectangles into the smallest square.
	packRectangles(rLoader.load());
	
	// When running the code without debugging this keeps the window open til a button is pressed.
	system("pause");
	return 0;
}