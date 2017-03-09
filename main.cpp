#include <iostream>

#include "src/Nifti.hpp"

using namespace std;

int main (int argc, char ** argv) {

    if (argc == 2) {
	NR::Nifti n (argv[1]);
	n.headerDump ();
    } else {
	cout << "Usage : " << endl;
	cout << " niftireader file_name" << endl;
    }

    return 0;
}
