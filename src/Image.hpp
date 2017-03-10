#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "NiftiExceptions.hpp"
#include "Voxel.hpp"

namespace NR {
    class Image;
    typedef std::shared_ptr<Image> ImagePtr;

    class Image {
    public:
	void add (Voxel voxel);
	Voxel get (unsigned int index) const;
	std::vector<Voxel> & getAll ();
	unsigned int getSize () const;

	static ImagePtr New ();

    private:
	std::vector<Voxel> _voxels;
	unsigned int _count;
    };
};
