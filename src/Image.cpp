#include "Image.hpp"

using namespace std;
using namespace NR;

ImagePtr Image::New () {
    return std::make_shared<Image> ();
}

void Image::add (Voxel voxel) {
    _voxels.push_back (voxel);
    _count++;
}

Voxel Image::get (unsigned int index) const {
    if (index >= 0 && index < _count)
	return _voxels[index];
    throw NiftiException ("Image::get - Index out of bounds");
}

vector<Voxel> & Image::getAll () {
    return _voxels;
}

unsigned int Image::getSize () const {
    return _count;
}

void Image::dump () const {
    cout << "/------- Dump Image -------\\" << endl;
    for (auto it : _voxels)
	it.print ();
    cout << "\\-------------------------/" << endl;
}
//###################
ImageTestPtr ImageTest::New () {
    return std::make_shared<ImageTest> ();
}

void ImageTest::add (QPoint voxel) {
    _voxels.push_back (voxel);
    _count++;
}

QPoint ImageTest::get (unsigned int index) const {
    if (index >= 0 && index < _count)
	return _voxels[index];
    throw NiftiException ("ImageTest::get - Index out of bounds");
}

vector<QPoint> * ImageTest::getAll () {
    return &_voxels;
}

unsigned int ImageTest::getSize () const {
    return _count;
}

void ImageTest::dump () const {
    cout << "/------- Dump ImageTest -------\\" << endl;
    // for (auto it : _voxels)
    // 	it.print ();
    cout << "\\-------------------------/" << endl;
}
