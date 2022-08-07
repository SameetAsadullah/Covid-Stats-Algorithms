/*IMPORTANT FUNCTIONS USED IN ALL FILES*/
#pragma once
#include<iostream>
#include<string>
using namespace std;

void drawLine(char c, int count) {	//DRAWS CHARACTERS ON THE TERMINAL
	for (int i = 0; i < count; ++i) {
		cout << c;
	}
}

bool checkInput(string date) {	//CHECKS DATE INPUT
	for (int i = 0; date[i] != '\0'; ++i) {
		if (date[i] == '-') {
			if (i != 4 && i != 7) {
				return false;
			}
		}
		else {
			if (date[i] < '0' || date[i] > '9') {
				return false;
			}
		}

		if (i > 9) {
			return false;
		}
	}
}

int countDigit(int n) {	//COUNTS DIGITS OF THE INTEGER PASSED
	int count = 0;

	while (n != 0) {
		n = n / 10;
		++count;
	}
	return count;
}

void printNoResult() {	//PRINTS OUTPUT IF NO RESULT FOUND
	cout << endl;
	drawLine('-', 80);
	cout << endl;
	drawLine(' ', 32);
	printf("No result found\n");
	drawLine('-', 80);
	cout << endl;
}