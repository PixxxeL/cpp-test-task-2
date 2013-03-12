#include <cstdlib>
#include <iostream>
#include "SurferGrid.h"

using namespace std;

int main(int argc, char *argv[])
{
    SurferGrid grid;
	grid.processData("data\\test.txt", "data\\out.txt");
	system("pause");
    return EXIT_SUCCESS;
}
