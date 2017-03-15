#pragma once

#include <iostream>

namespace NR {
    class NiftiException {
    public:
	NiftiException () {}
	NiftiException (std::string msg) throw () : _msg (msg) {}

	virtual std::string toString () const {
	    return "[!] Nifti Reader Error : " + _msg + ".";
	}
	
    protected:
	std::string _msg;
    };

    class FileNotFoundException : public NiftiException {
    public:
	FileNotFoundException (std::string file_name) throw () {
	    _msg = "file " + file_name + " not found";
	}
    };

    class HeaderErrorException : public NiftiException {
    public:
	HeaderErrorException () throw () : NiftiException ("Enable to read header") {}
    };

    class MatrixException : public NiftiException {
    public:
	MatrixException () throw () : NiftiException ("Matrix error") {}
    };

    class ImpossibleMulOperation : public MatrixException {
    public:
	ImpossibleMulOperation (unsigned int lines, unsigned int cols) throw () {
	    _msg = "Matrix, can't multiply two matrix with the following dimensions : A.lines = " + std::to_string (lines)  + ", B.columns = " + std::to_string (cols);
	}
    };

    class OutOfBoundException : public MatrixException {
    public:
	OutOfBoundException (unsigned int index) throw () {
	    _msg = "Matrix, index out of bound : " + std::to_string (index);
	} 
    };
};
