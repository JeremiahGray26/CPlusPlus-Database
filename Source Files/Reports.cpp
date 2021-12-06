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
#include <iomanip>
#include <cmath>
#include <limits>


#define KEY_UP 72
#define KEY_DOWN 80
#define x_KEY 120
#define a_KEY 97
#define e_KEY 101
#define d_KEY 100
#define enter_KEY 13


std::string SplitString(std::string inputData, int dataPosition); //used to parse strings

void LoadRptCustomers();
void LoadRptProduct();
void LoadRptReps();
void LoadRptSales();
void DrawReportMenu();
void ReportMenu();
void RepSales();
void MonthlySales();
void PrintLn(std::string myData, int vPos);

void TestPrint();







using namespace std;

int exitReports = 0;
int reportAction = 0;
std::string reptCustData[100][2];
int reptCustEnd = 0;


std::string reptProductData[100][2];
int reptProdEnd = 0;

std::string reptSalesData[100][9];
int reptSalesEnd = 0;

std::string reptRepData[100][3];
int reptRepEnd = 0;

void ReportModule() {
	exitReports = 0;
	LoadRptCustomers();
	LoadRptProduct();
	LoadRptReps();
	LoadRptSales();
	ReportMenu();

	
	
	


}

void ReportMenu() {
	//loop program until the user quits
	while (reportAction != 9) {
		DrawReportMenu();
		std::cin >> reportAction;

		switch (reportAction) {
		case 1:
			RepSales();
			break;
		case 2:
			MonthlySales();
			break;

		case 9:
			
			break;



		}

	}

	
}

void DrawReportMenu() {
	system("CLS");

	Hunt(0, 3);
	cout << "1. Rep Yearly Sales Report";
	Hunt(0, 5);
	cout << "2. Monthly Sales";
	

	Hunt(0, 13);
	cout << "9. Quit";

	//set cursor line up
	Hunt(0, 15);
	cout << "Selection>";

}



void RepSales() {
	int lastI = 0;
	
	int numLastLines = 0;
	int junk=0;
	string buildStr;
	system("CLS");

	std::cout << std::setprecision(2) << std::fixed;

	
	for (int i = 0; i < reptRepEnd + 1; i++) {
		double totalSales = 0;
		double bonusAmt = 0;
		double bonusMul=0;

		buildStr = "Sales Rep: " + reptRepData[i][0] + "       Sales Bonus: " + reptRepData[i][2] + "%";
		PrintLn(buildStr, i + numLastLines);
		numLastLines++;
		PrintLn("==================================================", i + numLastLines);
		numLastLines++;
		bonusMul = stod(reptRepData[i][2]) * 0.01;
		for (int h = 0; h < reptSalesEnd + 1; h++) {
			if (reptSalesData[h][8] == reptRepData[i][0]) {
				buildStr = reptSalesData[h][0] + "-" + reptSalesData[h][1] + "-" + reptSalesData[h][2] + ": " + reptSalesData[h][4] + "x" + reptSalesData[h][3] + "  ea: $" + reptSalesData[h][5] + "  Total : $" + reptSalesData[h][6];
				PrintLn(buildStr, i + numLastLines);
				totalSales = totalSales + stod(reptSalesData[h][6]);
				numLastLines++;

			}
		}
		
		//convert doubles to 2-digit precision and put in string
		bonusAmt = totalSales * bonusMul;
		std::ostringstream sTotalSales;
		sTotalSales << std::fixed;
		sTotalSales << std::setprecision(2);
		sTotalSales << totalSales;
		std::string zTotalSales = sTotalSales.str();

		std::ostringstream sBonusAmt;
		sBonusAmt << std::fixed;
		sBonusAmt << std::setprecision(2);
		sBonusAmt << bonusAmt;
		std::string zBonusAmt = sBonusAmt.str();
		

		buildStr = "Total Sales: $" + zTotalSales + "   Bonus: $" + zBonusAmt;
		PrintLn(buildStr, i + numLastLines);
		numLastLines++;
		lastI = i;
	}
	numLastLines++;
	
	Hunt(0, numLastLines+lastI);
	system("pause");
}

void PrintLn(string myData, int vPos) {
	Hunt(0, vPos);
	
	cout << myData;

}
void TestPrint() {
	for (int i = 0; i < reptSalesEnd + 1; i++) {
		for (int h = 0; h < 9; h++) {
			cout << reptSalesData[i][h] << " ";
		}
	}
}


