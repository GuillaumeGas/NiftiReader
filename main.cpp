#include <iostream>

#include "src/Nifti.hpp"
#include "src/ImageContainer.hpp"
#include "src/Voxel.hpp"
#include "src/NiftiExceptions.hpp"

using namespace std;

int main (int argc, char ** argv) {

    if (argc == 2) {
	try {
	    NR::Nifti n (argv[1]);
	    // n.headerDump ();

	    NR::ImageContainerPtr images = n.generateImages ();
	
	    for (int i = 0; i < images->getSize (); i++) {
		if (i % 5 == 0) {
		    NR::ImagePtr image = images->get (i);
		    cout << "Image " << i << endl;
		    for (int j = 0; j < image->getSize (); j++) {
			if (j % 5 == 0) {
			    NR::Voxel v = image->get (j);
			    printf ("  %d, %d, %d\n", v.x, v.y, v.z);
			}	
		    }
		}
	    }
	} catch (NR::NiftiException & e) {
	    cout << e.toString () << endl;
	}
    } else {
	cout << "Usage : " << endl;
	cout << " niftireader file_name" << endl;
    }

    return 0;
}
