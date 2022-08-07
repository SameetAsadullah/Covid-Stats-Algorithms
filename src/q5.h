#pragma once
#include <iostream> 
#include<vector>
#include<string>
#include<fstream>
#include"functions.h"
using namespace std;

struct q5Data { //STORES DATA FOR Q5
    string countryName;
    int cost, cases;

    q5Data():cost(-1) {
    }
};

void q5readFromFile(vector<q5Data> &v) {    //READS FROM FILE
    fstream f1("WHO-COVID-19.csv", ios::in);

	if (f1) {
        string countryName1, countryName2, temp;

		for (int i = 0; i < 7; ++i) {
			getline(f1, temp, ',');
		}
		getline(f1, temp, '\n');
        getline(f1, temp, ',');
        getline(f1, temp, ',');
        getline(f1, temp, ',');
        countryName1 = temp;

		while (!f1.eof()) {
            q5Data d;
            int cDeaths, cConfirmed;

			getline(f1, temp, ',');
            getline(f1, temp, ',');
            getline(f1, temp, ',');
            cDeaths = stoi(temp);
            getline(f1, temp, ',');
			getline(f1, temp, '\n');
            cConfirmed = stoi(temp);
            getline(f1, temp, ',');
            getline(f1, temp, ',');
            getline(f1, temp, ',');
            countryName2 = temp;

            if (countryName2[0] == '"') {   //HANDLING ERROR IN THE FILE
                string copy = countryName2;
                getline(f1, temp, ',');

                countryName2.clear();
                for (int i = 1; copy[i] != '\0'; ++i) {
                    countryName2 += copy[i];
                    
                }
                countryName2 += ',';
                for (int i = 0; temp[i + 1] != '\0'; ++i) {
                    countryName2 += temp[i];
                }
            }

            if (countryName1 != countryName2) {
                d.countryName = countryName1;
                d.cases = cConfirmed - cDeaths;
                if (d.countryName != "undefined") { //EXCLUDING UNDEFINED DATA
                    v.insert(v.end(), d);
                }
                countryName1 = countryName2;
            }
		}
	}

    else {
        cout << endl << "-> File not opened correctly" << endl;
    }

    f1.close();
    f1.open("CountryWeight.csv", ios::in);

    if (f1) {   //READING COSTS
        string name, cost;

        getline(f1, name, ',');
        getline(f1, cost, '\n');

        while (!f1.eof()) {
            getline(f1, name, ',');
            
            if (name[0] == '"') {
                string temp;
                string copy = name;

                getline(f1, temp, ',');
                name.clear();

                for (int i = 1; copy[i] != '\0'; ++i) {
                    name += copy[i];
                }

                name += ',';
                
                for (int i = 0; temp[i + 1] != '\0'; ++i) {
                    name += temp[i];
                }
            }

            getline(f1, cost, '\n');
           
            for (int i = 0; i < v.size(); ++i) {
                if (v[i].countryName == name) {
                    v[i].cost = stoi(cost);
                    break;
                }
            }
        }
    }

    else {
        cout << endl << "-> File not opened correctly" << endl;
    }
}

int max(int a, int b) { //RETURNS MAX VALUE 
    if (a > b) {
        return a;
    }
    return b;
}

void knapSack(vector<q5Data> v, int size, int weight) { //FINDS HIGHEST POSSIBLE SCORE
    int i, w;
  
    vector<vector<int>> arr;
    for (int i = 0; i < size + 1; ++i) {
        vector<int> temp(weight + 1);
        arr.insert(arr.end(), temp);
    }

    for (i = 0; i <= size; i++) {   //CALCULATING HIGHEST POSSIBLE SCORE
        for (w = 0; w <= weight; w++) {
            if (i == 0 || w == 0) {
                arr[i][w] = 0;
            }

            else if (v[i - 1].cost <= w) {
                arr[i][w] = max(v[i - 1].cases + arr[i - 1][w - v[i - 1].cost], arr[i - 1][w]);
            }

            else {
                arr[i][w] = arr[i - 1][w];
            }
        }
    }

    int temp = arr[size][weight];
    if (temp != 0) { //DISPLAING OUTPUT
        cout << endl << "-> Highest possible score: " << temp << endl;
        w = weight;

        cout << endl;
        drawLine('-', 80);
        cout << endl << "COUNTRY NAME";
        drawLine('\t', 6);
        cout << "   COST";
        drawLine('\t', 1);
        cout << "   ACTIVE CASES" << endl;
        drawLine('-', 80);
        cout << endl;

        for (i = size; i > 0 && temp > 0; i--) {
            if (temp == arr[i - 1][w]) {
                continue;
            }

            else {
                cout << v[i - 1].countryName;
                drawLine(' ', 60 - v[i - 1].countryName.size());
                cout << v[i - 1].cost;
                drawLine(' ', 10 - countDigit(v[i - 1].cost));
                cout << v[i - 1].cases << endl;
                temp = temp - v[i - 1].cases;
                w = w - v[i - 1].cost;
            }
        }
        drawLine('-', 80);
        cout << endl;
    }

    else {
        printNoResult();
    }
}

void q5() { //RUNS Q5
    vector<q5Data> v;
    int weight;

    cout << endl << "Enter Budget(Must be greater than zero): ";
    cin >> weight;

    while (weight <= 0) { //CHECKING INPUT IS VALID OR NOT
        cout << "ENTER BUDGET(MUST BE GREATER THAN ZERO): ";
        cin >> weight;
    }

    q5readFromFile(v);

    if (!v.empty()) {
        for (int i = 0; i < v.size(); ++i) {
            if (v[i].cost == -1) {
                v.erase(v.begin() + i);
            }
        }
        knapSack(v, v.size(), weight);
    }
}