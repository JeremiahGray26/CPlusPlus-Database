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
#include "comfunc.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define x_KEY 120
#define a_KEY 97
#define e_KEY 101
#define d_KEY 100
#define enter_KEY 13

using namespace std;

void LoadRep();
void RepModule();
void DrawList2();
void SelectRep();
void DeleteRep(int delRep);
void ClearRepList();
void ShowSelected2(int recNum);
void EditRep(int editRep);
void EditName1(int recNum);
void EditAddress1(int recNum);
void AddRep();


string repData[100][3];
int repEnd = 0;
int exitModule2 = 0;
/*
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

*/
void ClearRepList() {
	int i;
	for (i = 0; i < 100; i++) {
		repData[i][0] = "";
		repData[i][1] = "";
		repData[i][2] = "";

	}

}

void LoadRep() { 
	{
		fstream repFile;
		int repID = 0;

		repFile.open("SalesRepInfo.txt", ios::in);
		if (repFile.is_open()) {
			string textLine;
			while (getline(repFile, textLine)) {

				repData[repID][0] = SplitString(textLine, 0);
				repData[repID][1] = SplitString(textLine, 1);
				repData[repID][2] = SplitString(textLine, 2);

				//cout << repData[repID][0] << " * " << repData[repID][1] << " * " << repData[repID][2] << endl;

				repID++;
			}
			repEnd = repID - 1;
		}
		repFile.close(); //close the file object.
	}


}

void SaveRep() {
	int i = 0;
	ofstream repFile("Text.txt");

	if (repFile.is_open())
	{
		for (i = 0; i < 100; i++) {

			if (repData[i][0].empty()) { break; }
			repFile << repData[i][0] << "|" << repData[i][1] << "|" << repData[i][2] << endl;
		}
		repFile.close();
	}

}

void RepModule() {
	exitModule2 = 0;
	LoadRep();
	DrawList2();
	SelectRep();


}

void DrawList2() {
	int i;

	system("CLS");
	cout << "Sales Representative List";

	for (i = 0; i <= repEnd; ++i) {
		Hunt(2, i + 2);
		cout << i << " " << repData[i][0] << "  /  " << repData[i][1] << "  /  Bonus: " << repData[i][2] << "%" << endl;
	}

	Hunt(0, 22);
	cout << "Command>";
	Hunt(0, 24);
	cout << "Options: UP/DOWN=select  'a'=add Rep  'e'=edit Rep  'd'=delete Rep  'x'=exit";
}

void SelectRep() {
	int curRep;

	Hunt(0, 2);
	cout << "¯";
	Hunt(8, 22);  //cursor home
	curRep = 0;
	ShowSelected2(curRep);

	while (exitModule2 != 1) {
		switch (_getch()) {
		case KEY_UP:
			if (curRep == 0) { break; }
			Hunt(0, curRep + 2);
			cout << " ";
			curRep = curRep - 1;
			Hunt(0, curRep + 2);
			cout << "¯";
			ShowSelected2(curRep);
			Hunt(8, 22);  //cursor home
			break;

		case KEY_DOWN:
			if (curRep == repEnd) { break; }
			Hunt(0, curRep + 2);
			cout << " ";
			curRep = curRep + 1;
			Hunt(0, curRep + 2);
			cout << "¯";
			ShowSelected2(curRep);
			Hunt(8, 22);  //cursor home
			break;

		case x_KEY:
			exitModule2 = 1;
			break;

		case d_KEY:
			DeleteRep(curRep);
			LoadRep();
			DrawList2();
			break;

		case e_KEY:
			EditRep(curRep);
			LoadRep();
			DrawList2();
			break;

		case a_KEY:
			AddRep();
			LoadRep();
			DrawList2();
			break;


		}


	}

}

void ShowSelected2(int recNum) {
	Hunt(52, 22);
	cout << "                        ";
	Hunt(52, 22);
	cout << recNum << " " << repData[recNum][0];

}

void AddRep() {
	string newName;
	string newAddr;
	string newBonus = "0";

	string junk;  //dumping kb buffer leftover from menu selection, this is just junk

	getline(cin, junk);
	system("cls");
	cout << "Add New Representative";
	Hunt(0, 2);
	cout << "Name:";
	Hunt(6, 2);
	getline(cin, newName);
	Hunt(0, 3);
	cout << "Address:";
	Hunt(9, 3);
	getline(cin, newAddr);

	if (newName != "" && newAddr != "") {
		repData[repEnd + 1][0] = newName;
		repData[repEnd + 1][1] = newAddr;
		repData[repEnd + 1][2] = newBonus;
		repEnd++;
		SaveRep();
	}

}


//This function could use a little work, I can't properly add the "EditMonthlySales" function
void EditRep(int editRep) {
	int editComplete = 0;
	int field = 0;

	system("cls");
	cout << "Edit Representative";
	Hunt(2, 3);
	cout << "Name:" << endl;
	Hunt(2, 4);
	cout << "Address:";
	Hunt(8, 3);
	cout << repData[editRep][0];
	Hunt(11, 4);
	cout << repData[editRep][1];

	Hunt(0, 3);
	cout << "¯";

	while (editComplete != 1) {
		switch (_getch()) {
		case enter_KEY:
			if (field == 0) {
				EditName1(editRep);
				editComplete = 1;
			}
			else {
				EditAddress1(editRep);
				editComplete = 1;
			}
			break;

		case KEY_DOWN:
			if (field == 0) {
				Hunt(0, 3);
				cout << " ";
				Hunt(0, 4);
				cout << "¯";
				field = 1;

			}
			break;

		case KEY_UP:
			if (field == 1) {
				Hunt(0, 4);
				cout << " ";
				Hunt(0, 3);
				cout << "¯";
				field = 0;

			}
			break;

		case x_KEY:
			editComplete = 1;
			break;
		}



	}
}

void EditName1(int recNum) {
	string newName;
	//Hunt(0, 10);
	cout << "Enter New Name:";
	//Hunt(16, 10);
	getline(cin, newName);
	repData[recNum][0] = newName;
	SaveRep();

}

void EditAddress1(int recNum) {
	string newAddr;
	//Hunt(0, 10);
	cout << "Enter New Address:";
	//Hunt(19, 10);
	getline(cin, newAddr);
	repData[recNum][1] = newAddr;
	SaveRep();

}

void EditBonus(int recNum) {
	string updatedBonus;
	//Hunt(0, 10);
	cout << "Enter new bonus multiplier:";
	//Hunt(19, 10);
	getline(cin, updatedBonus);
	repData[recNum][2] = updatedBonus;
	SaveRep();

}

void DeleteRep(int delRep) {
	int i;
	int myOffSet = 0;
	string tempRep[100][3];

	for (i = 0; i < 100; i++) {
		if (i == delRep) {
			tempRep[i][0] = repData[i + 1][0];
			tempRep[i][1] = repData[i + 1][1];
			tempRep[i][1] = repData[i + 1][2];
			myOffSet++;
			i++;
		}
		else {
			tempRep[i - myOffSet][0] = repData[i][0];
			tempRep[i - myOffSet][1] = repData[i][1];
			tempRep[i - myOffSet][2] = repData[i][2];
		}
		repEnd--;

	}
	ClearRepList();



	i = 0;

	for (i = 0; i < 100; i++) {
		repData[i][0] = tempRep[i][0];
		repData[i][1] = tempRep[i][1];
		repData[i][2] = tempRep[i][2];

	}


	SaveRep();



}




