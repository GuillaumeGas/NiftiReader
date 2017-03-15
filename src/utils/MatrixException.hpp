#pragma once

#include <iostream>

class MatrixException {
public:
    MatrixException () {}
    MatrixException (std::string msg) throw () : _msg (msg) {}
};
