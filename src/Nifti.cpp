#include "Nifti.hpp"

using namespace std;
using namespace NR;

Nifti::Nifti (const char * fileName) {
    _fileName = string (fileName);
    _file = fopen (_fileName.c_str (), "r");

    if (!_file)
	throw FileNotFoundException (fileName);

    _fileSize = _getFileSize ();
    _readHeader ();
    _readData ();

    _srowMatrix = NULL;
    _rotMatrix = NULL;
    _pixDimMatrix = NULL;
    _qOffsetMatrix = NULL;
}

Nifti::~Nifti () {
    if (_file)
	fclose (_file);

    if (_data)
	delete[] _data;

    if (_srowMatrix)
	delete _srowMatrix;

    if (_rotMatrix)
	delete _rotMatrix;

    if (_pixDimMatrix)
	delete _pixDimMatrix;

    if (_qOffsetMatrix)
	delete _qOffsetMatrix;
}

int Nifti::getWidth () const {
    return _header.dim[1];
}

int Nifti::getHeight () const {
    return _header.dim[2];
}

void Nifti::_readHeader () {
    if (fread (&_header, NIFTI_HEADER_SIZE, 1, _file) != 1) // 1 represents the number of elements (one element = NIFTI_HEADER_SIZE bytes)
	throw HeaderErrorException ();
}

void Nifti::_readData () {
    // we skip useless data between header and voxels
    fseek (_file, _header.vox_offset, SEEK_SET);

    _dataSize = _fileSize - _header.vox_offset;

    cout << "Allocating " << _dataSize << " bytes..." << endl;
    _data = new char[_dataSize];

    if (!_data)
	throw NiftiException ("Unable to allocate memory (_readData)");

    if (fread (_data, _dataSize, 1, _file) != 1)
	throw NiftiException ("Can't read file !");
}

int Nifti::_getFileSize () {
    fseek (_file, 0L, SEEK_END);
    int res = ftell (_file);
    fseek (_file, 0L, SEEK_SET);
    return res;
}

Voxel Nifti::_transformVoxel (Voxel voxel) {
    if (_header.sform_code > 0)
	return _transformVoxelUsingMethod3 (voxel);
    if (_header.qform_code > 0)
	return _transformVoxelUsingMethod2 (voxel);

    throw NiftiException ("Unknown/Unimplemented voxel transform method");
}

Voxel Nifti::_transformVoxelUsingMethod3 (Voxel voxel) {
    Matrix<float> resMatrix (IJK_MATRIX_DIMY + 1, IJK_MATRIX_DIMX);
    Matrix<float> ijkMatrix (IJK_MATRIX_DIMY + 1, IJK_MATRIX_DIMX);

    ijkMatrix[0] = voxel.x;
    ijkMatrix[1] = voxel.y;
    ijkMatrix[2] = voxel.z;
    ijkMatrix[3] = 1;

    resMatrix = (*_srowMatrix) * ijkMatrix;

    return Voxel (resMatrix[0], resMatrix[1], resMatrix[2], voxel.p);
}

Voxel Nifti::_transformVoxelUsingMethod2 (Voxel voxel) {
    Matrix<float> resMatrix (IJK_MATRIX_DIMY, IJK_MATRIX_DIMX);
    Matrix<float> ijkMatrix (IJK_MATRIX_DIMY, IJK_MATRIX_DIMX);

    float q = (_header.pixdim[0] == -1 || _header.pixdim[0] == 1) ? _header.pixdim[0] : 1;

    ijkMatrix[0] = voxel.x;
    ijkMatrix[1] = voxel.y;
    ijkMatrix[2] = q * voxel.z;

    resMatrix = (*_rotMatrix) * ijkMatrix;
    resMatrix = resMatrix.hadamProduct (*_pixDimMatrix);
    resMatrix = resMatrix + (*_qOffsetMatrix);

    return Voxel (resMatrix[0], resMatrix[1], resMatrix[2], voxel.p);
}

