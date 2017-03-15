#include "Voxel.hpp"

using namespace std;
using namespace NR;

Voxel::Voxel (char x, char y, char z, char p) : x (x), y (y), z (z), p (p) {}

Voxel::Voxel (float test) : test (test) {}

void Voxel::print () {
    cout << "x = " << std::to_string (x) << " y = " << std::to_string (y) << " z = " << std::to_string (z) << " p = " << std::to_string (p) << endl;

    // printf ("x = %d, y = %d, z = %d, p = %d\n", x, y, z, p);
}
