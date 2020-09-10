/*
// file: DorianBenitez_HW41.cpp
// author: Dorian Benitez (drb160130)
// date: 2/16/2020
// purpose: CS 4375.501 - Homework #4 (Logistic Regression)
// 
// This .cpp file is for Homework 4 - Logistic regression of Intro to Machine Learning with instructor Karen Mazidi. This program will read a csv 
// and perform logistic regression on the data.
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


float sigmoid(float z) {
	return	1 / (1 + exp(-z));
}

int main() {
	ifstream inputFile("plasma.csv");
	string fibStr;
	string esrStr;
	mat DataMatrix(32, 2);
	mat fib(32,1);
	mat esr(32, 1);
	mat labels(32, 1);

	if (inputFile.is_open()) {
		for (int i =0; i < 32 ; i ++) {
			
			// Reads lines from the CSV file
			getline(inputFile, fibStr, ',');
			getline(inputFile, esrStr, '\n');


			// Converts string values to float values
			float fib_val = stof(fibStr);
			float esr_val = stof(esrStr);
		

			// Creates matrices of the values from the CSV file
			fib(i, 0) = fib_val;
			esr(i, 0) = esr_val;

			DataMatrix(i, 0) = 1;
			DataMatrix(i, 1) = fib_val;

			labels(i, 0) = (esr_val);
		}
	}


	else {
		cout << "File cannot be opened" << endl;
	}

	mat weights(2, 1,fill::ones);

	float learning_rate = 0.001;

	float startTime = clock();
	
	// Loop to match that in R
	for (int i = 0; i < 500000; i++) {
		mat probVec= DataMatrix * weights;
		for (int j =0; j<32; j++) {
			probVec(j) = sigmoid(probVec(j));
		}
		mat error = labels - probVec;
		weights = weights + learning_rate * DataMatrix.t() * error;
	}
	float endTime = clock();
	
	cout << "Weights after looping" << endl;
	weights.print();
	cout << "Run time of loop: " << (endTime - startTime) / CLOCKS_PER_SEC << endl;
}


