#pragma once

#include <iostream>

/**
   Voxel header
 */

namespace NR {
    struct Voxel {
	Voxel (char x, char y, char z, char p);
	Voxel (float test);
	void print ();

	char x, y, z, p;
	float test;
    };
};
