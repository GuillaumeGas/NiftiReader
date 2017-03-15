#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Image.hpp"
#include "utils/NiftiExceptions.hpp"

namespace NR {
    class ImageContainer;
    typedef std::shared_ptr<ImageContainer> ImageContainerPtr;

    class ImageContainer {
    public:
	static ImageContainerPtr New ();

	void add (ImagePtr image);
	ImagePtr get (unsigned int index) const;
	std::vector<ImagePtr> & getAll ();
	unsigned int getSize () const;

    private:
	std::vector<ImagePtr> _images;
	unsigned int _count;
    };
};

class ImageContainerTest;
typedef std::shared_ptr<ImageContainerTest> ImageContainerTestPtr;

class ImageContainerTest {
public:
    static ImageContainerTestPtr New ();

    void add (ImageTestPtr image);
    ImageTestPtr get (unsigned int index) const;
    std::vector<ImageTestPtr> & getAll ();
    unsigned int getSize () const;

private:
    std::vector<ImageTestPtr> _images;
    unsigned int _count;
};
