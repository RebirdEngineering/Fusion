#ifndef _IO_FILEFORMAT_H
#define _IO_FILEFORMAT_H

#include <lang/pp.h>

namespace io
{

class InputStream;
class OutputStream;

/**
 * Supported file formats.
 */
enum FileFormat //11
{
	/** Unknown image file format. */
	FILEFORMAT_UNKNOWN,
	/** BMP image file. */
	FILEFORMAT_BMP,
	/** TGA image file. */
	FILEFORMAT_TGA,
	/** JPG image file. */
	FILEFORMAT_JPG,
	/** DDS image file. */
	FILEFORMAT_DDS,
	/** PSD image file. */
	FILEFORMAT_PSD,
	/** PNG image file. */
	FILEFORMAT_PNG,
	/** PCX image file. */
	FILEFORMAT_PCX,
	/** PNM image file. */
	FILEFORMAT_PNM,
	/** GIF image file. */
	FILEFORMAT_GIF,
	/** TIFF image file. */
	FILEFORMAT_TIF,
	/** */
	FILEFORMAT_PVR,
	/** */
	FILEFORMAT_WAV,
	/** */
	FILEFORMAT_MP3,
	/** */
	FILEFORMAT_HGR, //Why is this still here
	/** */
	FILEFORMAT_RAW,
	/** */
	FILEFORMAT_WEBP = 16
};

FileFormat guessFileFormat(const std::string& filename);
const char* toString(FileFormat ff);

}

#endif