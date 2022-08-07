#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stack>
#include"functions.h"
using namespace std;

struct q3Data {	//STROES DATA FOR Q3
	string date;
	int newCases;
};

void q3ReadFromFile(string country, vector<q3Data> &v) { //READS FROM FILE
	fstream f1("WHO-COVID-19.csv", ios::in);
	string temp;

	if (f1) {
		bool check = false;

		for (int i = 0; i < 7; ++i) {
			getline(f1, temp, ',');
		}
		getline(f1, temp, '\n');
		
		while (!f1.eof()) {
			q3Data d;
			string countryName;

			getline(f1, temp, ',');
			d.date = temp;
			getline(f1, temp, ',');
			getline(f1, temp, ',');
			countryName = temp;

			if (countryName[0] == '"') { //HANDLING ERRORS IN THE FILE
				string copy = countryName;
				getline(f1, temp, ',');

				countryName.clear();
				for (int i = 1; copy[i] != '\0'; ++i) {
					countryName += copy[i];

				}
				countryName += ',';
				for (int i = 0; temp[i + 1] != '\0'; ++i) {
					countryName += temp[i];
				}
			}

			if (countryName == country && countryName != "undefined") { //EXCLUDING UNDEFINED DATA HERE TOO
				getline(f1, temp, ',');
				getline(f1, temp, ',');
				getline(f1, temp, ',');
				getline(f1, temp, ',');
				d.newCases = stoi(temp);
				getline(f1, temp, '\n');
				check = true;
				v.insert(v.end(), d);
			}

			else {
				if (check == true) {
					break;
				}

				for (int i = 0; i < 4; ++i) {
					getline(f1, temp, ',');
				}
				getline(f1, temp, '\n');
			}
		}
	}

	else {
		cout << endl << "-> File not opened correctly" << endl;
	}
	return;
}

void LIS(vector<int> arr, int size, int &start, int &end, stack<int> &s) { //FINDS LONGEST SPREAD PERIOD
	vector<int> LIS(size);
	int max = 1;
	bool check = true;

    LIS[0] = 1;
    
    for (int i = 1; i < size; ++i) { //CALCULATING LONGEST SPREAD PERIOD
        LIS[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j] && LIS[i] < LIS[j] + 1) {
                LIS[i] = LIS[j] + 1;
            }
        }

        if (LIS[i] > max) {
            max = LIS[i];
        }
    }

	for (int i = size - 1; i >= 0; --i) {	//FINDING LONGEST SPREAD PERIOD
		if (check == true && LIS[i] == max) {
			end = i;
			check = false;
			max--;
			s.push(i);
		}

		else if (LIS[i] == 1 && end != -1 && (max - 1) == 0) {
			start = i;
			s.push(i);
			return;
		}

		else if (LIS[i] == max) {
			s.push(i);
			max--;
		}
	}
}

void q3() {	//RUNS Q3
	string countryName;
	vector<q3Data> v;
	stack<int> s;
	int start = -1, end = -1;

	cin.ignore();
	cout << endl << "Enter country name i.e Turkey: ";
	getline(cin, countryName);
	
	q3ReadFromFile(countryName, v);

	vector<int> arr(v.size());

	for (int i = 0; i < v.size(); ++i) {
		arr[i] = v[i].newCases;
	}

	if (!v.empty()) { //DISPLAYING OUTPUT
		LIS(arr, v.size(), start, end, s);
		cout << endl << "-> " << countryName << " has a longest spread period elapsing " << (end - start) + 1;
		cout << " days from day " << start + 1 << " (" << v[start].newCases << ")";
		cout << " to day " << end + 1 << " (" << v[end].newCases << ")" << endl;

		cout << endl;
		drawLine('-', 80);
		cout << endl << "DATE";
		drawLine('\t', 3);
		cout << "DAY #";
		drawLine('\t', 3);
		cout << "NEW CASES" << endl;
		drawLine('-', 80);
		cout << endl;

		while (!s.empty()) {
			cout << v[s.top()].date;
			drawLine(' ', 25 - v[s.top()].date.size());
			cout << s.top() + 1;
			drawLine(' ', 24 - countDigit(s.top() + 1));
			cout << arr[s.top()] << endl;
			s.pop();
		}
		drawLine('-', 80);
		cout << endl;
	}

	else {
		printNoResult();
	}
}
