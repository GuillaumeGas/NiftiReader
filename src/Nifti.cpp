#include "Nifti.hpp"

using namespace std;
using namespace NR;

Nifti::Nifti (string fileName) {
    _fileName = fileName;
    _file = fopen (_fileName.c_str (), "r");

    if (!_file)
	throw FileNotFoundException (fileName);

    _readHeader ();
}

Nifti::~Nifti () {
    if (_file)
	fclose (_file);
}

void Nifti::_readHeader () {
    if (fread (&_header, NIFTI_HEADER_SIZE, 1, _file) != 1) // 1 represents the number of elements (one element = NIFTI_HEADER_SIZE bytes)
	throw HeaderErrorException ();
}

void Nifti::headerDump () const {
    cout << "/------ Nifti file : " << _fileName << " - Header ------\\" << endl;
    cout << " - Header size : " << _header.sizeof_hdr << endl;
}