void MonthlySales() {
	double totalSales = 0;
	int numLastLines = 0;
	int lastI = 0;

	int selMonth = 0;
	system("cls");
	Hunt(0, 0);
	cout << "Monthly Sales Report";
	Hunt(0, 1);
	cout << "==================================";
	Hunt(0, 3);
	cout << "Which Month? (1-12)";
	
	while (selMonth <1 || selMonth >12) {
		Hunt(20, 3);
		cout << "                        ";
		Hunt(20, 3);
		cin >> selMonth;
	}
	system("cls");
	Hunt(0, 0);
	for (int i = 0; i < reptSalesEnd + 1; i++) {
		if (stoi(reptSalesData[i][0]) == selMonth) {
			Hunt(0, numLastLines + 1);
			cout << reptSalesData[i][0] << "-" << reptSalesData[i][1] << "-" << reptSalesData[i][2] << "  " << reptSalesData[i][4] << "x" << reptSalesData[i][3] << " @ $" << reptSalesData[i][5] << "/ea  Total: $" << reptSalesData[i][6] << " to " << reptSalesData[i][7] << " by " << reptSalesData[i][8];
			totalSales = totalSales + stod(reptSalesData[i][6]);
			numLastLines++;
			lastI = i;
		}


	}
	numLastLines++;
	Hunt(0, lastI + numLastLines);
	cout << "Total Sales: $" << totalSales;
	numLastLines++;
	
	Hunt(0, lastI+numLastLines);
	system("pause");
}










void LoadRptCustomers() { //pulls customer data
	{
		fstream custFile;
		int reptCustID = 0;

		custFile.open("customers.txt", ios::in);
		if (custFile.is_open()) {
			string textLine;
			while (getline(custFile, textLine)) {

				reptCustData[reptCustID][0] = SplitString(textLine, 0);
				reptCustData[reptCustID][1] = SplitString(textLine, 1);

				//cout << custData[custID][0] << " * " << custData[custID][1] << endl;

				reptCustID++;
			}
			reptCustEnd = reptCustID - 1;
		}
		custFile.close(); //close the file object.
	}


}

void LoadRptProduct() { //pulls product data
	{
		fstream prodFile;
		int reptProdID = 0;

		prodFile.open("ProductFile.txt", ios::in);
		if (prodFile.is_open()) {
			string textLine;
			while (getline(prodFile, textLine)) {

				reptProductData[reptProdID][0] = SplitString(textLine, 0);
				reptProductData[reptProdID][1] = SplitString(textLine, 1);
				//cout << ProductData[prodID][0] << " * " << ProductData[prodID][1] << endl;

				reptProdID++;
			}
			reptProdEnd = reptProdID - 1;
		}
		prodFile.close(); //close the file object.
	}


}

void LoadRptSales() { //pulls sales data, field 8 is the sales rep
	{
		fstream salesFile;
		int reptSalesID = 0;

		salesFile.open("sales.txt", ios::in);
		if (salesFile.is_open()) {
			string textLine;
			while (getline(salesFile, textLine)) {

				reptSalesData[reptSalesID][0] = SplitString(textLine, 0);
				reptSalesData[reptSalesID][1] = SplitString(textLine, 1);
				reptSalesData[reptSalesID][2] = SplitString(textLine, 2);
				reptSalesData[reptSalesID][3] = SplitString(textLine, 3);
				reptSalesData[reptSalesID][4] = SplitString(textLine, 4);
				reptSalesData[reptSalesID][5] = SplitString(textLine, 5);
				reptSalesData[reptSalesID][6] = SplitString(textLine, 6);
				reptSalesData[reptSalesID][7] = SplitString(textLine, 7);
				reptSalesData[reptSalesID][8] = SplitString(textLine, 8);
				

				reptSalesID++;
			}
			reptSalesEnd = reptSalesID - 1;
		}
		salesFile.close(); //close the file object.
	}


}

void LoadRptReps() { //pulls rep data
	{
		fstream repFile;
		int reptRepID = 0;

		repFile.open("SalesRepInfo.txt", ios::in);
		if (repFile.is_open()) {
			string textLine;
			while (getline(repFile, textLine)) {

				reptRepData[reptRepID][0] = SplitString(textLine, 0);
				reptRepData[reptRepID][1] = SplitString(textLine,1);
				reptRepData[reptRepID][2] = SplitString(textLine, 2);
				
				reptRepID++;
			}
			reptRepEnd = reptRepID - 1;
		}
		repFile.close(); //close the file object.
	}


}




