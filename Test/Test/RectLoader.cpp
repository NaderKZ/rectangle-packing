#include "RectLoader.h"



RectLoader::RectLoader(const string&filePath)
{
	this->load(filePath);
}

RectLoader::RectLoader()
{
}


RectLoader::~RectLoader()
{
}

vector<Rect> RectLoader::load(string filePath)
{

	ifstream f(filePath, ios::in);
	if (f) 
	{
		vector<Rect> rectVector;
		int i = 0;
		
		while (!f.eof()) 
		{
			Point p1;
			Point p2;
			string lineBuffer;


			getline(f, lineBuffer, '\n');


			lineBuffer.erase(remove(lineBuffer.begin(), lineBuffer.end(), ','), lineBuffer.end());
			lineBuffer.erase(remove(lineBuffer.begin(), lineBuffer.end(), '\t'), lineBuffer.end());


			//cout << buffer << endl;
			
			
			p1.x = lineBuffer[0] - 48;
			p1.y = lineBuffer[1] - 48;

			p2.x = lineBuffer[2] - 48;
			p2.y = lineBuffer[3] - 48;
			
			Rect tempRect(i,p1,p2);

			rectVector.push_back(tempRect);
			
			//cout << tempRect.getId() << endl;
			
			i++;
		}
		//cout << rectVector.size() << endl;
		//cout << rectVector[1].getRectCorner1().x << endl;
		return rectVector;
	}
	else
	{
		cerr << "File could not be opened!" << endl;
	}

}