void Nifti::_initMethod3Matrix () {
    cout << "Using method 3" << endl;

    _srowMatrix = new Matrix<float> (SROW_MATRIX_DIMY, SROW_MATRIX_DIMX);

    float * matrixPtr = _srowMatrix->getDataPtr ();
    float * srowPtr = (float*)_header.srow_x;

    for (unsigned int i = 0; i < (SROW_MATRIX_DIMY * 3); i++)
    	*(matrixPtr + i) = *(srowPtr + i);

    matrixPtr[12] = matrixPtr[13] = matrixPtr[14] = 0;
    matrixPtr[15] = 1;
}

void Nifti::_initMethod2Matrix () {
    cout << "Using method 2" << endl;

    float b = _header.quatern_b;
    float c = _header.quatern_c;
    float d = _header.quatern_d;
    float a = sqrt (1 - (b*b) - (c*c) - (d*d));

    _rotMatrix = new Matrix<float> (ROT_MATRIX_DIM, ROT_MATRIX_DIM);
    _pixDimMatrix = new Matrix<float> (PIXDIM_MATRIX_DIMY, PIXDIM_MATRIX_DIMX);
    _qOffsetMatrix = new Matrix<float> (QOFFSET_MATRIX_DIMY, QOFFSET_MATRIX_DIMX);

    (*_rotMatrix)[0] = (a*a) + (b*b) - (c*c) - (d*d);
    (*_rotMatrix)[1] = 2 * ((b*c) - (a*d));
    (*_rotMatrix)[2] = 2 * ((b*d) + (a*c));
    (*_rotMatrix)[3] = 2 * ((b*c) + (a*d));
    (*_rotMatrix)[4] = (a*a) + (c*c) - (b*b) - (d*d);
    (*_rotMatrix)[5] = 2 * ((c*d) - (a*b));
    (*_rotMatrix)[6] = 2 * ((b*d) - (a*c));
    (*_rotMatrix)[7] = 2 * ((c*d) + (a*b));
    (*_rotMatrix)[8] = (a*a) + (d*d) - (b*b) - (c*c);

    for (int i = 0; i < PIXDIM_MATRIX_DIMY; i++)
	(*_pixDimMatrix)[i] = _header.pixdim[i];

    for (int i = 0; i < QOFFSET_MATRIX_DIMY; i++)
	(*_qOffsetMatrix)[i] = *(&_header.qoffset_x + i);

    
    cout << "######################" << endl;
    cout << "Rot mat :" << endl;
    _rotMatrix->print ();
    cout << endl;
    cout << "PixDim mat :" << endl;
    _pixDimMatrix->print ();
    cout << endl;
    cout << "QOffset mat :" << endl;
    _qOffsetMatrix->print ();
    cout << endl;
    cout << "######################" << endl;
}

ImageContainerPtr Nifti::generateImages () {
    ImageContainerPtr images = ImageContainer::New ();

    // Init matrix
    if (_header.sform_code > 0)
	_initMethod3Matrix ();
    if (_header.qform_code > 0)
	_initMethod2Matrix ();

    ImagePtr image;
    unsigned int bytesPerVoxel = _header.bitpix / 8;
    unsigned int bytesPerImage = (_header.dim[1] * _header.dim[2]) * bytesPerVoxel;
    unsigned int nbImages = 0;
    
    cout << "byteperpix : " << bytesPerVoxel << endl;
    cout << "bitpix : " << _header.bitpix << endl;
    int count = 0;
    float * data = (float*)_data;
    for (unsigned int i = 0; i < bytesPerImage/4; i ++) {
	if (i % bytesPerImage == 0 || i == 0) {
	    if (image != NULL) {
		images->add (image);
		nbImages++;
	    }
	    image = Image::New ();
	}

	// char i_ = _data[i];
	// char j_ = _data[i + 1];
	// char k_ = _data[i + 2];
	// char p_ = _data[i + 3];

	// //Voxel v = _transformVoxel (Voxel (i_, j_, k_, p_));
	// Voxel v = Voxel (i_, j_, k_, p_);
	
	Voxel v = Voxel (data[i]);
	if (data[i] != 0.f) {
	    printf ("test : %f\n", data[i]);
	}
	// if (count < 10) {
	//     cout << "## BEFORE ";
	//     for (int j = 0; j < 4; j++) printf ("%d ", data[i + j]);
	//     cout << endl << "## AFTER : ";
	//     printf ("%d %d %d %d\n", v.x, v.y, v.z, v.p);
	//     count += 4;
	// }

	image->add (v);
    }

    if (images->getSize () < nbImages) {
	images->add (image);
	nbImages++;
    }
    
    cout << "NbImages : " << nbImages << endl;
    
    return images;
}

