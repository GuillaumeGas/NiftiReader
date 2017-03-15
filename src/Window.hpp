#pragma once

#include <iostream>

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkNiftiImageIO.h>

#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkImageSeriesReader.h>

#include <itkRescaleIntensityImageFilter.h>

#include "DrawDialog.hpp"

#include "Nifti.hpp"
#include "ImageContainer.hpp"
#include "Voxel.hpp"
#include "Image.hpp"
// #include "utils/NiftiException.hpp"

class Window : public QMainWindow {
    Q_OBJECT
    
public:
    Window (const char * fileName);

public slots:
    void test ();
    void testItk ();

private:
    QWidget * _window;
    QVBoxLayout * _mainLayout;
    QPushButton * _button;
    QPushButton * _buttonItk;

    const char * _fileName;
};
