#ifndef _SURFER_GRID_H
#define _SURFER_GRID_H

#include <cstdlib>
#include <clocale>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const int BUFFER_STR_SIZE = 16;

class SurferGrid
{
public:
	SurferGrid();
	~SurferGrid();
	void processData(char *source, char *destination);
protected:
	char *initLocale;
	unsigned int columns;
	unsigned int rows;
	unsigned int xCenter;
	unsigned int yCenter;
	unsigned int cellSize;
	double noDataValue;
	double minValue;
	double maxValue;
	double *data;
	bool _readHeader(ifstream &source, ofstream &destination);
	void _processData(ifstream &source, ofstream &destination);
};

#endif
