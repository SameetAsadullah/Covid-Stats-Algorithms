#include"q1.h"
#include"q2.h"
#include"q3.h"
#include"q4.h"
#include"q5.h"
#include"q6.h"
#include"functions.h"
using namespace std;

void displayMenu() {
	cout << endl << "Enter the corresponding number of the query." << endl << endl;
	cout << "1- Top 20 countries with the most confirmed cases on a given day." << endl;
	cout << "2- Highest new cases between two given dates." << endl;
	cout << "3- Longest spread period for a given country." << endl;
	cout << "4- Longest daily death toll decrease period for a given country." << endl;
	cout << "5- Highest possible score attainable for aid." << endl;
	cout << "6- Compare the response of any two countries against the virus." << endl;
	cout << "0- Exit" << endl;
}

int main() {
	int input = 0;
	
	drawLine('=', 35);
	cout << " COVID STATISTICS MENU ";
	drawLine('=', 35);
	cout << endl;

	while (true) {
		displayMenu();
		cin >> input;

		while (input < 0 || input > 6) {
			cout << endl << "----------Enter valid input please----------";
			displayMenu();
			cin >> input;
		}

		if (input == 0) {
			break;
		}

		else if (input == 1) {
			q1();
		}

		else if (input == 2) {
			q2();
		}

		else if (input == 3) {
			q3();
		}

		else if (input == 4) {
			q4();
		}

		else if (input == 5) {
			q5();
		}

		else if (input == 6) {
			q6();
		}
	}
}