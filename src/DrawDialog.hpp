#pragma once

#include <iostream>
#include <vector>

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPoint>
#include <QSlider>

#include "ImageContainer.hpp"
#include "RenderArea.hpp"
#include "Nifti.hpp"
#include "utils/NiftiExceptions.hpp"

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkNiftiImageIO.h>

#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkImageSeriesReader.h>

#include <itkRescaleIntensityImageFilter.h>

class DrawDialog : public QDialog {
    Q_OBJECT

public:
    DrawDialog (NR::Nifti * nifti, QWidget * parent = NULL);
    DrawDialog (const char * fileName, QWidget * parent = NULL);

public slots:
    void setImage (int value);

private:
    QVBoxLayout * _mainLayout;
    RenderArea * _renderArea;
    QPushButton * _closeButton;
    QSlider * _slider;

    NR::Nifti * _nifti;
    ImageContainerTestPtr _images;
};
