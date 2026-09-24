#include <io/FileFormat.h>

namespace io
{

const char* names[] =
{	"UNKNOWN",
	"BMP",
	"TGA",
	"JPG",
	"DDS",
	"PSD",
	"PNG",
	"PCX",
	"PNM",
	"GIF",
	"TIF",
	"PVR",
	"WAV",
	"MP3",
	"HGR", //Why is this still here
	"RAW",
	"WEBP"
};

FileFormat guessFileFormat( const std::string& filename )
{
	size_t pos = filename.find_last_of('.');

	std::string suffix = filename.substr(pos + 1);

	FileFormat ff = FILEFORMAT_UNKNOWN;

	const char* ptr = toString(ff);

	if (ptr)
	{
		if (suffix == "bmp") ff = FILEFORMAT_BMP;
		else if (suffix == "tga") ff = FILEFORMAT_TGA;
		else if (suffix == "jpg" || suffix == "jpeg") ff = FILEFORMAT_JPG;
		else if (suffix == "dds") ff = FILEFORMAT_DDS;
		else if (suffix == "psd") ff = FILEFORMAT_PSD;
		else if (suffix == "png") ff = FILEFORMAT_PNG;
		else if (suffix == "pcx") ff = FILEFORMAT_PCX;
		else if (suffix == "pnm") ff = FILEFORMAT_PNM;
		else if (suffix == "gif") ff = FILEFORMAT_GIF;
		else if (suffix == "tif" || suffix == "tiff") ff = FILEFORMAT_TIF;
		else if (suffix == "pvr") ff = FILEFORMAT_PVR;
		else if (suffix == "wav") ff = FILEFORMAT_WAV;
		else if (suffix == "mp3") ff = FILEFORMAT_MP3;
		else if (suffix == "hgr") ff = FILEFORMAT_HGR; //Why is this still here
		else if (suffix == "raw") ff = FILEFORMAT_RAW;
	}

	return ff;
}

const char* toString(FileFormat ff)
{
	return names[ff];
}

}