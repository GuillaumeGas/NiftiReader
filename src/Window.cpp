#include "Window.hpp"

using namespace std;

Window::Window (const char * fileName) : _fileName (fileName) {
    _window = new QWidget;
    _mainLayout = new QVBoxLayout;
    _button = new QPushButton ("test");
    _buttonItk = new QPushButton ("test itk");
    
    setWindowTitle ("Nifti test !");

    _mainLayout->addWidget (_button);
    _mainLayout->addWidget (_buttonItk);
    _window->setLayout (_mainLayout);
    setCentralWidget (_window);

    QObject::connect (_button, SIGNAL (clicked ()), this, SLOT (test ()));
    QObject::connect (_buttonItk, SIGNAL (clicked ()), this, SLOT (testItk ()));
}

void Window::test () {
    NR::Nifti nifti (_fileName);

    nifti.headerDump ();

    DrawDialog dialog (&nifti);
    dialog.exec ();
}

void Window::testItk () {
    DrawDialog dialog (_fileName);
    dialog.exec ();

    // typedef itk::Image<short, 3> DWI;
    // typedef itk::ImageFileReader<DWI> DWIReader;

    // itk::ImageIOBase::Pointer imageIO = itk::ImageIOFactory::CreateImageIO (_fileName, itk::ImageIOFactory::ReadMode);
    // imageIO->SetFileName (string (_fileName));
    // imageIO->ReadImageInformation ();

    // DWIReader::Pointer dwiReader = DWIReader::New ();
    // dwiReader->SetFileName (imageIO->GetFileName ());
    // dwiReader->Update ();

    // DWI::RegionType region;
    // DWI::IndexType start;
    // DWI::SizeType size;

    // for (int i = 0; i < imageIO->GetNumberOfDimensions (); i++) {
    // 	start[i] = 0;
    // 	size[i] = imageIO->GetDimensions (i);
    // }

    // region.SetSize (size);
    // region.SetIndex (start);

    // DWI::Pointer dwi = dwiReader->GetOutput ();
    // DWI::Pointer outDwi = DWI::New ();

    // outDwi->SetRegions (region);
    // outDwi->Allocate ();

    // itk::ImageRegionIterator<DWI> imageIterator (dwi, region);

    // char * data = new char[size[0] * size[1] * size[2]];
    // int cpt = 0;
    // while (!imageIterator.IsAtEnd ()) {
    // 	data[cpt] = imageIterator.Value ();
    // 	if (data[cpt] != 100)
    // 	    printf ("%d\n", data[cpt]);
    // 	cpt++;
    // 	++imageIterator;
    // }

    // delete[] data;
}
