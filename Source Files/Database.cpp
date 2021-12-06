#include <stdlib.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <iostream>
#include <vector>
#include <sstream>
#include <conio.h> //used by GotoXY
#include "SalesRep.h"
#include "Customers.h"
#include "Product.h"
#include "Reports.h"
#include "comfunc.h"
#include "sales.h"
#include "SalesRep.h"





using namespace std;





//prototype declarations
void GotoXY(int x, int y);
void DrawMainMenu();
void PauseMe(); //debugging pause
string SplitString(string inputData, int dataPosition); //used to parse strings


//use this to enable debug options
int debugMe = 1;


//global variables
string companyName = "Generic Corp.";
string programTitle = "Stupid Database";  //set the program name here
string myVersion = "0.01";  //increment this for program version
int numCols = 75; //terminal columns
int numLines = 24; //terminal lines

//these will be used to reference data line items between different program modules
int clientID;

string prodData[99][2];
int totalProducts=0;


int main()
{
	int mainAction = 0;  //main menu selection default value is 0
	
//configure console
HWND console = GetConsoleWindow();
RECT r;
GetWindowRect(console, &r); //get console data
MoveWindow(console, r.left, r.top, 1024, 768, TRUE); // 1024 width, 768 height


//loop program until the user quits
while (mainAction != 9) {
	DrawMainMenu();
	cin >> mainAction;

	switch (mainAction) {
	case 1:
		CustModule();
		break;
	case 2:
		RepModule();
		break;
	case 3:
		ProductModule();
		break;
	case 4:
		SalesModule();

	case 5:
		ReportModule();
		break;

	case 8:

	case 9:
		break;



	}

}


exit(0);
}

//draw the main menu
void DrawMainMenu() {
	system("CLS");
	GotoXY(0, 0);
	cout << companyName;
	GotoXY(0, 1);
	cout << programTitle << " v" << myVersion;
	GotoXY(0, 3);
	cout << "1. Client Information";
	GotoXY(0, 5);
	cout << "2. Sales Representatives";
	GotoXY(0, 7);
	cout << "3. Product/Services";
	GotoXY(0, 9);
	cout << "4. Sales";
	GotoXY(0, 11);
	cout << "5. Reports";

	GotoXY(0, 13);
	cout << "9. Quit";

	//set cursor line up
	GotoXY(0, 15);
	cout << "Selection>";



}


//This way I can use GotoXY(x,y) to move the cursor around the terminal to draw elements
//x=column, y=line
//terminal is assumed to be standard 76x24 and sizes are declared in global vars.  This size isn't anything official, its just a good standard size which should fit fine within the 1024x768 window setup declared later
void GotoXY(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

}






void PauseMe() {
	string myNull;
	cout << "Do something...";
	cin >> myNull;


}
