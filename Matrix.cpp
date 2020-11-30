#include "Matrix.h"

// Constructor (all elements initialized to 0)
Matrix::Matrix(uint rows, uint cols): rowNumber(rows), columnNumber(cols), matrixValue(new double * [rowNumber]) {
    for (uint i = 0; i < rowNumber; i++) {
        this -> matrixValue[i] = new double[columnNumber];
    }
}

// constructor (must make a copy of the passed in array)
Matrix::Matrix(double** values, int w, int h) {
    for (int j = 0; j < w; ++j) {
        for (int k = 0; k < h; ++k) {
            matrixValue[j][k] = values[j][k];
        }
    }
}

// copy constructor
Matrix::Matrix(const Matrix & m): Matrix::Matrix(m.numRows(), m.numCols()) {
    for(uint j = 0; j < rowNumber; j++) {
        for (uint k = 0; k < columnNumber; k++) {
            matrixValue[j][k] = m.at(j, k);
        }
    }
}

 // destructor
Matrix::~Matrix() {
    for (uint l = 0; l < rowNumber; l++){
        delete[] matrixValue[l];
    }
    delete[] matrixValue;
}

// add scalar to this matrix
Matrix Matrix::add(double s) const {
    Matrix temporaryMatrix(*this);
    for (uint j = 0; j < rowNumber; j++) {
        for (uint k =0; k < columnNumber; k++) {
            temporaryMatrix.at(j, k) = this->at(j, k) + s;
        }
    }
    return temporaryMatrix;
}

// add this matrix and another matrix
Matrix Matrix::add(const Matrix & m) const {
    Matrix temporaryMatrixAgain(*this);
    if (rowNumber == m.numRows() && columnNumber == m.numCols()) {
        for (uint j = 0; j < rowNumber; j++) {
            for (uint k = 0; k < columnNumber; k++) {
                temporaryMatrixAgain.at(j, k) = this->at(j, k) + m.at(j, k);
            }
        }
        return temporaryMatrixAgain;
    } else {
        Matrix sameMatrix(*this);
        return sameMatrix;
    }
}

// subtract scalar from this matrix
Matrix Matrix::subtract(double s) const {
    Matrix temporaryMatrix(*this);
    for (uint j = 0; j < rowNumber; j++) {
        for (uint k = 0; k < columnNumber; k++) {
            temporaryMatrix.at(j, k) = this->at(j, k) - s;
        }
    }
    return temporaryMatrix;
}

// subtract another matrix from this matrix
Matrix Matrix::subtract(const Matrix & m) const {
    Matrix temporaryMatrixAgain(*this);
    if (rowNumber == m.numRows() && columnNumber == m.numCols()) {
        for (uint j = 0; j < rowNumber; j++) {
            for (uint k = 0; k < columnNumber; k++) {
                temporaryMatrixAgain.at(j, k) = this->at(j, k) - m.at(j, k);
            }
        }
        return temporaryMatrixAgain;
    } else {
        Matrix sameMatrixAgain(*this);
        return sameMatrixAgain;
    }
}

// multiply this matrix by a scalar
Matrix Matrix::multiply(double s) const {
    Matrix temporaryMatrix(*this); 
    for (uint j = 0; j < rowNumber; j++) {
        for (uint k = 0; k < columnNumber; k++) {
            temporaryMatrix.at(j, k) *= s;
        }
    }
    return temporaryMatrix;
}

// multiply this matrix by another matrix
Matrix Matrix::multiply(const Matrix & m) const {
    if(columnNumber == m.numRows()){
        Matrix temporaryMatrixAgain (rowNumber,m.numCols());
        for (uint j = 0; j < rowNumber; j++) {
            for (uint k = 0; k <m.numCols(); k++) {
                double total = 0;
                for (uint l = 0; l < m.numRows(); l++) {
                    total += matrixValue[j][l]*m.at(l,k);
                }
                temporaryMatrixAgain.at(j,k) = total;
            }
        }
        return temporaryMatrixAgain;
    } else {
        Matrix temporaryValue(0,0);
        return temporaryValue;
    }
}

// divide this matrix by a scalar
Matrix Matrix::divide(double s) const {
    Matrix temporaryMatrix(*this);
    for (uint j = 0; j < rowNumber; j++) {
        for (uint k = 0; k < columnNumber; k++) {
            temporaryMatrix.at(j, k) = this->at(j,k) / s;
        }
    }
    return temporaryMatrix;
}

// transpose of this matrix
Matrix Matrix::t() const {
    Matrix temporaryMatrixAgain(columnNumber, rowNumber);
    for (uint j = 0; j < rowNumber; j++) {
        for (uint k = 0; k < columnNumber; k++) {
            temporaryMatrixAgain.at(k, j) = this->at(j, k);
        }
    }
    return temporaryMatrixAgain;
}

// returns the number of rows
const uint Matrix::numRows() const {
    return rowNumber;
}

// returns the number of cols
const uint Matrix::numCols() const {
    return columnNumber;
}

// get/set element at row,col
double & Matrix::at(uint row, uint col) {
    return matrixValue[row][col];
}

// get element at row,col (when using a const object)
const double & Matrix::at(uint row, uint col) const {
    return matrixValue[row][col];
}

// The rest of this body code will be for overloading functions

double& Matrix::operator()(uint row, uint col) {
    return this->at(row, col);
}

Matrix& Matrix::operator=(const Matrix & m) {
    for (uint j = 0; j < rowNumber; j++) {
        delete[] matrixValue[j];
    }
    delete[] matrixValue;

    this->rowNumber = m.numRows();
    this->columnNumber = m.numCols();

    this->matrixValue = new double * [this->rowNumber];

    for (uint k = 0; k < this->rowNumber; k++) {
        this->matrixValue[k] = new double [this->columnNumber];
        for (uint l = 0; l < this->columnNumber; l++) {
            this->at(k, l) = m.at(k, l);
        }
    }
    return *this;
}

// This part of the body will now return the non-member operators in Matrix.h
Matrix operator+(const Matrix & m, double s) {
    return m.add(s);
}

Matrix operator+(double otherS, const Matrix & m) {
    return m.add(otherS);
}

Matrix operator+(const Matrix & m, const Matrix & m2) {
    return m.add(m2);
}

Matrix operator-(const Matrix & m, double s) {
    return m.subtract(s);
}

Matrix operator-(double otherS, const Matrix & m) {
    return m.multiply(-1) + otherS;
}

Matrix operator-(const Matrix & m, const Matrix & m2) {
    return m.subtract(m2);
}

Matrix operator*(const Matrix & m, double s) {
    return m.multiply(s);
}

Matrix operator*(double otherS, const Matrix & m) {
    return m.multiply(otherS);
}

Matrix operator*(const Matrix & m, const Matrix & m2) {
    return m.multiply(m2);
}

Matrix operator/(const Matrix & m, double s) {
    return m.divide(s);
}

Matrix operator/(double otherS, const Matrix & m) {
    Matrix temporaryMatrixAgain(m.numRows(), m.numCols());
    for (uint j = 0; j < m.numRows(); j++) {
        for (uint k = 0; k < m.numCols(); k++) {
            temporaryMatrixAgain(j, k) = (otherS / m.at(j, k));
        }
    }
    return temporaryMatrixAgain;
}

ostream& operator<<(ostream& results, const Matrix & m) {
    for (uint k = 0; k < m.numRows(); k++) {
        results << "[ ";
        for (uint l = 0; l < m.numCols(); l++) {
            results << m.at(k, l);
            if (l < m.numCols() -1) { 
                results << ", "; 
            }
        }
        results << " ]" << "\n";
    }
    return results;
}
