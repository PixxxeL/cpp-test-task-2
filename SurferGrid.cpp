#include "SurferGrid.h"


SurferGrid::SurferGrid()
{
	columns     = 0;
	rows        = 0;
	xCenter     = 0;
	yCenter     = 0;
	cellSize    = 0;
	noDataValue = 0.;
	minValue    = 0.;
	maxValue    = 0.;
	data        = NULL;
	initLocale  = setlocale(LC_ALL, NULL);
}


SurferGrid::~SurferGrid()
{
	data = NULL;
	delete data;
}

void SurferGrid::processData(char *source, char *destination)
{
	ifstream ifs(source);
	ofstream ofs(destination);
	if (!ifs) {
		cout << "Error opening source " << source << " file!" << endl;
		if (ofs) {
			ofs.close();
		}
		return;
	}
	if (!ofs) {
		cout << "Error opening destination " << destination << " file!" << endl;
		if (ifs) {
			ifs.close();
		}
		return;
	}

	bool isHeader = SurferGrid::_readHeader(ifs, ofs);
	if (isHeader) {
		SurferGrid::_processData(ifs, ofs);
	}
	ifs.close();
	ofs.close();
}

bool SurferGrid::_readHeader(ifstream &source, ofstream &destination)
{
	string buff;
	char label[BUFFER_STR_SIZE];
	char value[BUFFER_STR_SIZE];
	bool isPrint = true;
	try {
		source >> label >> columns;
		destination << label << " " << columns << endl;
		if (isPrint) {
			cout << label << " " << columns << endl;
		}
		source >> label >> rows;
		destination << label << " " << rows << endl;
		if (isPrint) {
			cout << label << " " << rows << endl;
		}
		source >> label >> xCenter;
		destination << label << " " << xCenter << endl;
		if (isPrint) {
			cout << label << " " << xCenter << endl;
		}
		source >> label >> yCenter;
		destination << label << " " << yCenter << endl;
		if (isPrint) {
			cout << label << " " << yCenter << endl;
		}
		source >> label >> cellSize;
		destination << label << " " << cellSize << endl;
		if (isPrint) {
			cout << label << " " << cellSize << endl;
		}
		// for comma in double start
		setlocale(LC_ALL, "Russian");
		cout.imbue(locale("Russian"));
		destination.imbue(locale("Russian"));
		// for comma in double end
		source >> label >> value;
		noDataValue = atof(value);
		destination << label << " " << noDataValue << endl;
		if (isPrint) {
			cout << label << " " << noDataValue << endl;
		}
	} catch (...) {
		return false;
	}
	if (!columns || !rows) {
		return false;
	}
	return true;
}

void SurferGrid::_processData(ifstream &source, ofstream &destination)
{
    data = new double[columns * rows];
	double d = 0, mult = 10.;
	char dStr[BUFFER_STR_SIZE];
	for (register unsigned int i = 0; i < rows; ++i) {
		for (register unsigned int j = 0; j < columns; ++j) {
			source >> dStr;
			d = atof(dStr);
			if (i == 0 && j == 0) {
				minValue = d;
				maxValue = d;
			}
			minValue = min(minValue, d);
			maxValue = max(maxValue, d);
			d *= mult;
			data[(i + 1) * j] = d;
			destination << d << " ";
		}
		destination << endl;
    }
	cout << "minvalue " << minValue << endl;
	cout << "maxvalue " << maxValue << endl;
	// revert locale
	setlocale(LC_ALL, initLocale);
	cout.imbue(locale());
	destination.imbue(locale());
}
