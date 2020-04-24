#include "RectLoader.h"



RectLoader::RectLoader(const string&filePath)
{
	this->filepath = filePath;
}

RectLoader::RectLoader()
{
}


RectLoader::~RectLoader()
{
}

/* The load() function reads each line from the file then 
splits each line into 2 seperate coordinates according to 
the tab or "\t" character between them and then converts 
the x and y from string to int for each point. the first 
point is always the top left and the second one is always
the bottom right. Then it saves the Rect objects in a 
vector and returns it.
*/
vector<Rect> RectLoader::load()
{
	cout << "Name of input file: " << this->filepath << "\n\n";
	string filePath = this->filepath;
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
			string delimiter = "\t";
			string temptoken, temptoken2;
			

			getline(f, lineBuffer, '\n');
			int pos = lineBuffer.find(delimiter);
			if (pos == -1)
			{
				cout << "the ascii file is corrupted. please check the file and try again!" << endl;
				system("pause");
				exit(EXIT_FAILURE);
			}

			temptoken = lineBuffer.substr(0, pos);
			temptoken2 = lineBuffer.substr(pos, 256);

			string delimiter2 = ",";
			int pos2 = temptoken.find(delimiter2);
			if (pos2 == -1)
			{
				cout << "the ascii file is corrupted. please check the file and try again!" << endl;
				system("pause");
				exit(EXIT_FAILURE);
			}
			p1.x = stoi(temptoken.substr(0, pos2));
			p1.y = stoi(temptoken.substr(pos2 +1, 256));



			pos2 = temptoken2.find(delimiter2);
			p2.x = stoi(temptoken2.substr(0, pos2));
			p2.y = stoi(temptoken2.substr(pos2+1, 256));

			Rect tempRect(i, p1, p2);
		
			rectVector.push_back(tempRect);
			i++;
		}

		
		f.close();
		
		return rectVector;
	}
	else
	{
		cerr << "File could not be opened!" << endl;
	}

}
