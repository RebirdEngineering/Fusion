#ifdef IMG_JPG_SUPPORT

#include <img/ImageWriter.h>
#include <external/jpeg/jpeglib.h>
#include <external/jpeg/jinclude.h>
#include <external/jpeg/jerror.h>


using namespace io;
//using namespace gr; //No


BEGIN_NAMESPACE(img)

#define OUTPUT_BUF_SIZE 16384

struct mem_destination_mgr
{
	jpeg_destination_mgr pub;
	JOCTET* buffer;
	OutputStream* outputStream;
};

typedef mem_destination_mgr* mem_dest_ptr;

METHODDEF(void) init_destination(j_compress_ptr cinfo)
{
	mem_dest_ptr dest = (mem_dest_ptr)cinfo->dest;

	/* Allocate the output buffer --- it will be released when done with image */
	dest->buffer = (JOCTET*)
		(*cinfo->mem->alloc_small) ((j_common_ptr)cinfo, JPOOL_IMAGE,
			OUTPUT_BUF_SIZE * SIZEOF(JOCTET));

	dest->pub.next_output_byte = dest->buffer;
	dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;
}

METHODDEF(boolean) empty_output_buffer(j_compress_ptr cinfo)
{
	mem_dest_ptr dest = (mem_dest_ptr)cinfo->dest;

	dest->outputStream->write(dest->buffer, OUTPUT_BUF_SIZE);

	dest->pub.next_output_byte = dest->buffer;
	dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

	return TRUE;
}

METHODDEF(void) term_destination(j_compress_ptr cinfo)
{
	mem_dest_ptr dest = (mem_dest_ptr)cinfo->dest;
	size_t datacount = OUTPUT_BUF_SIZE - dest->pub.free_in_buffer;

	/* Write any data remaining in the buffer */
	dest->outputStream->write(dest->buffer, datacount);
}

GLOBAL(void) jpeg_mem_dest(j_compress_ptr cinfo, OutputStream* outputStream)
{
	mem_dest_ptr dest = (mem_dest_ptr)cinfo->dest;

	/* The destination object is made permanent so that multiple JPEG images
	 * can be written to the same buffer without re-executing jpeg_mem_dest.
	 */
	if (cinfo->dest == NULL) {	/* first time for this JPEG object? */
		cinfo->dest = (struct jpeg_destination_mgr*)
			(*cinfo->mem->alloc_small) ((j_common_ptr)cinfo, JPOOL_PERMANENT,
				SIZEOF(mem_dest_ptr));
	}

	dest->outputStream = outputStream;
	dest->pub.init_destination = init_destination;
	dest->pub.empty_output_buffer = empty_output_buffer;
	dest->pub.term_destination = term_destination;
}


void ImageWriter::writeJPG(OutputStream& out, const void* data, int width, int height, SurfaceFormat srcformat, int quality) //80
{
	SurfaceFormat dstformat(SurfaceFormat::SURFACE_B8G8R8); //82

	std::vector<unsigned char> pixels(dstformat.getMemoryUsage(width, height)); //?
	jpeg_compress_struct cjpeg;
	jpeg_error_mgr jerr;
	char* src_data;
	cjpeg.err = jpeg_std_error(&jerr);
	dstformat.copyPixels(&pixels, dstformat.getMemoryUsage(width, 1), SurfaceFormat::SURFACE_UNKNOWN, 0, srcformat, &src_data, dstformat.getMemoryUsage(width, 1), SurfaceFormat::SURFACE_UNKNOWN, 0, width, height);
	jpeg_CreateCompress(&cjpeg, JPEG_LIB_VERSION, sizeof(cjpeg));
	jpeg_mem_dest(&cjpeg, &out);
	cjpeg.image_width = width;
	cjpeg.image_height = height;
	cjpeg.input_components = dstformat.bitsPerPixel() / 8;
	cjpeg.in_color_space = JCS_RGB;
	jpeg_set_defaults(&cjpeg);
	jpeg_set_quality(&cjpeg, quality, true);
	jpeg_start_compress(&cjpeg, true);
	while (cjpeg.next_scanline < cjpeg.image_height)
	{
		JSAMPROW row_pointer = pixels.data() + cjpeg.next_scanline * cjpeg.image_width * cjpeg.input_components;
		jpeg_write_scanlines(&cjpeg, &row_pointer, 1);
	}
	jpeg_destroy_compress(&cjpeg);
}


} // img

#endif // IMG_JPG_SUPPORT

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.