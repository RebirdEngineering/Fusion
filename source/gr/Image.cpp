#include <gr/Image.h>

using namespace img;

namespace gr //Seems they moved all the stuff to the graphical renderers
{

#ifdef IMG_WRITER_SUPPORT //Doesn't exist in the header at all.
void Image::save( const std::string& filename )
{
	ImageWriter::write( filename, SurfaceFormat::SURFACE_A8R8G8B8, m_bits.begin(), m_width, m_height, m_width*4, SurfaceFormat::SURFACE_A8R8G8B8, 0, SurfaceFormat() );
}
#endif


} // img
