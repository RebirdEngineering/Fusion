#ifdef IMG_WEBP_SUPPORT

#include <img/ImageWriter.h>
#include <external/webp/webp/encode.h>
#include <lang/Exception.h>

using namespace io;
using namespace lang;

namespace img
{

void ImageWriter::writeLosslessWebP(OutputStream& out, const void* data, int width, int height, SurfaceFormat srcformat) //Symbol seen in Classic 5.2.0 and countdown to ABGO v5.2.0, unofficial restoration
{
	const uint8_t* tex = (uint8_t*)data;
	size_t bytes = 0;
	int stride = 4 * width;
	switch (srcformat.type())
	{
	case SurfaceFormat::SURFACE_R8G8B8: bytes = WebPEncodeLosslessBGR(tex, width, height, stride, 0);
	case SurfaceFormat::SURFACE_B8G8R8: bytes = WebPEncodeLosslessRGB(tex, width, height, stride, 0);
	case SurfaceFormat::SURFACE_A8R8G8B8: bytes = WebPEncodeLosslessBGRA(tex, width, height, stride, 0);
	case SurfaceFormat::SURFACE_A8B8G8R8: bytes = WebPEncodeLosslessRGBA(tex, width, height, stride, 0);
	default: throwError(Exception(Format("WebP does support given surface format: {0}", srcformat.toString())));
	}
	out.write(data, bytes);
}

void ImageWriter::writeLossyWebP(OutputStream& out, const void* data, int width, int height, SurfaceFormat srcformat, int quality) //Symbol seen in Classic 5.2.0 and countdown to ABGO v5.2.0, unofficial restoration
{
	const uint8_t* tex = (uint8_t*)data;
	size_t bytes = 0;
	int stride = 4 * width;
	switch (srcformat.type())
	{
	case SurfaceFormat::SURFACE_R8G8B8: bytes = WebPEncodeBGR(tex, width, height, stride, (float)quality, 0);
	case SurfaceFormat::SURFACE_B8G8R8: bytes = WebPEncodeRGB(tex, width, height, stride, (float)quality, 0);
	case SurfaceFormat::SURFACE_A8R8G8B8: bytes = WebPEncodeBGRA(tex, width, height, stride, (float)quality, 0);
	case SurfaceFormat::SURFACE_A8B8G8R8: bytes = WebPEncodeRGBA(tex, width, height, stride, (float)quality, 0);
	default: throwError(Exception(Format("WebP does support given surface format: {0}", srcformat.toString())));
	}
	out.write(data, bytes);
}

}

#endif