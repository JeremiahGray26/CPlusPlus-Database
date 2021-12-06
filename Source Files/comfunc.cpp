#include <stdlib.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <iostream>
#include <vector>
#include <sstream>
#include <conio.h>


using namespace std;

void Hunt(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

}

string SplitString(string inputData, int dataPosition) {
	string my_str = inputData;
	vector<string> result;
	stringstream s_stream(my_str); //create string stream from the string
	while (s_stream.good()) {
		string substr;
		getline(s_stream, substr, '|'); //get first string delimited by user character
		result.push_back(substr);
	}

	return result.at(dataPosition);
}

