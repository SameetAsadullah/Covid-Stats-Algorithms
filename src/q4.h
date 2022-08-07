#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stack>
#include"functions.h"
using namespace std;

struct q4Data {	//STORES DATA FOR Q4
	string date;
	int deaths;
};

void q4ReadFromFile(string country, vector<q4Data> &v) {	//READS FROM FILE
	fstream f1("WHO-COVID-19.csv", ios::in);
	string temp;

	if (f1) {
		bool check = false;

		for (int i = 0; i < 7; ++i) {
			getline(f1, temp, ',');
		}
		getline(f1, temp, '\n');
		
		while (!f1.eof()) {
			q4Data d;
			string countryName;

			getline(f1, temp, ',');
			d.date = temp;
			getline(f1, temp, ',');
			getline(f1, temp, ',');
			countryName = temp;

			if (countryName[0] == '"') {	//HANDLING ERROR IN THE FILE
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
				d.deaths = stoi(temp);
				getline(f1, temp, ',');
				getline(f1, temp, ',');
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

void LDS(vector<int> arr, int size, stack<int> &s, int &period) { //FINDS DEATH TOLL DECREASE PERIOD
	vector<int> LDS(size);
	int max = 1;

    LDS[0] = 1;
    
    for (int i = 1; i < size; ++i) {	//CALCULATING DEATH TOLL DECREASE PERIOD
        LDS[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (arr[i] < arr[j] && LDS[i] < LDS[j] + 1) {
                LDS[i] = LDS[j] + 1;
            }
        }

        if (LDS[i] > max) {
            max = LDS[i];
        }
    }

	period = max;

	for (int i = size - 1; i >= 0; --i) { //FINDING DEATH TOLL DECREASE PERIOD
		if (LDS[i] == max) {
			s.push(i);
			max--;
		}
	}
}

void q4() { //RUNS Q4
	string countryName;
	vector<q4Data> v;
	stack<int> s;
	int period;

	cin.ignore();
	cout << endl << "Enter country name i.e Turkey: ";
	getline(cin, countryName);

	q4ReadFromFile(countryName, v);

	vector<int> arr(v.size());

	for (int i = 0; i < v.size(); ++i) {
		arr[i] = v[i].deaths;
	}

	if (!v.empty()) { //DISPLAYING OUTPUT
		LDS(arr, v.size(), s, period);
		cout << endl;
		cout << "-> " << countryName << " has a longest daily death toll decrease period of " << period << endl;
		
		cout << endl;
		drawLine('-', 80);
		cout << endl << "DATE";
		drawLine('\t', 3);
		cout << "DAY #";
		drawLine('\t', 3);
		cout << "DEATHS" << endl;
		drawLine('-', 80);
		cout << endl;

		while (!s.empty()) {
			cout << v[s.top()].date;
			drawLine(' ', 25 - v[s.top()].date.size());
			cout << s.top() + 1;
			drawLine(' ', 25 - countDigit(s.top() + 1));
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