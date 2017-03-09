#include "Nifti.hpp"

using namespace std;
using namespace NR;

Nifti::Nifti (string fileName) {
    _fileName = fileName;
    _file = fopen (_fileName.c_str (), "r");

    if (!_file)
	throw FileNotFoundException (fileName);

    _readHeader ();
}

Nifti::~Nifti () {
    if (_file)
	fclose (_file);
}

void Nifti::_readHeader () {
    if (fread (&_header, NIFTI_HEADER_SIZE, 1, _file) != 1) // 1 represents the number of elements (one element = NIFTI_HEADER_SIZE bytes)
	throw HeaderErrorException ();
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
