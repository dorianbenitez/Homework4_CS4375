/*
// file: DorianBenitez_HW42.cpp
// author: Dorian Benitez (drb160130)
// date: 2/16/2020
// purpose: CS 4375.501 - Homework #4 (Naive Bayes)
// 
// This .cpp file is for Homework 4 - Naive Bayes of Intro to Machine Learning with instructor Karen Mazidi. This program will read a csv 
// and perform Naive Bayes Classification on the data.
// 
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;

int main() {
	ifstream ip("titanic_project.csv");

	string pClassStr;
	string survivedStr;
	string sexStr;
	string ageStr;

	// Initialize the train and test data sets 
	mat train(900, 4);
	mat test(146, 4);

	if (ip.is_open()) {
		for (int i = 0; i < 900; i++) {
				// This will read the lines from the csv file
				getline(ip, pClassStr, ',');
				getline(ip, survivedStr, ',');
				getline(ip, sexStr, ',');
				getline(ip, ageStr, '\n');

				// Will convert string values to float values
				float pclass_val = stof(pClassStr);
				float survived_val = stof(survivedStr);
				float sex_val = stof(sexStr);
				float age_val = stof(ageStr);

				// Will insert the values into the train data set
				train(i, 0) = pclass_val;
				train(i, 1) = survived_val;
				train(i, 2) = sex_val;
				train(i, 3) = age_val;
		}

		for (int i = 0; i < 146; i++) {
			// Will read the lines from the csv file
			getline(ip, pClassStr, ',');
			getline(ip, survivedStr, ',');
			getline(ip, sexStr, ',');
			getline(ip, ageStr, '\n');

			// Will convert string values to float values
			float pclass_val = stof(pClassStr);
			float survived_val = stof(survivedStr);
			float sex_val = stof(sexStr);
			float age_val = stof(ageStr);

			// Will insert the values into the test data set
			test(i, 0) = pclass_val;
			test(i, 1) = survived_val;
			test(i, 2) = sex_val;
			test(i, 3) = age_val;
		}
	}

	else {
		cout << "Error opening file." << endl;
	}

	float survivedY = 0;        // Variable for the survivors
	float survivedN = 0;		// Variable for non-survivors

	for (int i = 0; i < 900; i++) {
		if (train(i, 1) == 1) 
			survivedY++;	
		else
			survivedN++;
	}

	//likelihood for pClass and survival
	mat lh_pclass(2, 3);

	//likelihood for sex and survival
	mat lh_sex(2, 2);

	//likelihood for age and survival
	mat age_mean(1, 2,fill::zeros);
	mat age_var(1, 2, fill::zeros);
	age_mean;

	// This will print the data
	cout << "Train data: " << endl;
	train.print();
	cout << "NUMBER OF ROWS in train: " << train.n_rows << endl;

	cout << "Test data: " << endl;
	test.print();
	cout << "NUMBER OF ROWS in test: " << test.n_rows << endl;

	cout << "Numver of survivors is: " << survivedY << "     Number of non-survivors is: " << survivedN << endl;
	
	float aprioriY = survivedY / 900;
	float aprioriN = survivedN / 900;

	mat apriori(1, 2);
	apriori(0, 0) = aprioriY;
	apriori(0, 1) = aprioriN;

	apriori.print();
	age_mean.print();
}

