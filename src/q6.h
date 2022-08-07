#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"functions.h"
using namespace std;

struct q6Data { //STORES DATA FOR Q6
    string date;
    int cases;
};

void q6ReadFromFile(string country1, string country2, vector<q6Data> &A, vector<q6Data> &B) { //READS FROM FILE
    fstream f1("WHO-COVID-19.csv", ios::in);
	string temp;

	if (f1) {
		for (int i = 0; i < 7; ++i) {
			getline(f1, temp, ',');
		}
		getline(f1, temp, '\n');
		
		while (!f1.eof()) {
            int cConfirmed, cDeaths;
            string countryName;
            q6Data d;

			getline(f1, temp, ',');
            d.date = temp;
			getline(f1, temp, ',');
			getline(f1, temp, ',');
            countryName = temp;

            if (countryName[0] == '"') { //HANDLING ERROR IN THE FILE
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

			if (countryName == country1 || countryName == country2) {
                getline(f1, temp, ',');
				getline(f1, temp, ',');
				getline(f1, temp, ',');
                cDeaths = stoi(temp);
				getline(f1, temp, ',');
				getline(f1, temp, '\n');
                cConfirmed = stoi(temp);

                d.cases = cConfirmed - cDeaths;
                if (countryName == country1 && countryName != "undefined") { //EXCLUDING UNDEFINED DATA HERE TOO
                    A.insert(A.end(), d);
                }

                if (countryName == country2 && countryName != "undefined") { //EXCLUDING UNDEFINED DATA HERE TOO
                    B.insert(B.end(), d);
                }
			}

			else {
                if (!A.empty() && !B.empty()) {
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

void LCS(vector<q6Data> c1, vector<q6Data> c2, int size1, int size2, int K, string country1, string country2) { //FINDING SIMILARITY
    int max = 0, start1, end1, start2, end2, size;

    vector<vector<int>> arr;
    for (int i = 0; i < size1 + 1; ++i) {
        vector<int> temp(size2 + 1);
        arr.insert(arr.end(), temp);
    }


    for (int i = 0; i <= size1; ++i) {
        for (int j = 0; j <= size2; ++j) {
            arr[i][j] = 0;
        }
    }

    for (int i = size1 - 1; i >= 0; --i) {  //CALCULATING SIMILARITY
        for (int j = size2 - 1; j >= 0; --j) {
            if (abs(c1[i].cases - c2[j].cases) <= K) {
                arr[i][j] = arr[i + 1][j + 1] + 1;
            }

            if (arr[i][j] > max) {
                max = arr[i][j];
            }
        }
    }

    for (int i = 0; i < size1; ++i) {   //FINDING SIMILARITY
        for (int j = 0; j < size2; ++j) {
            if (arr[i][j] == max) {
                start1 = i;
                start2 = j;
                end1 = i;
                end2 = j;
                i = size1;
                break;
            }
        }
    }

    /*DISPLAYING OUTPUT*/
    while (arr[end1][end2] != 1) {
        end1++;
        end2++;
    }

    cout << endl << "-> Similarity: " << (end1 - start1) + 1 << endl;
    
    size = country1.size();
    if (country1.size() % 2 != 0) {
        size++;
    }

    cout << endl;
    drawLine('-', (59 - size) / 2);
    cout << country1;
    drawLine('-', (59 - country1.size()) / 2);
    cout << "|";
    
    size = country2.size();
    if (country2.size() % 2 != 0) {
        size++;
    }

    drawLine('-', (59 - size) / 2);
    cout << country2;
    drawLine('-', (59 - country2.size()) / 2);
    cout << endl << "DATE";
    drawLine('\t', 4);
    cout << "     ACTIVE CASES";
    drawLine('\t', 1);
    cout << "  |";
    drawLine('\t', 1);
    cout << "DATE";
    drawLine('\t', 4);
    cout << " ACTIVE CASES" << endl;
    drawLine('-', 58);
    cout << "|";
    drawLine('-', 58);
    cout << endl;

    while (arr[start1][start2] != 0) {
        cout << c1[start1].date;
        drawLine(' ', 41 - c1[start1].date.size());
        cout << c1[start1].cases;
        drawLine(' ', 15 - countDigit(c1[start1].cases));
        cout << "  |";
        drawLine(' ', 4);
        cout << c2[start2].date;
        drawLine(' ', 31);
        cout << c2[start2].cases << endl;
        start1++;
        start2++;
    }
    drawLine('-', 58);
    cout << "|";
    drawLine('-', 58);
    cout << endl;
}

void q6() {
    string country1, country2;
    int K;
    vector<q6Data> c1, c2;

    cout << endl;
    cin.ignore();
    cout << "Enter first country name i.e Turkey: ";
    getline(cin, country1);
    cout << "Enter second country name i.e Turkey: ";
    getline(cin,country2);
    cout << "Enter compare threshold K(Must be greater than or equal to zero): ";
    cin >> K;
    while (K < 0) {
        cout << "ENTER COMPARE THRESHOLD K(MUST BE GREATER THAN OR EQUAL TO ZERO): ";
        cin >> K;
    }

    q6ReadFromFile(country1, country2, c1, c2);

    if (!c1.empty() && !c2.empty()) {
        LCS(c1, c2, c1.size(), c2.size(), K, country1, country2);
    }

    else {
        printNoResult();
    }
}