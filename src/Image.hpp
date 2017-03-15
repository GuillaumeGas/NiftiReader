#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include <QPoint>

#include "utils/NiftiExceptions.hpp"
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
	void dump () const;

	static ImagePtr New ();

    private:
	std::vector<Voxel> _voxels;
	unsigned int _count;
    };
};

class ImageTest;
typedef std::shared_ptr<ImageTest> ImageTestPtr;

class ImageTest {
public:
    void add (QPoint point);
    QPoint get (unsigned int index) const;
    std::vector<QPoint> * getAll ();
    unsigned int getSize () const;
    void dump () const;

    static ImageTestPtr New ();

private:
    std::vector<QPoint> _voxels;
    unsigned int _count;
};
