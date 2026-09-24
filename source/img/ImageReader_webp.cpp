#ifdef IMG_WEBP_SUPPORT

#include <img/ImageReader.h>
#include <external/webp/webp/decode.h>
#include <lang/Exception.h>

using namespace io;
using namespace lang;

namespace img
{

void ImageReader::readHeader_webp() //13
{
	ByteArrayInputStream in(*m_in); //13
	const uint8_t* data = (uint8_t*)in.data(); //14
	size_t size = in.available(); //15
	WebPBitstreamFeatures features; //18
	VP8StatusCode status = WebPGetFeaturesInternal(data, size, &features, WEBP_DECODER_ABI_VERSION);
	if (status) //Seasons 4.1.0
		throwError(Exception(Format("Loading WebP image failed"))); //21

	m_width = features.width;
	m_height = features.height;
	m_fmt = features.has_alpha ? SurfaceFormat::SURFACE_A8B8G8R8 : SurfaceFormat::SURFACE_B8G8R8;
	m_bitsPerPixel = m_fmt.bitsPerPixel();
	m_pitch = m_fmt.getMemoryUsage(m_width, 1);
	m_mipLevels = 1;
	m_surfaces = 1;
	m_surfaceBuffer.resize(1);
	Surface& surface = m_surfaceBuffer[0]; //33
	surface.width = m_width;
	surface.height = m_height;
	surface.data.resize(m_height * m_pitch); //37

	if (features.has_alpha) //We'd use a convenient else but according to DWARF they used a separate define since we want similar code we're doing it this way
	{
		uint8_t* res = WebPDecodeRGBAInto(data, size, surface.data.data(), surface.data.size(), m_pitch); //41
		if (!res)
			throwError(Exception(Format("Loading WebP image failed"))); //43
	}
	else
	{
		uint8_t* res = WebPDecodeRGBInto(data, size, surface.data.data(), surface.data.size(), m_pitch); //47
		if (!res)
			throwError(Exception(Format("Loading WebP image failed"))); //49
	}
	//todo?
}

}

#endif