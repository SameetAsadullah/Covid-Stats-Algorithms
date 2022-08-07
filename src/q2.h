#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include"functions.h"
using namespace std;

struct q2Data {	//STORES DATA FOR Q2
	string countryName;
	int newCases;
};

struct q2CompareCases {	//USED TO COMPARE CASES IN HEAP
	bool operator()(q2Data const& d1, q2Data const& d2) {
		return d1.newCases < d2.newCases;
	}
};

bool compareDates(string date1, string date2) {	//RETURNS TRUE IF DATE1 IS BEFORE DATE2 OTHERWISE FALSE
	int day1, month1, year1, day2, month2, year2;
	int date1Int, date2Int;
	string temp1 = "", temp2 = "";

	for (int i = 0; i < 4; ++i) {	
		temp1 += date1[i];
		temp2 += date2[i];
	}

	year1 = stoi(temp1);
	year2 = stoi(temp2);

	temp1.clear();
	temp2.clear();
	
	for (int i = 5; i < 7; ++i) {
		temp1 += date1[i];
		temp2 += date2[i];
	}

	month1 = stoi(temp1);
	month2 = stoi(temp2);

	temp1.clear();
	temp2.clear();
	
	for (int i = 8; i < 10; ++i) {
		temp1 += date1[i];
		temp2 += date2[i];
	}

	day1 = stoi(temp1);
	day2 = stoi(temp2);

	date1Int = (year1 * 10000) + (month1 * 100) + day1;
	date2Int = (year2 * 10000) + (month2 * 100) + day2;

	if (date1Int < date2Int) {
		return true;
	}
	else {
		return false;
	}
}

void q2ReadFromFile(priority_queue<q2Data, vector<q2Data>, q2CompareCases>& pQ, string lowerDate, string higherDate) {	//READS FROM FILE
	fstream f1("WHO-COVID-19.csv", ios::in);
	string temp;

	if (f1) {
		int oldCases, cases;
		string oldCountry, date;

		for (int i = 0; i < 7; ++i) {
			getline(f1, temp, ',');
		}
		getline(f1, temp, '\n');
		
		while (!f1.eof()) {
			q2Data d;

			getline(f1, temp, ',');
			date = temp;
			getline(f1, temp, ',');
			getline(f1, temp, ',');
			d.countryName = temp;
			
			if (d.countryName[0] == '"') {	//HANDLING ERRORS IN THE FILE
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
			getline(f1, temp, '\n');
			cases = stoi(temp);

			if (date == lowerDate) {
				oldCountry = d.countryName;
				oldCases = cases;
			}

			if (date == higherDate) {
				if (oldCountry == d.countryName) {
					d.newCases = cases - oldCases;
					if (oldCountry != "undefined") {	//EXCLUDING UNDEFINED DATA
						pQ.push(d);
					}
					oldCountry.clear();
				}
			}
		}
	}

	else {
		cout << endl << "-> File not opened correctly" << endl;
	}
}

void q2() {	//RUNS Q2
	string date1, date2;
	priority_queue<q2Data, vector<q2Data>, q2CompareCases> pQ;

	cout << endl;
	while (true) {	//CHECKING INPUT WHETHER ITS VALID OR NOT
		cout << "Enter first date(yyyy-mm-dd). It must be any date before second date: ";
		cin >> date1;
		while (!checkInput(date1)) {
			cout << "ENTER FIRST DATE(MUST BE BEFORE SECOND DATE) IN CORRECT FORMAT(YYYY-MM-DD): ";
			cin >> date1;
		}

		cout << "Enter second date(yyyy-mm-dd). It must be any date after first date: ";
		cin >> date2;
		while (!checkInput(date2)) {
			cout << "ENTER SECOND DATE(MUST BE AFTER FIRST DATE) IN CORRECT FORMAT(YYYY-MM-DD): ";
			cin >> date2;
		}

		if (!compareDates(date1, date2)) {
			cout << endl << "-> FIRST DATE MUST BE ANY DATE BEFORE SECOND DATE. ENTER DATES AGAIN NOW." << endl << endl;
		}

		else {
			break;
		}
	}

	q2ReadFromFile(pQ, date1, date2);

	if (!pQ.empty()) { //DISPLAYING OUTPUT
		q2Data temp = pQ.top();
		cout << endl;
		drawLine('-', 80);
		cout << endl << "COUNTRY NAME";
		drawLine('\t', 6);
		cout << "      HIGHEST NEW CASES" << endl;
		drawLine('-', 80);
		cout << endl;
		
		cout << temp.countryName;
		drawLine(' ', 63 - temp.countryName.size());
		cout << temp.newCases << endl;
		pQ.pop();

		while (pQ.top().newCases == temp.newCases) {
			temp = pQ.top();
			cout << temp.countryName;
			drawLine(' ', 63 - temp.countryName.size());
			cout << temp.newCases << endl;
			pQ.pop();
		}
		drawLine('-', 80);
		cout << endl;
	}

	else {
		printNoResult();
	}
}