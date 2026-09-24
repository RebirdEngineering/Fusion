#include <img/ImageWriter.h>
#include <io/IOException.h>

using namespace io;
using namespace lang;

namespace img
{

void ImageWriter::write(OutputStream& out, FileFormat fileformat, const void* data, int width, int height, SurfaceFormat srcformat, SurfaceFormat dstformat)
{
	switch (fileformat)
	{
		case FILEFORMAT_JPG:	writeJPG(out, data, width, height, srcformat, 100); break;
		case FILEFORMAT_PNG:	writePNG(out, data, width, height, srcformat); break;
		case FILEFORMAT_RAW:	out.write(data, srcformat.getMemoryUsage(width, height));
#ifdef IMG_PVR_WRITE
		case FILEFORMAT_PVR:	writePVR(out, data, width, height, srcformat, 100);
#endif
#ifdef IMG_WEBP_WRITE //This only appears in newer Fusion revisions (Seasons 5.3.1)
		case FILEFORMAT_WEBP:	writeLossyWebP(out, data, width, height, srcformat, 100); //Write lossless WEBP isn't called.
		case FILEFORMAT_WEBP:	writeLosslessWebP(out, data, width, height, srcformat, 100); //Never called. Function completely removed in newer engine revisions.
#endif
		default: throwError(IOException(Format("Unsupported ImageWriter file format {0}", toString(fileformat))));
	}
}

}
