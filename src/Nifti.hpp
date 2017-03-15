#pragma once

#include <iostream>
#include <cstdio>
#include <cmath>

#include "ImageContainer.hpp"
#include "Voxel.hpp"

#include "utils/NiftiExceptions.hpp"
#include "utils/Matrix.hpp"

/**
   Nifti header

   More information about this file format : 
     https://brainder.org/2012/09/23/the-nifti-file-format/

   (*1) : ANALYZE 7.5 file format, old and problematic but widespread
 */

#define NIFTI_HEADER_SIZE 348   //bytes
#define SROW_MATRIX_DIMX 4       //srow matrix 4x4 (used in method 3)
#define SROW_MATRIX_DIMY 4
#define ROT_MATRIX_DIM 3        //rotation matrix 3x3 (used in method 2)
#define PIXDIM_MATRIX_DIMX 1    //pixdim matrix 1x3, one colum, three lines
#define PIXDIM_MATRIX_DIMY 3
#define QOFFSET_MATRIX_DIMX 1   //qoffset matrix 1x3
#define QOFFSET_MATRIX_DIMY 3
#define IJK_MATRIX_DIMX 1
#define IJK_MATRIX_DIMY 3

#define TODO(s)					\
    cout << "Todo : " << s << endl;		\
    exit (-1);					

// namespace NR : Nifti Reader
namespace NR {

    // Total size : 348 bytes
    struct NrHeader { 
	int sizeof_hdr;      // size of the header, must be 348 bytes
	char data_type[10];  // not used, compatibility with ANALYZE (*1)
	char db_name[18];    // ""
	int extents;         // ""
	short session_error; // ""
	char regular;        // ""
	char dim_info;       // encoding directions (phase, frequency, slice=
	short dim[8];        // data array dimensions
        float intent_p1;     // 1st intent parameter
	float intent_p2;     // 2nd intent parameter
	float intent_p3;     // 3rd intent parameter
	short intent_code;   // NIFTI intent
	short datatype;      // Data type
	short bitpix;        // number of bits per voxel
	short slice_start;   // first slice index
	float pixdim[8];     // grid spacings (unit per dimension)
	float vox_offset;    // offset into a .nii file
	float scl_slope;     // data scaling, slope
	float scl_inter;     // data scaling, offset
	short slice_end;     // last slice index
	char slice_code;     // slice timing order
	char xyzt_units;     // units of pixdim[1..4]
	float cal_max;       // maximum display intensity
	float cal_min;       // minimum display intensity
	float slice_duration;// time for one slice
	float toffset;       // time axis shift
	int glmax;           // not used, compatibility with ANALYZE
	int glmin;           // ""
	char descript[80];   // any text
	char aux_file[24];   // auxiliary filename
	short qform_code;    // use the quaternion fields
	short sform_code;    // use of the affine fields
	float quatern_b;     // Quaternion b parameter
	float quatern_c;     // Quaternion c parameter
	float quatern_d;     // Quaternion d parameter
	float qoffset_x;     // Quaternion x shift
	float qoffset_y;     // Quaternion y shift
	float qoffset_z;     // Quaternion z shift
	float srow_x[4];     // 1st row affine transform
	float srow_y[4];     // 2nd row affine transform
	float srow_z[4];     // 3rd row affine transform
	char intent_name[16];// name ot meaning of the data
	char magic[4];       // magic string
    };

    class Nifti {
    public:
	Nifti (const char * fileName);
	~Nifti ();

	void headerDump () const;
	ImageContainerPtr generateImages ();

	int getWidth () const;
	int getHeight () const;

    private:
	void _readHeader ();
	void _readData ();
	int _getFileSize ();

	Voxel _transformVoxel (Voxel voxel);
	Voxel _transformVoxelUsingMethod3 (Voxel voxel);
	Voxel _transformVoxelUsingMethod2 (Voxel voxel);

	void _initMethod3Matrix ();
	void _initMethod2Matrix ();

	std::string _fileName;
	FILE * _file;
	unsigned int _fileSize;

	NrHeader _header;
	char * _data;
	unsigned int _dataSize;

	// The following var are using by the different methods (1, 2 and 3)
	// Theses methods are used to transform the voxels (i, j, k => x, y, z coordinates)
	Matrix<float> * _srowMatrix;    // 3rd Method, 4x4
	Matrix<float> * _rotMatrix;     // 2nd Method
	Matrix<float> * _pixDimMatrix;  // 2nd Method
	Matrix<float> * _qOffsetMatrix; // 2nd Method
    };
};
