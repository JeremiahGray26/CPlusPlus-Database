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

void LoadCustomers();

void CustModule();

void DrawList();
void SelectCustomer();
void DeleteCust(int delCust);
void ClearCustList();
void ShowSelected(int custNum);
void EditCust(int editCust);
void EditName(int recNum);
void EditAddress(int recNum);
void AddCust();



string custData[100][2];
int custEnd = 0;
int exitModule = 0;


void ClearCustList() {
	int i;
	for (i = 0; i < 100; i++) {
		custData[i][0] = "";
		custData[i][1] = "";
		

	}

}
void LoadCustomers(){ //pulls customer data
	{
		fstream custFile;
		int custID = 0;

		custFile.open("customers.txt", ios::in);
		if (custFile.is_open()) {
			string textLine;
			while (getline(custFile, textLine)) {

				custData[custID][0] = SplitString(textLine,0);
				custData[custID][1] = SplitString(textLine, 1);
				
				//cout << custData[custID][0] << " * " << custData[custID][1] << endl;

				custID++;
			}
			custEnd = custID-1;
		}
		custFile.close(); //close the file object.
	}
	
	
}

void SaveCustomers() {
	int i = 0;
	ofstream custfile("customers.txt");

	if (custfile.is_open())
	{
		for(i = 0; i < 100; i++){

			if (custData[i][0].empty()) { break; }
			custfile << custData[i][0] << "|" << custData[i][1] << endl;
		}
		custfile.close();
	}
		
}



void CustModule() {
	exitModule = 0;
	LoadCustomers();
	DrawList();
	SelectCustomer();


}

void DrawList() {
	int i;

	system("CLS");
	cout << "Customer List";
	
	for (i = 0; i <= custEnd; ++i) {
		Hunt(2, i+2);
		cout << i << " " << custData[i][0] << "   /   " << custData[i][1];
	}

	Hunt(0, 22);
	cout << "Command>";
	Hunt(0, 24);
	cout << "Options: UP/DOWN=select  'a'=add client  'e'=edit client  'd'=delete client  'x'=exit";
}

void SelectCustomer() {
	int curCust;
	
	Hunt(0, 2);
	cout << "¯";
	Hunt(8, 22);  //cursor home
	curCust = 0;
	ShowSelected(curCust);

	while (exitModule !=1) {
		switch (_getch()) {
		case KEY_UP:
			if (curCust == 0) { break; }
			Hunt(0, curCust + 2);
			cout << " ";
			curCust = curCust - 1;
			Hunt(0, curCust + 2);
			cout << "¯";
			ShowSelected(curCust);
			Hunt(8, 22);  //cursor home
			break;

		case KEY_DOWN:
			if (curCust == custEnd) { break; }
			Hunt(0, curCust + 2);
			cout << " ";
			curCust = curCust + 1;
			Hunt(0, curCust + 2);
			cout << "¯";
			ShowSelected(curCust);
			Hunt(8, 22);  //cursor home
			break;

		case x_KEY:
			exitModule = 1;
			break;

		case d_KEY:
			DeleteCust(curCust);
			LoadCustomers();
			DrawList();
			break;

		case e_KEY:
			EditCust(curCust);
			LoadCustomers();
			DrawList();
			break;
		
		case a_KEY:
			AddCust();
			LoadCustomers();
			DrawList();
			break;

		
		}


	}

}

void ShowSelected(int recNum) {
	Hunt(52, 22);
	cout << "                        ";
	Hunt(52, 22);
	cout << recNum << " " << custData[recNum][0];

}


void AddCust() {
	string newName;
	string newAddr;
	
	string junk;  //dumping kb buffer leftover from menu selection, this is just junk
	
	getline(cin, junk);
	system("cls");
	cout << "Add New Customer";
	Hunt(0, 2);
	cout << "Name:";
	Hunt(6, 2);
	getline(cin, newName);
	Hunt(0, 3);
	cout << "Address:";
	Hunt(9, 3);
	getline(cin, newAddr);

	if (newName != "" && newAddr != "") {
		custData[custEnd + 1][0] = newName;
		custData[custEnd + 1][1] = newAddr;
		SaveCustomers();
	}
	
}

void EditCust(int editCust) {
	int editComplete = 0;
	int field = 0;

	system("cls");
	cout << "Edit Customer";
	Hunt(2, 3);
	cout << "Name:" << endl;
	Hunt(2, 4);
	cout << "Address:";
	Hunt(8, 3);
	cout << custData[editCust][0];
	Hunt(11, 4);
	cout << custData[editCust][1];
	
	Hunt(0, 3);
	cout << "¯";

	while (editComplete != 1) {
		switch (_getch()) {
		case enter_KEY:
			if (field == 0) {
				EditName(editCust);
				editComplete = 1;
			}
			else {
				EditAddress(editCust);
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

void EditName(int recNum) {
	string newName;
	Hunt(0, 10);
	cout << "Enter New Name:";
	Hunt(16, 10);
	getline(cin,newName);
	custData[recNum][0] = newName;
	SaveCustomers();

}


void EditAddress(int recNum) {
	string newAddr;
	Hunt(0, 10);
	cout << "Enter New Address:";
	Hunt(19, 10);
	getline(cin, newAddr);
	custData[recNum][1] = newAddr;
	SaveCustomers();

}

void DeleteCust(int delCust) {
	int i;
	int myOffSet = 0;
	string tempCust[100][2];

	for (i = 0; i < 100; i++) {
		if (i == delCust) {
			tempCust[i][0] = custData[i+1][0];
			tempCust[i][1] = custData[i+1][1];
			myOffSet++;
			i++;
		}
		else {
			tempCust[i-myOffSet][0] = custData[i][0];
			tempCust[i-myOffSet][1] = custData[i][1];
		}
		//custEnd--;

	}
	ClearCustList();
	


	i = 0;

	for(i=0; i<100; i++){
		custData[i][0] = tempCust[i][0];
		custData[i][1] = tempCust[i][1];
		
	}
	

	SaveCustomers();



}

