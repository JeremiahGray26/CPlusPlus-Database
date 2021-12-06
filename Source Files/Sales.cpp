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

void ClearSalesList();
void LoadSales();
void SaveSales();
void SalesModule();
void DrawSalesList();
void SelectSale();
void ShowSaleSelected(int recNum);
//void AddSale();





using namespace std;

string salesData[100][9];
int salesEnd = 0;
int exitSalesModule = 0;


void SalesModule() {
	exitSalesModule = 0;
	LoadSales();
	DrawSalesList();
	//SelectSale();
	system("pause");
}


void DrawSalesList() {
	int i;

	system("CLS");
	cout << "Sales List";

	for (i = 0; i <= salesEnd; ++i) {
		Hunt(2, i + 2);
		cout << i << " " << salesData[i][0] << "-" << salesData[i][1] << salesData[i][2] << "  " << salesData[i][4] << "x" << salesData[i][3] << " @$" << salesData[i][5] << "/ea  Total: $" << salesData[i][6] << " to " << salesData[i][7] << " by " << salesData[i][8];
	}

	Hunt(0, 22);
	cout << "Command>";
	Hunt(0, 24);
	cout << "Options: UP/DOWN=select  'a'=add sale  'e'=edit sale  'd'=delete sale  'x'=exit";
}

void ClearSalesList() {
	int i;
	for (i = 0; i < 100; i++) {
		salesData[i][0] = "";
		salesData[i][1] = "";
		salesData[i][2] = "";
		salesData[i][3] = "";
		salesData[i][4] = "";
		salesData[i][5] = "";
		salesData[i][6] = "";
		salesData[i][7] = "";
		salesData[i][8] = "";

	}

}


void SelectSale() {
	int curSale;

	Hunt(0, 2);
	cout << "¯";
	Hunt(8, 22);  //cursor home
	curSale = 0;
	ShowSaleSelected(curSale);

	while (exitSalesModule != 1) {
		switch (_getch()) {
		case KEY_UP:
			if (curSale == 0) { break; }
			Hunt(0, curSale + 2);
			cout << " ";
			curSale = curSale - 1;
			Hunt(0, curSale + 2);
			cout << "¯";
			ShowSaleSelected(curSale);
			Hunt(8, 22);  //cursor home
			break;

		case KEY_DOWN:
			if (curSale == salesEnd) { break; }
			Hunt(0, curSale + 2);
			cout << " ";
			curSale = curSale + 1;
			Hunt(0, curSale + 2);
			cout << "¯";
			ShowSaleSelected(curSale);
			Hunt(8, 22);  //cursor home
			break;

		case x_KEY:
			exitSalesModule = 1;
			break;
/*
		case d_KEY:
			DeleteSale(curSale);
			LoadSales();
			DrawList();
			break;

			*/
/*
		case e_KEY:
			EditCust(curCust);
			LoadSales();
			DrawList();
		break;
		*/
		case a_KEY:
			//AddSale();
			LoadSales();
			DrawSalesList();
			break;


		}


	}

}
/*
void AddSale() {
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

*/

void ShowSaleSelected(int recNum) {
	Hunt(52, 22);
	cout << "                        ";
	Hunt(52, 22);
	cout << recNum << " " << salesData[recNum][0];

}

void LoadSales() { //pulls sales data
	{
		fstream salesFile;
		int saleID = 0;

		salesFile.open("sales.txt", ios::in);
		if (salesFile.is_open()) {
			string textLine;
			while (getline(salesFile, textLine)) {

				salesData[saleID][0] = SplitString(textLine, 0);
				salesData[saleID][1] = SplitString(textLine, 1);

				//cout << custData[custID][0] << " * " << custData[custID][1] << endl;

				saleID++;
			}
			salesEnd = saleID - 1;
		}
		salesFile.close(); //close the file object.
	}


}


void SaveSales() {
	int i = 0;
	ofstream salesfile("sales.txt");

	if (salesfile.is_open())
	{
		for (i = 0; i < 100; i++) {

			if (salesData[i][0].empty()) { break; }
			salesfile << salesData[i][0] << "|" << salesData[i][1] << "|" << salesData[i][2] << "|" << salesData[i][3] << "|" << salesData[i][4] << "|" << salesData[i][5] << "|" << salesData[i][6] << "|" << salesData[i][7] << "|" << salesData[i][8] << endl;
		}
		salesfile.close();
	}

}
