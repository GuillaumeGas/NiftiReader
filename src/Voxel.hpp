#pragma once

#include <iostream>

/**
   Voxel header
 */

namespace NR {
    struct Voxel {
	Voxel (char x, char y, char z);

	char x, y, z;
    };
};
