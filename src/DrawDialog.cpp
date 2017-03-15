#include "DrawDialog.hpp"

using namespace std;

DrawDialog::DrawDialog (NR::Nifti * nifti, QWidget * parent) : _nifti (nifti), QDialog (parent) {
    setWindowTitle ("Draw Dialog");
    resize (_nifti->getWidth (), _nifti->getHeight ());

    NR::ImageContainerPtr images = _nifti->generateImages ();
    NR::ImagePtr image = images->get (0);
    // for (auto it : image->getAll ()) {
    	// printf ("%d %d %d %d\n", it.x, it.y, it.z, it.p);
	// printf ("%f\n", it.test);
    	// _points.push_back (QPoint (it.x, it.y));
    // }

    // _mainLayout = new QVBoxLayout;
    // _renderArea = new RenderArea (&_points);
    // _closeButton = new QPushButton ("Close");

    // QObject::connect (_closeButton, SIGNAL (clicked ()), this, SLOT (accept ()));

    // _mainLayout->addWidget (_renderArea);
    // _mainLayout->addWidget (_closeButton);
    // setLayout (_mainLayout);
}

DrawDialog::DrawDialog (const char * fileName, QWidget * parent) : QDialog (parent) {

    setWindowTitle ("Draw Dialog");

    typedef itk::Image<short, 3> DWI;
    typedef itk::ImageFileReader<DWI> DWIReader;

    itk::ImageIOBase::Pointer imageIO = itk::ImageIOFactory::CreateImageIO (fileName, itk::ImageIOFactory::ReadMode);
    imageIO->SetFileName (string (fileName));
    imageIO->ReadImageInformation ();

    DWIReader::Pointer dwiReader = DWIReader::New ();
    dwiReader->SetFileName (imageIO->GetFileName ());
    dwiReader->Update ();

    DWI::RegionType region;
    DWI::IndexType start;
    DWI::SizeType size;

    for (int i = 0; i < imageIO->GetNumberOfDimensions (); i++) {
	start[i] = 0;
	size[i] = imageIO->GetDimensions (i);
    }

    resize (size[0], size[1]);

    region.SetSize (size);
    region.SetIndex (start);

    DWI::Pointer dwi = dwiReader->GetOutput ();
    DWI::Pointer outDwi = DWI::New ();

    outDwi->SetRegions (region);
    outDwi->Allocate ();

    itk::ImageRegionIterator<DWI> imageIterator (dwi, region);

    int cpt = 0;
    int x, y;
    x = y = 0;

    ImageTestPtr image = ImageTest::New ();
    _images = ImageContainerTest::New ();
    while (!imageIterator.IsAtEnd ()) {
	char c = imageIterator.Value ();
	if (!c)
	    image->add (QPoint (x, y));

	cpt++;
	++imageIterator;
	x++;
	if (x%size[0] == 0) {
	    y++;
	    x = 0;
	}
	if ((x + 1) == size[0] && (y + 1) == size[1]) {
	    _images->add (image);
	    image = ImageTest::New ();
	    x = y = 0;
	}
    }
    if (_images->getSize () < size[2])
	_images->add (image);

    _mainLayout = new QVBoxLayout;
    _renderArea = new RenderArea (_images->get (0)->getAll ());
    _closeButton = new QPushButton ("Close");
    _slider = new QSlider (Qt::Horizontal);
    _slider->setMaximum (size[2] - 1);

    QObject::connect (_closeButton, SIGNAL (clicked ()), this, SLOT (accept ()));
    QObject::connect (_slider, SIGNAL (valueChanged (int)), this, SLOT (setImage (int)));

    _mainLayout->addWidget (_renderArea);
    _mainLayout->addWidget (_closeButton);
    _mainLayout->addWidget (_slider);
    setLayout (_mainLayout);
 
}

void DrawDialog::setImage (int value) {
    try {
	_renderArea->setPoints (_images->get (value)->getAll ());
    } catch (NR::NiftiException & e) {
	cout << e.toString() << endl;
    }
}
