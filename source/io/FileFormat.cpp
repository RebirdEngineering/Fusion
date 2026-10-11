#include <io/FileFormat.h>
#include <lang/string.h>

using namespace lang;

namespace io
{

const char* names[] = //11
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

FileFormat guessFileFormat( const std::string& filename ) //30
{
	size_t pos = filename.find_last_of('.'); //32
	if (pos == -1)
		return FILEFORMAT_UNKNOWN;

	std::string suffix = string::toupper(filename).substr(pos + 1); //35

	FileFormat ff = FILEFORMAT_UNKNOWN; //37

	const char* ptr = toString(ff); //39
	
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
	else if (suffix == "webp") ff = FILEFORMAT_WEBP;
	
	return ff;
}

const char* toString(FileFormat ff) //50
{
	return names[ff];
}

}