#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include"functions.h"
using namespace std;

struct q1Data {	//STORES DATA FOR Q1
	string countryName;
	int confirmedCases;
};

struct q1CompareCases {	//USED TO COMPARE CASES IN HEAP
	bool operator()(q1Data const& d1, q1Data const& d2) {
		return d1.confirmedCases < d2.confirmedCases;
	}
};

void q1ReadFromFile(priority_queue<q1Data, vector<q1Data>, q1CompareCases>& pQ, string date) { //READS DATA FROM THE FILE
	fstream f1("WHO-COVID-19.csv", ios::in);
	string temp;

	if (f1) {
		while (!f1.eof()) {
			q1Data d;

			getline(f1, temp, ',');
			if (temp == date) {
				getline(f1, temp, ',');
				getline(f1, temp, ',');
				d.countryName = temp;

				if (d.countryName[0] == '"') {	//HANDLING ERROR IN THE FILE
					string copy = d.countryName;
					getline(f1, temp, ',');

					d.countryName.clear();
					for (int i = 1; copy[i] != '\0'; ++i) {
						d.countryName += copy[i];

					}
					d.countryName += ',';
					for (int i = 0; temp[i + 1] != '\0'; ++i) {
						d.countryName += temp[i];
					}
				}

				getline(f1, temp, ',');
				getline(f1, temp, ',');
				getline(f1, temp, ',');
				getline(f1, temp, ',');
				d.confirmedCases = stoi(temp);
				getline(f1, temp, '\n');

				if (d.countryName != "undefined") {	//EXCLUDING UNDEFINED DATA
					pQ.push(d);
				}
			}

			else {
				for (int i = 0; i < 6; ++i) {
					getline(f1, temp, ',');
				}
				getline(f1, temp, '\n');
			}
		}
	}

	else {
		cout << endl << "-> File not opened correctly" << endl;
	}
}

void q1() {	//RUNS Q1
	string date;

	cout << endl << "Enter Date(yyyy-mm-dd): ";
	cin >> date;
	while (!checkInput(date)) {	//CHECKING INPUT THAT WHETHER IT IS CORRECT OR NOT
		cout << "ENTER DATE IN CORRECT FORMAT(YYYY-MM-DD): ";
		cin >> date;
	}

	priority_queue<q1Data, vector<q1Data>, q1CompareCases> pQ;
	q1ReadFromFile(pQ, date);

	if (!pQ.empty()) {	//DISPLAYING OUTPUT
		cout << endl;
		drawLine('-', 80);
		cout << endl << "COUNTRY NAME";
		drawLine('\t', 7);
		cout << "CONFIRMED CASES" << endl;
		drawLine('-', 80);
		cout << endl;
		for (int i = 0; i < 20; ++i) {
			if (!pQ.empty()) {
				q1Data temp = pQ.top();
				cout << temp.countryName;
				drawLine(' ', 65 - temp.countryName.size());
				cout << temp.confirmedCases << endl;
				pQ.pop();
			}
		}
		drawLine('-', 80);
		cout << endl;
	}

	else {
		printNoResult();
	}

	return;
}