void Nifti::headerDump () const {

    printf ("/------ Nifti file : %s - Header ------\\\n", _fileName.c_str ());
    printf (" - Header size : %d\n", _header.sizeof_hdr);
    printf (" - Dim info : %d\n", _header.dim_info);
    printf (" - Dim [8] : ");
    for (unsigned int i = 0; i < 8; i++) printf ("%d, ", _header.dim[i]);
    printf ("\n");
    printf (" - Intent p1 : %f\n", _header.intent_p1);
    printf (" - Intent p2 : %f\n", _header.intent_p2);
    printf (" - Intent p3 : %f\n", _header.intent_p3);
    printf (" - Intent code : %d\n", _header.intent_code);
    printf (" - Datatype : %d\n", _header.datatype);
    printf (" - BitPix : %d\n", _header.bitpix);
    printf (" - Slice start : %d\n", _header.slice_start);
    printf (" - Pix dim [8] : ");
    for (unsigned int i = 0; i < 8; i++) printf ("%f, ", _header.pixdim[i]);
    printf ("\n");
    printf (" - Vox offset : %f\n", _header.vox_offset);
    printf (" - Scl slope : %f\n", _header.scl_slope);
    printf (" - Scl inter : %f\n", _header.scl_inter);
    printf (" - Slice end : %d\n", _header.slice_end);
    printf (" - Slice code : %d\n", _header.slice_code);
    printf (" - xyzt Units : %d\n", _header.xyzt_units);
    printf (" - Cal max : %f\n", _header.cal_max);
    printf (" - Cal min : %f\n", _header.cal_min);
    printf (" - Slice duration : %f\n", _header.slice_duration);
    printf (" - Toffset : %f\n", _header.toffset);
    printf (" - Descript : %s\n", _header.descript);
    printf (" - Aux file : %s\n", _header.aux_file);
    printf (" - Qform code : %d\n", _header.qform_code);
    printf (" - Sform code : %d\n", _header.sform_code);
    printf (" - Quatern b : %f\n", _header.quatern_b);
    printf (" - Quatern c : %f\n", _header.quatern_c);
    printf (" - Quatern d : %f\n", _header.quatern_d);
    printf (" - Qoffset x : %f\n", _header.qoffset_x);
    printf (" - Qoffset y : %f\n", _header.qoffset_y);
    printf (" - Qoffset z : %f\n", _header.qoffset_z);
    printf (" - Srow x : ");
    for (unsigned int i = 0; i < 4; i++) printf ("%f, ", _header.srow_x[i]);
    printf ("\n");
    printf (" - Srow y : ");
    for (unsigned int i = 0; i < 4; i++) printf ("%f, ", _header.srow_y[i]);
    printf ("\n");
    printf (" - Srow z : ");
    for (unsigned int i = 0; i < 4; i++) printf ("%f, ", _header.srow_z[i]);
    printf ("\n");
    printf (" - Intent name : %s\n", _header.intent_name);
    printf (" - Magic : %s\n", _header.magic);
}
