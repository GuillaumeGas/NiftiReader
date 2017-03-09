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
};
