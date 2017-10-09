// MatrixClass4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;



template <class T>
class Matrix {
public:
	vector<vector<T>> M; // Matrix

	Matrix<T> Transpose();

	Matrix<T> operator+(Matrix<T> &B); // Matrix addition
	Matrix<T> operator*(Matrix<T> &B); // Matrix multiplication

	void PrintMatrix();
};

template <class T>
vector<T> AddTwoVectors(vector<T> v1, vector<T> v2) {
	vector<T> v3 (v1.size());
	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), plus<T>());
	return v3;
}

template <class T>
T VectorDotProduct(vector<T> v1, vector<T> v2) {
	vector<T> v3 (v1.size());
	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), multiplies<T>());
	return accumulate(v3.begin(), v3.end(), 0.0);
}

template <class T>
Matrix<T> Matrix<T>::Transpose() {
	Matrix<T> Tr;
	vector<T> EmptyVector;
	for (int i = 0; i < this->M[0].size(); i++) {
		Tr.M.push_back(EmptyVector);
		for (int j = 0; j < this->M.size(); j++) {
			Tr.M[i].push_back(M[j][i]);
		}
	}
	return Tr;
}

template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T> &B) {
	Matrix<T> C;
	for (int i = 0; i < B.M.size(); i++) {
		C.M.push_back(AddTwoVectors(this->M[i], B.M[i]));
	}
	return C;
}

template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> &B) {
	Matrix<T> C;
	vector<T> EmptyVector;
	Matrix<T> Bt = B.Transpose();
	for (int i = 0; i < this->M.size(); i++) {
		C.M.push_back(EmptyVector);
		for (int j = 0; j < B.M.size(); j++) {
			C.M[i].push_back(VectorDotProduct(this->M[i], Bt.M[j]));
		}
	}
	return C;
}

template <class T>
void Matrix<T>::PrintMatrix() {
	int nrows = this->M.size();
	int ncols = this->M[0].size();
	for (int row = 0; row < nrows; row++) {
		for (int col = 0; col < ncols; col++) {
			cout << this->M[row][col] << ",";
		}
		cout << "\n";
	}
}


int main()
{
	Matrix<double> A;
	A.M = { {1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0} };
	A.PrintMatrix();
	Matrix<double> B;
	B.M = { { 1.0,0.0,0.0 },{ 0.0,1.0,0.0 },{ 0.0,0.0,1.0 } };
	B.PrintMatrix();
	(A + B).PrintMatrix();
	B.Transpose().PrintMatrix();
	(A*B).PrintMatrix();
	system("pause");
    return 0;
}

