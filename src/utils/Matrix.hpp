#pragma once

#include <iostream>

#include "NiftiExceptions.hpp"

template <class T>
class Matrix {
public:
    Matrix (unsigned int lines, unsigned int cols) {
	_data = new T [(lines * cols) * sizeof (T)];
	_lines = lines;
	_cols = cols;
    }

    ~Matrix () {
	if (_data)
	    delete[] _data;
    }

    T * getDataPtr () {
	return _data;
    }

    unsigned int getLines () const {
	return _lines;
    }

    unsigned int getCols () const {
	return _cols;
    }

    Matrix<T> & operator= (Matrix<T> b) {
	if (_data && (_lines != b.getLines () || _cols != b.getCols ())) {
	    delete[] _data;
	    _lines = b.getLines ();
	    _cols = b.getCols ();
	    _data = new T[(_lines * _cols) * sizeof (T)];
	}

	for (int i = 0; i < _lines * _cols; i++)
	    _data[i] = b[i];
    }

    Matrix<T> operator* (Matrix<T> & b) {
	if (_cols != b.getLines ()) {
	    // throw ImpossibleMulOperation (_lines, b.getCols ());
	    std::cout << "Impossible mul operation : A.cols = " << std::to_string (_cols) << ", B.lines = " << std::to_string (b.getLines ()) << std::endl;
	    throw -1;
	}

	int bLines = b.getLines ();
	int bCols = b.getCols ();
	Matrix<T> res (bLines, bCols);
	int linRes = 0, colRes = 0;

	for (int linA = 0; linA < _lines; linA++) {
	    for (int colB = 0; colB < b.getCols (); colB++) {
		int linB = 0;
		for (int colA = 0; colA < _cols; colA++) {
		    res[colRes + (linRes * bCols)] += _data[colA + (linA * _cols)] * b[colB + (linB * bCols)];
		    linB++;
		}
		colRes++;
	    }
	    linRes++;
	    colRes = 0;
	}
	
	return res;
    }

    Matrix<T> operator+ (Matrix<T> & b) {
	if (_lines != b.getLines () || _cols != b.getCols ()) {
	    std::cout << "Impossible sum operation ! A.lines = " << std::to_string (_lines) << ", A.cols = " << std::to_string (_cols) << ", B.lines = " << std::to_string (b.getLines ()) << ", B.cols = " << std::to_string (b.getCols ()) << std::endl;
	    throw -1;
	}

	Matrix<T> res (_lines, _cols);

	for (int i = 0; i < _lines * _cols; i++)
	    res[i] = _data[i] + b[i];

	return res;
    }

    Matrix<T> hadamProduct (Matrix<T> & b) {
	if (_lines != b.getLines () || _cols != b.getCols ()) {
	    std::cout << "Impossible sum operation ! A.lines = " << std::to_string (_lines) << ", A.cols = " << std::to_string (_cols) << ", B.lines = " << std::to_string (b.getLines ()) << ", B.cols = " << std::to_string (b.getCols ()) << std::endl;
	    throw -1;
	}

	Matrix<T> res (_lines, _cols);

	for (int i = 0; i < _lines * _cols; i++)
	    res[i] = _data[i] * b[i];

	return res;	
    }

    T & operator[] (unsigned int index) {
	if (index >= (_lines * _cols)) {
	    std::cout << "Index out of bounds : " << std::to_string (index) << std::endl;
	    throw -1;
	    // throw OutOfBoundException (index);
	}
	return _data[index];
    }

    void print () {
	for (int i = 0; i < _lines; i++) {
	    for (int j = 0; j < _cols; j++) {
		std::cout << _data[j + (i * _cols)] << " ";
	    }
	    std::cout << std::endl;
	}
    }

private:
    T * _data;
    unsigned int _lines;
    unsigned int _cols;
};
