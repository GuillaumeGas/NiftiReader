#include "ImageContainer.hpp"

using namespace std;
using namespace NR;

ImageContainerPtr ImageContainer::New () {
    return std::make_shared<ImageContainer> ();
}

void ImageContainer::add (ImagePtr image) {
    _images.push_back (image);
    _count++;
}

ImagePtr ImageContainer::get (unsigned int index) const {
    if (index >= 0 && index < _count)
	return _images[index];
    throw NiftiException ("ImageContainer::get - Index out of bounds");
}

vector<ImagePtr> & ImageContainer::getAll () {
    return _images;
}

unsigned int ImageContainer::getSize () const {
    return _count;
}
