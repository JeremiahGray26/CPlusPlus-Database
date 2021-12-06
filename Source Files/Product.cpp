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

void LoadProduct();

void ProductModule();

void DrawList1();
void SelectProduct();
void DeleteProduct(int delProduct);
void ClearProductList();
void ShowSelected1(int ProductNum);
void EditProduct(int EditProduct);
void EditBrand(int recNum);
void EditPrice(int recNum);
void AddProduct();


string ProductData[100][2];
int prodEnd = 0;
int exitModule1 = 0;


void ClearProductList() {
	int i;
	for (i = 0; i < 100; i++) {
		ProductData[i][0] = "";
		ProductData[i][1] = "";

	}

}
void LoadProduct() { //pulls customer data
	{
		fstream prodFile;
		int prodID = 0;

		prodFile.open("ProductFile.txt", ios::in);
		if (prodFile.is_open()) {
			string textLine;
			while (getline(prodFile, textLine)) {

				ProductData[prodID][0] = SplitString(textLine, 0);
				ProductData[prodID][1] = SplitString(textLine, 1);
				//cout << ProductData[prodID][0] << " * " << ProductData[prodID][1] << endl;

				prodID++;
			}
			prodEnd = prodID - 1;
		}
		prodFile.close(); //close the file object.
	}


}

void SaveProduct() {
	int i = 0;
	ofstream prodFile("ProductFile.txt");

	if (prodFile.is_open())
	{
		for (i = 0; i < 100; i++) {

			if (ProductData[i][0].empty()) { break; }
			prodFile << ProductData[i][0] << "|" << ProductData[i][1] << endl;
		}
		prodFile.close();
	}

}



void ProductModule() {
	exitModule1 = 0;
	LoadProduct();
	DrawList1();
	SelectProduct();


}

void DrawList1() {
	int i;

	system("CLS");
	cout << "Product List";

	for (i = 0; i <= prodEnd; ++i) {
		Hunt(2, i + 2);
		cout << i << " " << ProductData[i][0] << "   /   " << ProductData[i][1];
	}

	Hunt(0, 22);
	cout << "Command>";
	Hunt(0, 24);
	cout << "Options: UP/DOWN=select  'a'=add Product  'e'=edit Product  'd'=delete Product 'c'=calculate Sales  'x'=exit";
}

void SelectProduct() {
	int curProduct;

	Hunt(0, 2);
	cout << "¯";
	Hunt(8, 22);  //cursor home
	curProduct = 0;
	ShowSelected1(curProduct);

	while (exitModule1 != 1) {
		switch (_getch()) {
		case KEY_UP:
			if (curProduct == 0) { break; }
			Hunt(0, curProduct + 2);
			cout << " ";
			curProduct = curProduct - 1;
			Hunt(0, curProduct + 2);
			cout << "¯";
			ShowSelected1(curProduct);
			Hunt(8, 22);  //cursor home
			break;

		case KEY_DOWN:
			if (curProduct == prodEnd) { break; }
			Hunt(0, curProduct + 2);
			cout << " ";
			curProduct = curProduct + 1;
			Hunt(0, curProduct + 2);
			cout << "¯";
			ShowSelected1(curProduct);
			Hunt(8, 22);  //cursor home
			break;

		case x_KEY:
			exitModule1 = 1;
			break;

		case d_KEY:
			DeleteProduct(curProduct);
			LoadProduct();
			DrawList1();
			break;

		case e_KEY:
			EditProduct(curProduct);
			LoadProduct();
			DrawList1();
			break;

		case a_KEY:
			AddProduct();
			LoadProduct();
			DrawList1();
			break;

		}


	}

}

void ShowSelected1(int recNum) {
	Hunt(52, 22);
	cout << "                        ";
	Hunt(52, 22);
	cout << recNum << " " << ProductData[recNum][0];

}


void AddProduct() {
	string newBrand;
	string newPrice;

	string junk;  //dumping kb buffer leftover from menu selection, this is just junk

	getline(cin, junk);
	system("CLS");
	cout << "Add New Customer";
	Hunt(0, 2);
	cout << "Brand:";
	Hunt(6, 2);
	getline(cin, newBrand);
	Hunt(0, 3);
	cout << "Price:";
	Hunt(9, 3);
	getline(cin, newPrice);

	if (newBrand != "" && newPrice != "") {
		ProductData[prodEnd + 1][0] = newBrand;
		ProductData[prodEnd + 1][1] = newPrice;
		SaveProduct();
	}

}

void EditProduct(int EditProduct) {
	int editComplete = 0;
	int field = 0;

	system("CLS");
	cout << "Edit Product";
	Hunt(2, 3);
	cout << "Brand:" << endl;
	Hunt(2, 4);
	cout << "Price:";
	Hunt(8, 3);
	cout << ProductData[EditProduct][0];
	Hunt(11, 4);
	cout << "$" + ProductData[EditProduct][1];

	Hunt(0, 3);
	cout << "¯";

	while (editComplete != 1) {
		switch (_getch()) {
		case enter_KEY:
			if (field == 0) {
				EditBrand(EditProduct);
				editComplete = 1;
			}
			else {
				EditPrice(EditProduct);
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

void EditBrand(int recNum) {
	string newBrand;
	Hunt(0, 10);
	cout << "Enter New Brand:";
	Hunt(16, 10);
	getline(cin, newBrand);
	ProductData[recNum][0] = newBrand;
	SaveProduct();

}


void EditPrice(int recNum) {
	string newPrice;
	Hunt(0, 10);
	cout << "Enter New Price:";
	Hunt(19, 10);
	getline(cin, newPrice);
	ProductData[recNum][1] = newPrice;
	SaveProduct();

}
void DeleteProduct(int delProduct) {
	int i;
	int myOffSet = 0;
	string tempProduct[100][2];

	for (i = 0; i < 100; i++) {
		if (i == delProduct) {
			tempProduct[i][0] = ProductData[i + 1][0];
			tempProduct[i][1] = ProductData[i + 1][1];
			myOffSet++;
			i++;
		}
		else {
			tempProduct[i - myOffSet][0] = ProductData[i][0];
			tempProduct[i - myOffSet][1] = ProductData[i][1];
		}
		//prodEnd--;

	}
	ClearProductList();



	i = 0;

	for (i = 0; i < 100; i++) {
		ProductData[i][0] = tempProduct[i][0];
		ProductData[i][1] = tempProduct[i][1];

	}


	SaveProduct();



}

