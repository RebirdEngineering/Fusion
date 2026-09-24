#include <img/SurfaceFormat.h>
#include <gr/GraphicsException.h>
#include <math/float.h>
#include <assert.h>


USING_NAMESPACE(lang)
USING_NAMESPACE(math) //floatToHalf was moved to math


BEGIN_NAMESPACE(img) //In img now


/**
 * DXT1-5 surface color data struct.
 */
struct DXTColBlock //19
{
	uint16_t	col0;
	uint16_t	col1;
	uint8_t		rows[4];
};

/** 
 * DXT2-3 surface alpha data struct. 
 */
struct DXTAlphaBlockExplicit //29
{
	uint16_t	rows[4];
};

/** 
 * DXT4-5 surface alpha data struct. 
 */
struct DXTAlphaBlock3BitLinear //37
{
	uint8_t		alpha0;
	uint8_t		alpha1;
	uint8_t		values[6];
};

const char* const FORMAT_NAMES[] = //44
{
	/** The surface format is unknown. */
	"UNKNOWN",
	/** 24-bit RGB pixel format. */
	"R8G8B8",
	/** 24-bit RGB pixel format. */
	"B8G8R8",
	/** 32-bit RGB pixel format with alpha. */
	"A8R8G8B8",
	/** 32-bit RGB pixel format where 8 bits are reserved for each color. */
	"X8R8G8B8",
	/** 32-bit RGB pixel format where 8 bits are reserved for each color.  */
	"X8B8G8R8",
	/** 32-bit RGB pixel format with alpha.  */
	"A8B8G8R8",
	/** 16-bit RGB pixel format. (PS2) */
	"R5G6B5",
	/** 16-bit RGB pixel format. */
	"R5G5B5",
	/** 18-bit RGB pixel format. */
	"R6G6B6",
	/** 4-bit palettized pixel format. (PC/PS2) */
	"P4",
	/** 8-bit palettized pixel format. (PC/PS2)	*/
	"P8",
	/** 8-bit luminosity format. (PC/PS2) */
	"L8",
    /** [ADD] */
	"L8A8",
	/** 16-bit pixel format where 5 bits are reserved for color and 1 bit is reserved for transparency. */
	"A1R5G5B5",
	/** 16-bit RGB pixel format where 4 bits are reserved for each color. */
	"X4R4G4B4",
	/** 16-bit RGBA pixel format. */
	"A4R4G4B4",
	/** 16-bit RGBA pixel format. */
	"A4B4G4R4",
	/** 16-bit RGBA pixel format. */
	"R4G4B4A4",
	/** 16-bit pixel format where 5 bits are reserved for color and 1 bit is reserved for transparency. */
	"A1B5G5R5",
	/** 16-bit pixel format where 5 bits are reserved for color and 1 bit is reserved for transparency. */
	"R5G5B5A1",
	/** 8-bit RGB texture format. (PS2) */
	"R3G3B2",
	/** 8-bit RGB texture format. */
	"R3G2B3",
	/** 8-bit alpha-only. */
	"A8",
	/** 16-bit RGB pixel format with alpha.	*/
	"A8R3G3B2",
	/** 16-bit RGB pixel format with alpha.	*/
	"A8R3G2B3",
	/** DirectX compressed texture */
	"DXT1",
	/** DirectX compressed texture */
	"DXT3",
	/** DirectX compressed texture */
	"DXT5",
	/** [ADD] */
	"RGB_PVRTC_GL_2BPP",
	/** [ADD] */
	"RGBA_PVRTC_GL_2BPP",
	/** [ADD] */
	"RGB_PVRTC_GL_4BPP",
	/** [ADD] */
	"RGBA_PVRTC_GL_4BPP",
	/** [ADD] */
	"ETC1_RGB_4BPP",
	/** 16-bit float format, 16 bits red channel. */
	"R16F",
	/** 32-bit float format, 16 bits red and green channels. */
	"G16R16F",
	/** 64-bit float format, 16 bits for the alpha, blue, green, red. */
	"A16B16G16R16F",
	/** 32-bit float format, 32 bits red channel. */
	"R32F",
	/** 64-bit float format, 32 bits red and green channels. */
	"G32R32F",
	/** 128-bit float format, 32 bits for the alpha, blue, green, red. */
	"A32B32G32R32F",
	/** 32-bit depth buffer format */
	"D32",
	/** 24-bit depth buffer format */
	"D24",
	/** 16-bit depth buffer format */
	"D16",
	/** "32", depth using 24 bits and stencil 8 bits */
	"D24S8",
};

/** 
 * Descriptions of surface formats: 
 * {format, bitcount, red mask, green mask, blue mask, alpha mask}. 
 */
static const uint32_t FORMATDESC[][6] = //140 | I'm p sure this is correct
{
	{SurfaceFormat::SURFACE_UNKNOWN   ,  0, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{SurfaceFormat::SURFACE_R8G8B8    , 24, 0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000},
	{SurfaceFormat::SURFACE_B8G8R8    , 24, 0x000000ff, 0x0000ff00, 0x00ff0000, 0x00000000},
	{SurfaceFormat::SURFACE_A8R8G8B8  , 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000},
	{SurfaceFormat::SURFACE_X8R8G8B8  , 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000},
	{SurfaceFormat::SURFACE_X8B8G8R8  , 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0x00000000},
	{SurfaceFormat::SURFACE_A8B8G8R8  , 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000},
	{SurfaceFormat::SURFACE_R5G6B5    , 16, 0x0000f800, 0x000007e0, 0x0000001f, 0x00000000},
	{SurfaceFormat::SURFACE_R5G5B5    , 16, 0x00007c00, 0x000003e0, 0x0000001f, 0x00000000},
	{SurfaceFormat::SURFACE_R6G6B6    , 32, (0x3F<<12),  (0x3F<<6),     (0x3F), 0x00000000},
	{SurfaceFormat::SURFACE_P4		 ,  4,  0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{SurfaceFormat::SURFACE_P8		 ,  8,  0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{SurfaceFormat::SURFACE_L8		 ,  8,  0x000000FF, 0x000000FF, 0x000000FF, 0x00000000},
    {SurfaceFormat::SURFACE_A8L8	 ,  16, 0x000000FF, 0x000000FF, 0x000000FF, 0x0000ff00}, //Add L8A8
	{SurfaceFormat::SURFACE_A1R5G5B5  , 16, 0x00007c00, 0x000003e0, 0x0000001f, 0x00008000},
	{SurfaceFormat::SURFACE_X4R4G4B4  , 16, 0x00000f00, 0x000000f0, 0x0000000f, 0x00000000},
	{SurfaceFormat::SURFACE_A4R4G4B4  , 16, 0x00000f00, 0x000000f0, 0x0000000f, 0x0000f000},
	{SurfaceFormat::SURFACE_A4B4G4R4  , 16, 0x0000000f, 0x000000f0, 0x00000f00, 0x0000f000},
	{SurfaceFormat::SURFACE_R4G4B4A4  , 16, 0x0000f000, 0x00000f00, 0x000000f0, 0x0000000f},
	{SurfaceFormat::SURFACE_A1B5G5R5  , 16, 0x0000001f, 0x000003e0, 0x00007c00, 0x00008000},
	{SurfaceFormat::SURFACE_R5G5B5A1  , 16, (0x1F<<11),	(0x1F<<6),	(0x1F<<1),	0x00000001},
	{SurfaceFormat::SURFACE_R3G3B2    ,  8, 0x000000e0, 0x0000001c, 0x00000003, 0x00000000},
	{SurfaceFormat::SURFACE_R3G2B3    ,  8, 0x000000e0, 0x00000018, 0x00000007, 0x00000000},
	{SurfaceFormat::SURFACE_A8        ,  8, 0x00000000, 0x00000000, 0x00000000, 0x000000ff},
	{SurfaceFormat::SURFACE_A8R3G3B2  , 16, 0x000000e0, 0x0000001c, 0x00000003, 0x0000ff00},
	{SurfaceFormat::SURFACE_A8R3G2B3  , 16, 0x000000e0, 0x00000018, 0x00000007, 0x0000ff00},
	{SurfaceFormat::SURFACE_DXT1	  , 0,  0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{SurfaceFormat::SURFACE_DXT3	  , 0,  0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{SurfaceFormat::SURFACE_DXT5	  , 0,  0x00000000, 0x00000000, 0x00000000, 0x00000000},
    {SurfaceFormat::SURFACE_PVRTC_RGB_2BPP	  , 2,  0x00000000, 0x00000000, 0x00000000, 0x00000000}, //Add PVRTC
    {SurfaceFormat::SURFACE_PVRTC_RGBA_2BPP	  , 2,  0x00000000, 0x00000000, 0x00000000, 0x00000000}, //Add PVRTC
    {SurfaceFormat::SURFACE_PVRTC_RGB_4BPP	  , 4,  0x00000000, 0x00000000, 0x00000000, 0x00000000}, //Add PVRTC
    {SurfaceFormat::SURFACE_PVRTC_RGBA_4BPP	  , 4,  0x00000000, 0x00000000, 0x00000000, 0x00000000}, //Add PVRTC
    {SurfaceFormat::SURFACE_ETC1_RGB_4BPP	  , 4,  0x00000000, 0x00000000, 0x00000000, 0x00000000}, //Add ETC
	{SurfaceFormat::SURFACE_R16F,			16, 0,0,0,0},
	{SurfaceFormat::SURFACE_G16R16F,		32, 0,0,0,0},
	{SurfaceFormat::SURFACE_A16B16G16R16F,	64, 0,0,0,0},
	{SurfaceFormat::SURFACE_R32F,			32, 0,0,0,0},
	{SurfaceFormat::SURFACE_G32R32F,		64, 0,0,0,0},
	{SurfaceFormat::SURFACE_A32B32G32R32F, 128, 0,0,0,0},
	{SurfaceFormat::SURFACE_D32		  , 32, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{SurfaceFormat::SURFACE_D24		  , 24, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{SurfaceFormat::SURFACE_D16		  , 16, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{SurfaceFormat::SURFACE_D24S8	  , 32, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

/** Number of supported surface formats. */
static const int FORMATS = sizeof(FORMATDESC)/sizeof(FORMATDESC[0]); //189

/** HDR format specific info. */
static const int HDR_INFO[][6] = //192 |  format, bits/component, rgba component indices
{
	{SurfaceFormat::SURFACE_R16F,			16, 0,-1,-1,-1},
	{SurfaceFormat::SURFACE_G16R16F,		16, 0,1,-1,-1},
	{SurfaceFormat::SURFACE_A16B16G16R16F,	16, 0,1,2,3},
	{SurfaceFormat::SURFACE_R32F,			32, 0,-1,-1,-1},
	{SurfaceFormat::SURFACE_G32R32F,		32, 0,1,-1,-1},
	{SurfaceFormat::SURFACE_A32B32G32R32F,	32, 0,1,2,3},
};

const int PVRTC2_MIN_TEXWIDTH = 16; //202
const int PVRTC2_MIN_TEXHEIGHT = 8; //203
const int PVRTC4_MIN_TEXWIDTH = 8; //204
const int PVRTC4_MIN_TEXHEIGHT = 8; //205
const int ETC_MIN_TEXWIDTH = 4; //206
const int ETC_MIN_TEXHEIGHT = 4; //207

/** 
 * Returns left zero bit count before first non-zero bit.
 */
static inline int maskToShift( uint32_t mask ) //212
{
	int count = 0;
	uint32_t testBit = 1;
	if ( 0 == mask )
		return 32;

	while ( 0 == (mask & testBit) )
	{
		++count;
		testBit += testBit;
	}
	return count;
}

/** 
 * Returns number of non-zero bits in the dword.
 */
static inline int countBits( uint32_t mask ) //230
{
	int count = 0;
	uint32_t testBit = 1;
	while ( 0 != testBit )
	{
		if ( 0 != (mask&testBit) )
			++count;
		testBit += testBit;
	}
	return count;
}

/** 
 * Returns red component of R5G6B5 in range [0,255]. 
 */
static inline uint32_t getRedR5G6B5( uint32_t c ) //246
{
	return (c>>11) * 255 / 31;
}

/** 
 * Returns green component of R5G6B5 in range [0,255]. 
 */
static inline uint32_t getGreenR5G6B5( uint32_t c ) //254
{
	return ((c>>5)&0x3F) * 255 / 63;
}

/** 
 * Returns blue component of R5G6B5 in range [0,255]. 
 */
static inline uint32_t getBlueR5G6B5( uint32_t c ) //262
{
	return (c&0x1F) * 255 / 31;
}

/** 
 * Returns ARGB8888 from values in range [0,255]. 
 */
static inline uint32_t makeA8R8G8B8( uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha ) //270
{
	return (alpha<<24) + (red<<16) + (green<<8) + blue;
}

/** 
 * Returns R5G6B5 as ARGB8888. 
 */
static inline uint32_t convertR5G6B5toARGB8888( uint32_t c ) //278
{
	return makeA8R8G8B8( getRedR5G6B5(c), getGreenR5G6B5(c), getBlueR5G6B5(c), 0xFF );
}

/** 
 * Gets DXT1-3 block colors. 
 */
static inline void getBlockColorsA8R8G8B8( const DXTColBlock* colorBlock, uint32_t c[4] ) //286
{
	if ( colorBlock->col0 > colorBlock->col1 ) 
	{
		c[0] = convertR5G6B5toARGB8888( colorBlock->col0 );
		c[1] = convertR5G6B5toARGB8888( colorBlock->col1 );

		// Four-color block: derive the other two colors.
		// 00 = c[0], 01 = c[1], 10 = c[2], 11 = c[3]
		// These 2-bit codes correspond to the 2-bit fields 
		// stored in the 64-bit block.
		c[2] = makeA8R8G8B8( 
			(2*getRedR5G6B5(colorBlock->col0)+getRedR5G6B5(colorBlock->col1)+1)/3, 
			(2*getGreenR5G6B5(colorBlock->col0)+getGreenR5G6B5(colorBlock->col1)+1)/3,
			(2*getBlueR5G6B5(colorBlock->col0)+getBlueR5G6B5(colorBlock->col1)+1)/3,
			255 );

		c[3] = makeA8R8G8B8( 
			(getRedR5G6B5(colorBlock->col0)+2*getRedR5G6B5(colorBlock->col1)+1)/3, 
			(getGreenR5G6B5(colorBlock->col0)+2*getGreenR5G6B5(colorBlock->col1)+1)/3,
			(getBlueR5G6B5(colorBlock->col0)+2*getBlueR5G6B5(colorBlock->col1)+1)/3,
			255 );
	}	 
	else
	{ 
		c[0] = convertR5G6B5toARGB8888( colorBlock->col0 );
		c[1] = convertR5G6B5toARGB8888( colorBlock->col1 );

		// Three-color block: derive the other color.
		// 00 = c[0],  01 = c[1],  10 = c[2],  
		// 11 = transparent.
		// These 2-bit codes correspond to the 2-bit fields 
		// stored in the 64-bit block. 
		c[2] = makeA8R8G8B8( 
			(getRedR5G6B5(colorBlock->col0)+getRedR5G6B5(colorBlock->col1))/2,
			(getGreenR5G6B5(colorBlock->col0)+getGreenR5G6B5(colorBlock->col1))/2,
			(getBlueR5G6B5(colorBlock->col0)+getBlueR5G6B5(colorBlock->col1))/2,
			255 );

		c[3] = makeA8R8G8B8(0,0,0,0);
	}
}

/** 
 * Gets DXT4-5 block alpha values. 
 */
static inline void getBlockAlphas( const DXTAlphaBlock3BitLinear* alphaBlock, uint32_t a[8] )
{
	// 8-alpha or 6-alpha block?   
	a[0] = alphaBlock->alpha0;
	a[1] = alphaBlock->alpha1;

	if ( alphaBlock->alpha0 > alphaBlock->alpha1 )
	{    
		// 8-alpha block:  derive the other six alphas.
		// Bit code 000 = a[0], 001 = a[1], others are interpolated.
		a[2] = (6 * alphaBlock->alpha0 + 1 * alphaBlock->alpha1 + 3) / 7;		// Bit code 010
		a[3] = (5 * alphaBlock->alpha0 + 2 * alphaBlock->alpha1 + 3) / 7;		// Bit code 011
		a[4] = (4 * alphaBlock->alpha0 + 3 * alphaBlock->alpha1 + 3) / 7;		// Bit code 100
		a[5] = (3 * alphaBlock->alpha0 + 4 * alphaBlock->alpha1 + 3) / 7;		// Bit code 101
		a[6] = (2 * alphaBlock->alpha0 + 5 * alphaBlock->alpha1 + 3) / 7;		// Bit code 110
		a[7] = (1 * alphaBlock->alpha0 + 6 * alphaBlock->alpha1 + 3) / 7;		// Bit code 111  
	}    
	else
	{  
		// 6-alpha block.
		// Bit code 000 = a[0], 001 = a[1], others are interpolated.
		a[2] = (4 * alphaBlock->alpha0 + 1 * alphaBlock->alpha1 + 2) / 5;		// Bit code 010
		a[3] = (3 * alphaBlock->alpha0 + 2 * alphaBlock->alpha1 + 2) / 5;		// Bit code 011
		a[4] = (2 * alphaBlock->alpha0 + 3 * alphaBlock->alpha1 + 2) / 5;		// Bit code 100
		a[5] = (1 * alphaBlock->alpha0 + 4 * alphaBlock->alpha1 + 2) / 5;		// Bit code 101
		a[6] = 0;																// Bit code 110
		a[7] = 255;																// Bit code 111
	}
}

/** 
 * Reads ARGB8888 pixel value from DXT1-compressed texture. 
 */
static inline uint32_t getPixelDXT1( int x, int y, const void* data, int pitch ) //365
{
	int xblock = x >> 2;
	int yblock = y >> 2;

	const uint8_t* blockData = reinterpret_cast<const uint8_t*>(data) + xblock*8 + yblock*pitch;
	const DXTColBlock* colorBlock = reinterpret_cast<const DXTColBlock*>( blockData );

	uint32_t c[4];
	getBlockColorsA8R8G8B8( colorBlock, c );
	
	uint8_t b = colorBlock->rows[ y & 3 ];
	return c[ ((b>>(x&3)*2)&3) ];
}

/** 
 * Reads ARGB8888 pixel value from DXT2/3-compressed texture. 
 */
static inline uint32_t getPixelDXT3( int x, int y, const void* data, int pitch ) //383
{
	int xblock = x >> 2;
	int yblock = y >> 2;

	const uint8_t* blockData = reinterpret_cast<const uint8_t*>(data) + xblock*16 + yblock*pitch;
	const DXTAlphaBlockExplicit* alphaBlock = reinterpret_cast<const DXTAlphaBlockExplicit*>( blockData );
	const DXTColBlock* colorBlock = reinterpret_cast<const DXTColBlock*>( blockData+8 );

	uint32_t c[4];
	getBlockColorsA8R8G8B8( colorBlock, c );
	uint8_t b = colorBlock->rows[ y & 3 ];
	uint32_t color = c[ ((b>>(x&3)*2)&3) ];

	uint32_t alpha = ( alphaBlock->rows[y&3] >> (4*(x&3)) ) & 0xF;
	alpha = (alpha * 255) / 15;

	return (color&0xFFFFFF) + (alpha<<24);
}

/** 
 * Reads ARGB8888 pixel value from DXT4/5-compressed texture. 
 */
static inline uint32_t getPixelDXT5( int x, int y, const void* data, int pitch ) //406
{
	int xblock = x >> 2;
	int yblock = y >> 2;

	const uint8_t* blockData = reinterpret_cast<const uint8_t*>(data) + xblock*16 + yblock*pitch;
	const DXTAlphaBlock3BitLinear* alphaBlock = reinterpret_cast<const DXTAlphaBlock3BitLinear*>( blockData );
	const DXTColBlock* colorBlock = reinterpret_cast<const DXTColBlock*>( blockData+8 );

	uint32_t c[4];
	getBlockColorsA8R8G8B8( colorBlock, c );
	uint8_t b = colorBlock->rows[ y & 3 ];
	uint32_t color = c[ ((b>>(x&3)*2)&3) ];

	uint32_t a[8];
	getBlockAlphas( alphaBlock, a );
	
	// first two rows of 4 pixels each:
	const uint32_t mask = 0x00000007;		// bits = 00 00 01 11
	uint32_t bits = *reinterpret_cast<const uint32_t*>( alphaBlock->values );
	uint8_t alphaBits[4][4];
	alphaBits[0][0] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[0][1] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[0][2] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[0][3] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[1][0] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[1][1] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[1][2] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[1][3] = (uint8_t)( bits & mask );

	// now for last two rows:
	bits = *reinterpret_cast<const uint32_t*>( alphaBlock->values+3 );
	alphaBits[2][0] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[2][1] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[2][2] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[2][3] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[3][0] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[3][1] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[3][2] = (uint8_t)( bits & mask );
	bits >>= 3;
	alphaBits[3][3] = (uint8_t)( bits & mask );

	// get alpha value
	uint32_t alpha = a[ alphaBits[y&3][x&3] & 7 ];
	
	return (color&0xFFFFFF) + (alpha<<24);
}

SurfaceFormat::SurfaceFormat() :
	m_type( SurfaceFormat::SURFACE_UNKNOWN )
{
	assert( SURFACE_LAST == FORMATS );
}

SurfaceFormat::SurfaceFormat( const char* desc ) :
	m_type( SurfaceFormat::SURFACE_UNKNOWN )
{
	assert( SURFACE_LAST == FORMATS );
	for ( int i = 0 ; i < FORMATS ; ++i )
	{
		if ( !strcmp(FORMAT_NAMES[i],desc) )
		{
			m_type = (SurfaceFormatType)i;
			break;
		}
	}
}

SurfaceFormat::SurfaceFormat( SurfaceFormatType type ) : //648
	m_type( type )
{
	assert( (SurfaceFormatType)FORMATDESC[type][0] == type );
	assert( SURFACE_LAST == FORMATS );
}

SurfaceFormat::SurfaceFormat( int bitCount, uint32_t redMask, uint32_t greenMask, uint32_t blueMask, uint32_t alphaMask )
{
	m_type = SurfaceFormat::SURFACE_UNKNOWN;

	for ( int i = 0 ; i < FORMATS ; ++i )
	{
		if ( FORMATDESC[i][1] == (uint32_t)bitCount &&
			FORMATDESC[i][2] == (uint32_t)redMask &&
			FORMATDESC[i][3] == (uint32_t)greenMask &&
			FORMATDESC[i][4] == (uint32_t)blueMask &&
			FORMATDESC[i][5] == (uint32_t)alphaMask )
		{
			m_type = (SurfaceFormat::SurfaceFormatType)FORMATDESC[i][0];
		}
	}
}

SurfaceFormat::SurfaceFormatType SurfaceFormat::type() const
{
	return m_type;
}

int SurfaceFormat::bitsPerPixel() const
{
	return (int)FORMATDESC[m_type][1];
}

bool SurfaceFormat::hasAlpha() const
{
	return FORMATDESC[m_type][5] > 0 || compressed();
}

uint32_t SurfaceFormat::getChannelMask( int i ) const
{
	assert( i >= 0 && i < 4 );
	assert( !compressed() );

	if ( compressed() )
		return 0;
	else
		return FORMATDESC[m_type][2+i];
}

int SurfaceFormat::getChannelBitCount( int i ) const
{
	assert( i >= 0 && i < 4 );
	assert( !compressed() );

	if ( compressed() )
		return 0;
	else
		return countBits( FORMATDESC[m_type][2+i] );
}

int SurfaceFormat::paletteEntries() const
{
	if ( SURFACE_P8 == m_type )
		return 256;
	else if ( SURFACE_P4 == m_type )
		return 16;
	else
		return 0;
}

const char* SurfaceFormat::toString() const
{
	assert( m_type < SURFACE_LAST );
	return FORMAT_NAMES[m_type];
}

void SurfaceFormat::copyPixels( void* dst, const SurfaceFormat& dstpalfmt, const void* dstpal, 
	const SurfaceFormat& srcfmt, const void* src, const SurfaceFormat& srcpalfmt, const void* srcpal,
	int pixels ) const
{
	assert( !compressed() );
	assert( !srcfmt.compressed() );
	assert( srcfmt.m_type != SURFACE_UNKNOWN );
	assert( srcpalfmt.m_type != SURFACE_P4 && srcpalfmt.m_type != SURFACE_P8 );
	assert( dstpalfmt.m_type != SURFACE_P4 && dstpalfmt.m_type != SURFACE_P8 );
	assert( !srcpalfmt.palettized() );

	if ( m_type == srcfmt.m_type )
	{
		int bytes = (pixels * bitsPerPixel()) >> 3;
		memcpy( dst, src, bytes );
		return;
	}

	if ( !srcfmt.palettized() )
		srcpal = 0;

	if ( !compressed() && !srcfmt.compressed() )
	{
		if ( !srcfmt.palettized() )
			srcpal = 0;
		if ( !palettized() )
			dstpal = 0;

		const uint8_t*		srcbytes		= reinterpret_cast<const uint8_t*>( src );
		const uint8_t*		srcpalbytes		= reinterpret_cast<const uint8_t*>( srcpal );
		const int			srcpalentries	= srcfmt.paletteEntries();
		const int			srcbitcount		= srcfmt.bitsPerPixel();
		int					srcsubpix		= 0;
		const int			srcbitoffs		= (8-srcbitcount) & 7;
		const uint32_t*		srcfmtdesc		= &FORMATDESC[ (srcpal ? srcpalfmt.m_type : srcfmt.m_type) ][1];
		const uint32_t*		srcmask			= &srcfmtdesc[1];
		int					srcbits[4];
		int					srcshift[4];
		uint32_t 			srcval[4];
		float				srcvalf[4];
		const int 			srcpixbitcount	= srcfmtdesc[0];
		const int			srcpixsize		= srcpixbitcount >> 3;
		const uint8_t* 		srcpixbytes;

		uint8_t*			dstbytes		= reinterpret_cast<uint8_t*>( dst );
		const uint8_t*		dstpalbytes		= reinterpret_cast<const uint8_t*>( dstpal );
		const int			dstpalentries	= paletteEntries();
		const int			dstbitcount		= bitsPerPixel();
		int					dstsubpix		= 0;
		const uint32_t*		dstfmtdesc		= &FORMATDESC[ (dstpal ? dstpalfmt.m_type : m_type) ][1];
		const uint32_t*		dstmask			= &dstfmtdesc[1];
		int					dstbits[4];
		int					dstshift[4];
		uint32_t 			dstval[4];
		const int 			dstpixbitcount	= dstfmtdesc[0];
		const int			dstpixsize		= dstpixbitcount >> 3;
		const uint8_t* 		dstpixbytes;

		// compute aux channel variables
		for ( int i = 0 ; i < 4 ; ++i )
		{
			srcbits[i] = countBits( srcmask[i] );
			srcshift[i] = maskToShift( srcmask[i] );
			dstbits[i] = countBits( dstmask[i] );
			dstshift[i] = maskToShift( dstmask[i] );
		}

		for ( int i = 0 ; i < pixels ; ++i )
		{
			if ( 128 == i )
			{
				 i = i;
			}
			if ( srcfmt.hdr() )
			{
				// read HDR format
				assert( srcfmt.m_type-SURFACE_R16F < sizeof(HDR_INFO)/sizeof(HDR_INFO[0]) );
				const int* hdrinfo = HDR_INFO[srcfmt.m_type-SURFACE_R16F];
				for ( int k = 0 ; k < 4 ; ++k )
				{
					int ix = hdrinfo[2+k];
					if ( ix >= 0 )
					{
						assert( 16 == hdrinfo[1] || 32 == hdrinfo[1] );

						if ( 16 == hdrinfo[1] )
							srcvalf[k] = halfToFloat( reinterpret_cast<const uint16_t*>(srcbytes)[ix] );
						else
							srcvalf[k] = reinterpret_cast<const float*>(srcbytes)[ix];
					}
					else
					{
						srcvalf[k] = (k == 3 ? 1.f : 0.f);
					}
				}

				if ( !hdr() )
				{
					// clamp to A8B8G8R8, target not HDR
					for ( int k = 0 ; k < 4 ; ++k )
					{
						if ( srcvalf[k] < 0.f )
							srcval[k] = 0;
						else if ( srcvalf[k] > 1.f )
							srcval[k] = 255;
						else
							srcval[k] = int( srcvalf[k] * 255.f );
					}
				}
			}
			else // non-hdr source pixel format:
			{
				// apply palette if any
				if ( srcpal )
				{
					int ix = (*srcbytes >> (srcbitoffs-srcsubpix&7)) & (srcpalentries-1);
					assert( (unsigned)ix < (unsigned)srcpalentries ); // color index out of source palette range
					srcpixbytes = srcpalbytes + ix*srcpixsize;
				}
				else
				{
					srcpixbytes = srcbytes;
				}
				
				// read pixel data
				uint32_t srcpix = *srcpixbytes;
				switch ( srcpixbitcount )
				{
				case 32:	srcpix |= (uint32_t)srcpixbytes[3] << 24; // fall-through -> 24
				case 24:	srcpix |= (uint32_t)srcpixbytes[2] << 16; // fall-through -> 16
				case 16:	srcpix |= (uint32_t)srcpixbytes[1] << 8; break;
				}

				// convert pixel to A8B8G8R8
				for ( int k = 0 ; k < 4 ; ++k )
					srcval[k] = ( (srcpix & srcmask[k]) >> srcshift[k] ) << (8-srcbits[k]);

				if ( hdr() )
				{
					// convert to HDR, since dest is HDR
					for ( int k = 0 ; k < 4 ; ++k )
						srcvalf[k] = (float)srcval[k] * (1.f/255.f);
				}
			}
			
			// convert A8B8G8R8 to destination format
			if ( hdr() )
			{
				// write hdr
				assert( m_type-SURFACE_R16F < sizeof(HDR_INFO)/sizeof(HDR_INFO[0]) );
				const int* hdrinfo = HDR_INFO[m_type-SURFACE_R16F];

				for ( int k = 0 ; k < 4 ; ++k )
				{
					int ix = hdrinfo[2+k];
					if ( ix >= 0 )
					{
						assert( 16 == hdrinfo[1] || 32 == hdrinfo[1] );

						if ( 16 == hdrinfo[1] )
							reinterpret_cast<uint16_t*>(dstbytes)[ix] = floatToHalf( srcvalf[k] );
						else
							reinterpret_cast<float*>(dstbytes)[ix] = srcvalf[k];
					}
				}
			}
			else
			{
				uint32_t dstpix = uint32_t(-1);
				if ( dstpal )
				{
					// find best match in dst palette
					int mindist = 1<<30;
					dstpixbytes = dstpalbytes;
					for ( int n = 0 ; n < dstpalentries ; ++n )
					{
						// read dst palette data
						uint32_t pix = *dstpixbytes;
						switch ( dstpixbitcount )
						{
						case 32:	pix |= (uint32_t)dstpixbytes[3] << 24; // fall-through -> 24
						case 24:	pix |= (uint32_t)dstpixbytes[2] << 16; // fall-through -> 16
						case 16:	pix |= (uint32_t)dstpixbytes[1] << 8; break;
						}

						// convert dst palette data and compute distance to target color
						int dist = 0;
						for ( int k = 0 ; k < 4 ; ++k )
						{
							dstval[k] = ( (pix & dstmask[k]) >> dstshift[k] ) << (8-dstbits[k]);
							dist += (dstval[k]-srcval[k]) * (dstval[k]-srcval[k]);
						}
						
						// find closest color
						if ( dist < mindist )
						{
							mindist = dist;
							dstpix = n;
							if ( 0 == mindist )
								break;
						}
						
						dstpixbytes += dstpixsize;
					}
				}
				else
				{
					// convert channels to destination format
					for ( int k = 0 ; k < 4 ; ++k )
					{
						uint32_t dstv = ( srcval[k] >> (8-dstbits[k]) ) << dstshift[k];
						dstpix = (dstpix & ~dstmask[k]) | dstv;
						if ( 0 == srcbits[k] )
							dstpix |= dstmask[k];
					}
				}
				
				// write data
				switch ( dstbitcount )
				{
				case 32:	dstbytes[3] = (uint8_t)( dstpix >> 24 ); // fall-through -> 24
				case 24:	dstbytes[2] = (uint8_t)( dstpix >> 16 ); // fall-through -> 16
				case 16:	dstbytes[1] = (uint8_t)( dstpix >> 8 ); // fall-through -> 8
				case 8:		dstbytes[0] = (uint8_t)( dstpix ); break;
				case 4:		dstbytes[0] = (uint8_t)( dstbytes[0] & (~(0xF << dstsubpix)) );
							dstbytes[0] = (uint8_t)( dstbytes[0] + (dstpix << dstsubpix) ); break;
				}
			}

			srcsubpix += srcbitcount;
			srcbytes += srcsubpix>>3;
			srcsubpix &= 7;
			
			dstsubpix += dstbitcount;
			dstbytes += dstsubpix>>3;
			dstsubpix &= 7;
		}
	}
}

void SurfaceFormat::copyPixels( void* dst, int dstpitch, const SurfaceFormat& dstpalfmt, const void* dstpal,
	const SurfaceFormat& srcfmt, const void* src, int srcpitch, const SurfaceFormat& srcpalfmt, const void* srcpal,
	int width, int height ) const //971 | TODO: ADD PVRTC and ETC DECODE
{
	assert( !compressed() );
	assert( bitsPerPixel() >= 8 || !srcfmt.compressed() );

	const int bytesperpixel = bitsPerPixel()/8;

	for ( int y = 0 ; y < height ; ++y )
	{
		uint8_t* d = reinterpret_cast<uint8_t*>(dst) + y*dstpitch;

		switch ( srcfmt.m_type )
		{
		case SURFACE_DXT1:
			for ( int x = 0 ; x < width ; ++x )
			{
				uint32_t pix = getPixelDXT1( x, y, src, srcpitch );
				copyPixels( d, dstpalfmt, dstpal, SurfaceFormat::SURFACE_A8R8G8B8, &pix, SurfaceFormat(), 0, 1 );
				d += bytesperpixel;
			}
			break;

		case SURFACE_DXT3:
			for ( int x = 0 ; x < width ; ++x )
			{
				uint32_t pix = getPixelDXT3( x, y, src, srcpitch );
				copyPixels( d, dstpalfmt, dstpal, SurfaceFormat::SURFACE_A8R8G8B8, &pix, SurfaceFormat(), 0, 1 );
				d += bytesperpixel;
			}
			break;

		case SURFACE_DXT5:
			for ( int x = 0 ; x < width ; ++x )
			{
				uint32_t pix = getPixelDXT5( x, y, src, srcpitch );
				copyPixels( d, dstpalfmt, dstpal, SurfaceFormat::SURFACE_A8R8G8B8, &pix, SurfaceFormat(), 0, 1 );
				d += bytesperpixel;
			}
			break;
		case SURFACE_PVRTC_RGB_2BPP:
		case SURFACE_PVRTC_RGBA_2BPP:
		case SURFACE_PVRTC_RGB_4BPP:
		case SURFACE_PVRTC_RGBA_4BPP:
			
			break;
		case SURFACE_ETC1_RGB_4BPP:
			//for (int x = 0; x < width; ++x)
			//{
			//	uint32_t pix = decompressETC(src, width, height, d, 0);
			//	copyPixels(d, dstpalfmt, dstpal, SurfaceFormat::SURFACE_A8R8G8B8, &pix, SurfaceFormat(), 0, 1);
			//	d += bytesperpixel;
			//}
			break;

		default:{
			const uint8_t* s = reinterpret_cast<const uint8_t*>(src) + y*srcpitch;
			copyPixels( d, dstpalfmt, dstpal, srcfmt, s, srcpalfmt, srcpal, width );
			break;}
		}
	}

}

void SurfaceFormat::getPixel( int x, int y,
	const void* data, int pitch, 
	const SurfaceFormat& palfmt, const void* pal,
	float* rgba ) const
{
	uint32_t pix = 0;

	switch ( m_type )
	{
	case SURFACE_DXT1:
		pix = getPixelDXT1( x, y, data, pitch );
		break;

	case SURFACE_DXT3:	
		pix = getPixelDXT3( x, y, data, pitch );
		break;

	case SURFACE_DXT5:
		pix = getPixelDXT5( x, y, data, pitch );
		break;

	default:{
		int pixelbytes = (int)FORMATDESC[m_type][1] >> 3;
		const uint8_t* src = reinterpret_cast<const uint8_t*>(data) + y*pitch + x*pixelbytes;
		SurfaceFormat(SURFACE_A8R8G8B8).copyPixels( &pix, SurfaceFormat(), 0, *this, src, palfmt, pal, 1 );
		}
	}

	uint8_t* buf = (uint8_t*)&pix;
	rgba[2] = (float)buf[0] * (1.f/255.f);
	rgba[1] = (float)buf[1] * (1.f/255.f);
	rgba[0] = (float)buf[2] * (1.f/255.f);
	rgba[3] = (float)buf[3] * (1.f/255.f);
}

int SurfaceFormat::getMemoryUsage( int w, int h ) const //1091
{
	int bytes = 0;

	if ( compressed() )
	{
		w += 3;
		h += 3;
		w >>= 2;
		h >>= 2;

		switch ( m_type )
		{
		case SurfaceFormat::SURFACE_DXT1:
			bytes = (w*h) << 3;
			break;

		case SurfaceFormat::SURFACE_DXT3:
		case SurfaceFormat::SURFACE_DXT5:
			bytes = (w*h) << 4;
			break;
        case SurfaceFormat::SURFACE_PVRTC_RGB_2BPP: //Add PVRTC RGB 2BPP
        case SurfaceFormat::SURFACE_PVRTC_RGBA_2BPP:
			if (w < 16)
            {
                w = 16;
            }
            if (h < 8)
            {
                h = 8;
            }
            bytes = (w*h*bitsPerPixel())>>3;
			break;
        case SurfaceFormat::SURFACE_PVRTC_RGB_4BPP: //Add PVRTC RGB 4BPP
        case SurfaceFormat::SURFACE_PVRTC_RGBA_4BPP:
			if (w < 8)
            {
                w = 8;
            }
            if (h < 8) //May be redundant
            {
                h = 8;
            }
            bytes = (w*h*bitsPerPixel())>>3;
			break;
        case SurfaceFormat::SURFACE_ETC1_RGB_4BPP: //Add ETC1 RGB 4BPP
			if (w < 4)
            {
                w = 4;
            }
            if (h < 4)
            {
                h = 4;
            }
            bytes = (w*h*bitsPerPixel())>>3;
			break;
		}
	}
	else
	{
		bytes = (w*h*bitsPerPixel())>>3;
	}

	return bytes;
}

//Carbon copies of functions from the PVR SDK unlike importing the PVR SDK header, they simply copied everything and stuffed it here with minimal changes (or a very old version?), if it works it works :shrug:
//Closer to theirs (they used version 3.1@2308999 [pvrtt 4.04, according to libgles_cm.dll + libEGL.dll + libGLESv2.dll] which is lost):
/*
 https://github.com/AprilAndFriends/april/blob/master/aprilpix/src/PowerVR-SDK/PVRTDecompress.cpp
 https://github.com/DK22Pac/CTW-Mobile-Explorer/blob/master/PVRTC/PVRTDecompress.cpp
 https://github.com/EKA2L1/EKA2L1/blob/master/src/emu/drivers/src/graphics/backend/ogl/pvrt-dec.cpp
 https://github.com/HappyGames/cocos3d-x/blob/master/cocos3d/Engine/libcocos3d/cc3PVR/PVRT/PVRTDecompress.cpp
 https://github.com/JoeDavisIMG/Native_SDK/blob/master/Framework/PVRAssets/Texture/PVRTDecompress.cpp
 https://github.com/Rinnegatamante/Vita3K/blob/master/vita3k/renderer/src/pvrt-dec.cpp
 https://github.com/Vita3K/Vita3K/blob/master/vita3k/renderer/src/texture/pvrt-dec.cpp
 https://github.com/Vita3K/Vita3K-Android/blob/master/vita3k/renderer/src/texture/pvrt-dec.cpp
 https://github.com/Zweronz/PVRT-SDK/blob/master/src/PVRTDecompress.cpp
 https://github.com/anonymousjustice/pvr-pi/blob/master/SDKPackage_OGLES2/Tools/PVRTDecompress.cpp
 https://github.com/cappah/powervr-graphics-native-sdk/blob/master/framework/PVRCore/Texture/PVRTDecompress.cpp
 https://github.com/djlaserman/Vita3K/blob/master/vita3k/renderer/src/pvrt-dec.cpp
 https://github.com/elix22/Native_SDK/blob/master/framework/PVRCore/Texture/PVRTDecompress.cpp
 https://github.com/galek/et-engine/blob/master/src/imaging/pvrdecompressor.cpp
 https://github.com/jeanlemotan/silkopter/blob/master/q/src/res/Impl/pvrtc/PVRTDecompress.cpp
 https://github.com/johndpope/Medusa/blob/master/Medusa/Medusa/Lib/Common/PVR/PVRTDecompress.cpp
 https://github.com/korenkonder/Vita3K/blob/master/vita3k/renderer/src/texture/pvrt-dec.cpp
 https://github.com/linuxaged/Native_SDK/blob/master/Framework/PVRAssets/Texture/PVRTDecompress.cpp
 https://github.com/paulvortex/RwgTex/blob/master/libs/pvrtextool/source/PVRTDecompress.cpp
 https://github.com/pent0/pvrtc/blob/master/src/pvrtc.cpp
 https://github.com/phoenixzz/VoronoiMapGen/blob/master/SGPLibraryCode/modules/sgp_render/opengles2/PVRTTexture/PVRTDecompress.cpp
 https://github.com/reybits/simple-viewer-gl/blob/master/src/formats/PVRTDecompress.cpp
 https://github.com/serhii-rieznik/et-engine/blob/master/include/et/imaging/pvrdecompressor.cpp
 https://github.com/stubma/WiEngine/blob/master/jni/libpvr/PVRTDecompress.cpp
 https://github.com/Vita3K/Vita3K/blob/master/vita3k/renderer/src/texture/pvrt-dec.cpp

 https://github.com/stuartcaunt/isgl3d/blob/master/external/PowerVR_SDK-2.0.9/PVRTDecompress.cpp (2.0.9)
*/

//https://github.com/anonymousjustice/pvr-pi/blob/master/SDKPackage_OGLES2/Builds/sdkver.h (2.10@863987)

//https://github.com/gildor2/UEViewer/blob/master/libs/PowerVR/PVRTDecompress.cpp
//https://github.com/powervr-graphics/Native_SDK/blob/master/framework/PVRCore/texture/PVRTDecompress.cpp
//https://github.com/axmolengine/axmol/blob/master/core/base/pvr.cpp
//https://github.com/Vita3K/Vita3K/blob/master/vita3k/renderer/src/texture/pvrt-dec.cpp
//https://github.com/stubma/WiEngine/blob/master/jni/libpvr/PVRTDecompress.cpp
//https://github.com/ChristophePretty/cocos2d-x/blob/master/cocos/base/pvr.cpp
//https://github.com/mewbak/sau/blob/master/src/fmt_pvr.c
//https://github.com/imesense-forks/castano-nvidia-texture-tools/blob/master/extern/pvrtextool/Include/PVRTDecompress.h
//https://github.com/henyouqian/arrow/blob/master/lw/externalLib/PVRTools/include/PVRTools/PVRTDecompress.h
//https://github.com/drawcode/ddengine/blob/master/ddengine/include/PowerVR/PVRTDecompress.h
//https://github.com/s2ack/ti-gsdk/blob/master/GFX_Linux_SDK/OGLES/SDKPackage/Utilities/PVRTexTool/Library/Include/PVRTDecompress.h
//https://github.com/jcayzac/random-stuff/blob/master/ios-LittleBombers/src/pvrt/PVRTDecompress.cpp
//https://github.com/siketyan/DePvr/blob/master/DePvr.Unmanaged/include/PVRTDecompress.h
//https://github.com/QianMo/GPU-Pro-Books-Source-Code/
//https://github.com/cocos3d/cocos3d/blob/master/cocos3d/cc3PVR/PVRT/PVRTDecompress.cpp
//https://github.com/cocos3d/cocos3d/blob/d4092affdb81d84307bde09d4c638f1352454af5/cocos3d/cc3PVR/PVRT_3.1/PVRTDecompress.cpp (3.1, this code is based off this)

//https://github.com/hirakuni45/glfw3_app/blob/7034306982062a3b3ae50081a1a0ab08a704d945/glfw3_app/common/img_io/pvr_io.hpp#L137 //?

//Hacks since those aren't typedefs
#define PVRTint32 int
#define PVRTuint32 uint32_t
#define PVRTuint8 uint8_t
#define PVRT_MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define PVRT_MAX(a,b)            (((a) > (b)) ? (a) : (b))
#define PVRT_CLAMP(x, l, h)      (PVRT_MIN((h), PVRT_MAX((x), (l))))

struct Pixel32 //1148
{
	PVRTint32 red, green, blue, alpha;
};

struct Pixel128S //1152
{
	PVRTint32 red, green, blue, alpha;
};

struct PVRTCWord //1156
{
	PVRTuint32  u32ModulationData;
	PVRTuint32  u32ColourData;
};

struct PVRTCWordIndices //1161
{
	int P[2], Q[2], R[2], S[2]; //1163
};

static Pixel32 getColourA(PVRTuint32 u32ColourData) //1166
{
	Pixel32 colour;

	// Opaque Colour Mode - RGB 554
	if ((u32ColourData & 0x8000) != 0)
	{
		colour.red   = (PVRTuint8)((u32ColourData & 0x7c00) >> 10); // 5->5 bits
		colour.green = (PVRTuint8)((u32ColourData & 0x3e0)  >> 5); // 5->5 bits
		colour.blue  = (PVRTuint8)(u32ColourData  & 0x1e) | ((u32ColourData & 0x1e) >> 4); // 4->5 bits
		colour.alpha = (PVRTuint8)0xf;// 0->4 bits
	}
	// Transparent Colour Mode - ARGB 3443
	else
	{	
		colour.red   = (PVRTuint8)((u32ColourData & 0xf00)  >> 7) | ((u32ColourData & 0xf00) >> 11); // 4->5 bits
		colour.green = (PVRTuint8)((u32ColourData & 0xf0)   >> 3) | ((u32ColourData & 0xf0)  >> 7); // 4->5 bits
		colour.blue  = (PVRTuint8)((u32ColourData & 0xe)    << 1) | ((u32ColourData & 0xe)   >> 2); // 3->5 bits
		colour.alpha = (PVRTuint8)((u32ColourData & 0x7000) >> 11);// 3->4 bits - note 0 at right
	}

	return colour;
}

static Pixel32 getColourB(PVRTuint32 u32ColourData) //1186
{ 
	Pixel32 colour;

	// Opaque Colour Mode - RGB 555
	if (u32ColourData & 0x80000000)
	{	
		colour.red   = (PVRTuint8)((u32ColourData & 0x7c000000) >> 26); // 5->5 bits 
		colour.green = (PVRTuint8)((u32ColourData & 0x3e00000)  >> 21); // 5->5 bits
		colour.blue  = (PVRTuint8)((u32ColourData & 0x1f0000)   >> 16); // 5->5 bits
		colour.alpha = (PVRTuint8)0xf;// 0 bits
	}
	// Transparent Colour Mode - ARGB 3444
	else
	{	
		colour.red   = (PVRTuint8)(((u32ColourData & 0xf000000)  >> 23) | ((u32ColourData & 0xf000000) >> 27)); // 4->5 bits
		colour.green = (PVRTuint8)(((u32ColourData & 0xf00000)   >> 19) | ((u32ColourData & 0xf00000)  >> 23)); // 4->5 bits
		colour.blue  = (PVRTuint8)(((u32ColourData & 0xf0000)    >> 15) | ((u32ColourData & 0xf0000)   >> 19)); // 4->5 bits
		colour.alpha = (PVRTuint8)((u32ColourData & 0x70000000) >> 27);// 3->4 bits - note 0 at right
	}

	return colour;
}

static void interpolateColours(Pixel32 P, Pixel32 Q, Pixel32 R, Pixel32 S, //1206, following mangled symbol
						Pixel128S *pPixel, PVRTuint8 ui8Bpp)
{
	PVRTuint32 ui32WordWidth=4;
	PVRTuint32 ui32WordHeight=4;
	if (ui8Bpp==2)
		ui32WordWidth=8;

	//Convert to int 32.
	Pixel128S hP = {(PVRTint32)P.red,(PVRTint32)P.green,(PVRTint32)P.blue,(PVRTint32)P.alpha};
	Pixel128S hQ = {(PVRTint32)Q.red,(PVRTint32)Q.green,(PVRTint32)Q.blue,(PVRTint32)Q.alpha};
	Pixel128S hR = {(PVRTint32)R.red,(PVRTint32)R.green,(PVRTint32)R.blue,(PVRTint32)R.alpha};
	Pixel128S hS = {(PVRTint32)S.red,(PVRTint32)S.green,(PVRTint32)S.blue,(PVRTint32)S.alpha};

	//Get vectors.
	Pixel128S QminusP = {hQ.red - hP.red, hQ.green - hP.green, hQ.blue - hP.blue, hQ.alpha - hP.alpha};	
	Pixel128S SminusR = {hS.red - hR.red, hS.green - hR.green, hS.blue - hR.blue, hS.alpha - hR.alpha};	

	//Multiply colours.
	hP.red		*=	ui32WordWidth;
	hP.green	*=	ui32WordWidth;
	hP.blue		*=	ui32WordWidth;
	hP.alpha	*=	ui32WordWidth;
	hR.red		*=	ui32WordWidth;
	hR.green	*=	ui32WordWidth;
	hR.blue		*=	ui32WordWidth;
	hR.alpha	*=	ui32WordWidth;
	
	if (ui8Bpp==2)
	{
		//Loop through pixels to achieve results.
		for (unsigned int x=0; x < ui32WordWidth; x++)
		{			
			Pixel128S Result={4*hP.red, 4*hP.green, 4*hP.blue, 4*hP.alpha};
			Pixel128S dY = {hR.red - hP.red, hR.green - hP.green, hR.blue - hP.blue, hR.alpha - hP.alpha};	

			for (unsigned int y=0; y < ui32WordHeight; y++)				
			{
				pPixel[y*ui32WordWidth+x].red   = (PVRTint32)((Result.red   >> 7) + (Result.red   >> 2));
				pPixel[y*ui32WordWidth+x].green = (PVRTint32)((Result.green >> 7) + (Result.green >> 2));
				pPixel[y*ui32WordWidth+x].blue  = (PVRTint32)((Result.blue  >> 7) + (Result.blue  >> 2));
				pPixel[y*ui32WordWidth+x].alpha = (PVRTint32)((Result.alpha >> 5) + (Result.alpha >> 1));				

				Result.red		+= dY.red;
				Result.green	+= dY.green;
				Result.blue		+= dY.blue;
				Result.alpha	+= dY.alpha;
			}			

			hP.red		+= QminusP.red;
			hP.green	+= QminusP.green;
			hP.blue		+= QminusP.blue;
			hP.alpha	+= QminusP.alpha;

			hR.red		+= SminusR.red;
			hR.green	+= SminusR.green;
			hR.blue		+= SminusR.blue;
			hR.alpha	+= SminusR.alpha;
		}
	}
	else
	{
		//Loop through pixels to achieve results.
		for (unsigned int y=0; y < ui32WordHeight; y++)
		{			
			Pixel128S Result={4*hP.red, 4*hP.green, 4*hP.blue, 4*hP.alpha};
			Pixel128S dY = {hR.red - hP.red, hR.green - hP.green, hR.blue - hP.blue, hR.alpha - hP.alpha};	

			for (unsigned int x=0; x < ui32WordWidth; x++)				
			{
				pPixel[y*ui32WordWidth+x].red   = (PVRTint32)((Result.red   >> 6) + (Result.red   >> 1));
				pPixel[y*ui32WordWidth+x].green = (PVRTint32)((Result.green >> 6) + (Result.green >> 1));
				pPixel[y*ui32WordWidth+x].blue  = (PVRTint32)((Result.blue  >> 6) + (Result.blue  >> 1));
				pPixel[y*ui32WordWidth+x].alpha = (PVRTint32)((Result.alpha >> 4) + (Result.alpha));				

				Result.red += dY.red;
				Result.green += dY.green;
				Result.blue += dY.blue;
				Result.alpha += dY.alpha;
			}			

			hP.red += QminusP.red;
			hP.green += QminusP.green;
			hP.blue += QminusP.blue;
			hP.alpha += QminusP.alpha;

			hR.red += SminusR.red;
			hR.green += SminusR.green;
			hR.blue += SminusR.blue;
			hR.alpha += SminusR.alpha;
		}
	}
}

static void unpackModulations(const PVRTCWord& word, int offsetX, int offsetY, PVRTint32 i32ModulationValues[16][8], PVRTint32 i32ModulationModes[16][8], PVRTuint8 ui8Bpp) //1283
{	
	PVRTuint32 WordModMode = word.u32ColourData & 0x1;
	PVRTuint32 ModulationBits = word.u32ModulationData;

	// Unpack differently depending on 2bpp or 4bpp modes.
	if (ui8Bpp==2)
	{
		if(WordModMode)
		{
			// determine which of the three modes are in use:

			// If this is the either the H-only or V-only interpolation mode...
			if(ModulationBits & 0x1)
			{
				// look at the "LSB" for the "centre" (V=2,H=4) texel. Its LSB is now
				// actually used to indicate whether it's the H-only mode or the V-only...

				// The centre texel data is the at (y==2, x==4) and so its LSB is at bit 20.
				if(ModulationBits & (0x1 << 20))
				{
					// This is the V-only mode
					WordModMode = 3; 
				}
				else
				{
					// This is the H-only mode
					WordModMode = 2; 
				}

				// Create an extra bit for the centre pixel so that it looks like
				// we have 2 actual bits for this texel. It makes later coding much easier.
				if(ModulationBits & (0x1 << 21))
				{
					// set it to produce code for 1.0
					ModulationBits |= (0x1 << 20); 
				}
				else
				{
					// clear it to produce 0.0 code
					ModulationBits &= ~(0x1 << 20);
				}
			}// end if H-Only or V-Only interpolation mode was chosen

			if(ModulationBits & 0x2)
			{
				ModulationBits |= 0x1; /*set it*/
			}
			else
			{
				ModulationBits &= ~0x1; /*clear it*/
			}

			// run through all the pixels in the block. Note we can now treat all the
			// "stored" values as if they have 2bits (even when they didn't!)
			for(int y = 0; y < 4; y++)
			{
				for(int x = 0; x < 8; x++)
				{
					i32ModulationModes[x+offsetX][y+offsetY] = WordModMode;				

					// if this is a stored value...
					if(((x^y)&1) == 0)
					{
						i32ModulationValues[x+offsetX][y+offsetY] = ModulationBits & 3;						
						ModulationBits >>= 2;
					}
				}
			} // end for y
		}
		// else if direct encoded 2bit mode - i.e. 1 mode bit per pixel
		else
		{
			for(int y = 0; y < 4; y++)
			{
				for(int x = 0; x < 8; x++)
				{
					i32ModulationModes[x+offsetX][y+offsetY] = WordModMode;					

					/*
					// double the bits so 0=> 00, and 1=>11
					*/
					if(ModulationBits & 1)
					{
						i32ModulationValues[x+offsetX][y+offsetY] = 0x3;						
					}
					else
					{
						i32ModulationValues[x+offsetX][y+offsetY] = 0x0;					
					}
					ModulationBits >>= 1;
				}
			}// end for y
		}		
	}
	else
	{
		//Much simpler than the 2bpp decompression, only two modes, so the n/8 values are set directly.
		// run through all the pixels in the word.
		if (WordModMode)
		{
			for(int y = 0; y < 4; y++)
			{
				for(int x = 0; x < 4; x++)
				{
					i32ModulationValues[y+offsetY][x+offsetX] = ModulationBits & 3;
					//if (i32ModulationValues==0) {}; don't need to check 0, 0 = 0/8.
					if (i32ModulationValues[y+offsetY][x+offsetX]==1) { i32ModulationValues[y+offsetY][x+offsetX]=4;}
					else if (i32ModulationValues[y+offsetY][x+offsetX]==2) { i32ModulationValues[y+offsetY][x+offsetX]=14;} //+10 tells the decompressor to punch through alpha.
					else if (i32ModulationValues[y+offsetY][x+offsetX]==3) { i32ModulationValues[y+offsetY][x+offsetX]=8;}
					ModulationBits >>= 2;
				} // end for x
			} // end for y
		}
		else
		{
			for(int y = 0; y < 4; y++)
			{
				for(int x = 0; x < 4; x++)
				{
					i32ModulationValues[y+offsetY][x+offsetX] = ModulationBits & 3;
					i32ModulationValues[y+offsetY][x+offsetX]*=3;
					if (i32ModulationValues[y+offsetY][x+offsetX]>3) i32ModulationValues[y+offsetY][x+offsetX]-=1;
					ModulationBits >>= 2;
				} // end for x
			} // end for y
		}
	}
}

static PVRTint32 getModulationValues(PVRTint32 i32ModulationValues[16][8],PVRTint32 i32ModulationModes[16][8],PVRTuint32 xPos,PVRTuint32 yPos,PVRTuint8 ui8Bpp) //1383
{
	if (ui8Bpp==2)
	{
		const int RepVals0[4] = {0, 3, 5, 8};				

		// extract the modulation value. If a simple encoding
		if(i32ModulationModes[xPos][yPos]==0)
		{
			return RepVals0[i32ModulationValues[xPos][yPos]];
		}
		else
		{
			// if this is a stored value
			if(((xPos^yPos)&1)==0)
			{
				return RepVals0[i32ModulationValues[xPos][yPos]];				
			}

			// else average from the neighbours
			// if H&V interpolation...
			else if(i32ModulationModes[xPos][yPos] == 1)
			{
				return (RepVals0[i32ModulationValues[xPos][yPos-1]] + 
					RepVals0[i32ModulationValues[xPos][yPos+1]] + 
					RepVals0[i32ModulationValues[xPos-1][yPos]] + 
					RepVals0[i32ModulationValues[xPos+1][yPos]] + 2) / 4;				
			}
			// else if H-Only
			else if(i32ModulationModes[xPos][yPos] == 2)
			{
				return (RepVals0[i32ModulationValues[xPos-1][yPos]] + 
					RepVals0[i32ModulationValues[xPos+1][yPos]] + 1) / 2;
			}
			// else it's V-Only
			else
			{
				return (RepVals0[i32ModulationValues[xPos][yPos-1]] + 
					RepVals0[i32ModulationValues[xPos][yPos+1]] + 1) / 2;
			}
		}
	}
	else if (ui8Bpp==4)
		return i32ModulationValues[xPos][yPos];

	return 0;
}

static inline void pvrtcGetDecompressedPixels(const PVRTCWord& P, const PVRTCWord& Q, //1422
								const PVRTCWord& R, const PVRTCWord& S, //1423
								Pixel32 *pColourData, //1424
								PVRTuint8 ui8Bpp) //1425
{
	//4bpp only needs 8*8 values, but 2bpp needs 16*8, so rather than wasting processor time we just statically allocate 16*8.
	PVRTint32 i32ModulationValues[16][8];
	//Only 2bpp needs this.
	PVRTint32 i32ModulationModes[16][8];
	//4bpp only needs 16 values, but 2bpp needs 32, so rather than wasting processor time we just statically allocate 32.
	Pixel128S upscaledColourA[32];
	Pixel128S upscaledColourB[32];

	PVRTuint32 ui32WordWidth=4;
	PVRTuint32 ui32WordHeight=4;
	if (ui8Bpp==2)
		ui32WordWidth=8;

	//Get the modulations from each word.
	unpackModulations(P, 0, 0, i32ModulationValues, i32ModulationModes, ui8Bpp);
	unpackModulations(Q, ui32WordWidth, 0, i32ModulationValues, i32ModulationModes, ui8Bpp);
	unpackModulations(R, 0, ui32WordHeight, i32ModulationValues, i32ModulationModes, ui8Bpp);
	unpackModulations(S, ui32WordWidth, ui32WordHeight, i32ModulationValues, i32ModulationModes, ui8Bpp);

	// Bilinear upscale image data from 2x2 -> 4x4
	interpolateColours(getColourA(P.u32ColourData), getColourA(Q.u32ColourData), 
		getColourA(R.u32ColourData), getColourA(S.u32ColourData), 
		upscaledColourA, ui8Bpp);
	interpolateColours(getColourB(P.u32ColourData), getColourB(Q.u32ColourData), 
		getColourB(R.u32ColourData), getColourB(S.u32ColourData), 
		upscaledColourB, ui8Bpp);

	for (unsigned int y=0; y < ui32WordHeight; y++)
	{
		for (unsigned int x=0; x < ui32WordWidth; x++)
		{
			PVRTint32 mod = getModulationValues(i32ModulationValues,i32ModulationModes,x+ui32WordWidth/2,y+ui32WordHeight/2,ui8Bpp);
			bool punchthroughAlpha=false;
			if (mod>10) {punchthroughAlpha=true; mod-=10;}

			Pixel128S result;				
			result.red   = (upscaledColourA[y*ui32WordWidth+x].red * (8-mod) + upscaledColourB[y*ui32WordWidth+x].red * mod) / 8;
			result.green = (upscaledColourA[y*ui32WordWidth+x].green * (8-mod) + upscaledColourB[y*ui32WordWidth+x].green * mod) / 8;
			result.blue  = (upscaledColourA[y*ui32WordWidth+x].blue * (8-mod) + upscaledColourB[y*ui32WordWidth+x].blue * mod) / 8;
			if (punchthroughAlpha) result.alpha = 0;
			else result.alpha = (upscaledColourA[y*ui32WordWidth+x].alpha * (8-mod) + upscaledColourB[y*ui32WordWidth+x].alpha * mod) / 8;

			//Convert the 32bit precision result to 8 bit per channel colour.
			if (ui8Bpp==2)
			{
				pColourData[y*ui32WordWidth+x].red = (PVRTuint8)result.red;
				pColourData[y*ui32WordWidth+x].green = (PVRTuint8)result.green;
				pColourData[y*ui32WordWidth+x].blue = (PVRTuint8)result.blue;
				pColourData[y*ui32WordWidth+x].alpha = (PVRTuint8)result.alpha;
			}
			else if (ui8Bpp==4)
			{
				pColourData[y+x*ui32WordHeight].red = (PVRTuint8)result.red;
				pColourData[y+x*ui32WordHeight].green = (PVRTuint8)result.green;
				pColourData[y+x*ui32WordHeight].blue = (PVRTuint8)result.blue;
				pColourData[y+x*ui32WordHeight].alpha = (PVRTuint8)result.alpha;				
			}
		}
	}	
}

static inline unsigned int wrapWordIndex(unsigned int numWords, int word) //1476
{
	return ((word + numWords) % numWords);
}

#if defined(_DEBUG)
static inline bool isPowerOf2(unsigned int input)
{
	unsigned int minus1;

	if (!input) return 0;

	minus1 = input - 1;
	return ((input | minus1) == (input ^ minus1));
}
#endif

static PVRTuint32 TwiddleUV(PVRTuint32 XSize, PVRTuint32 YSize, PVRTuint32 XPos, PVRTuint32 YPos) //1489
{
	//Initially assume X is the larger size.
	PVRTuint32 MinDimension=XSize;
	PVRTuint32 MaxValue=YPos;
	PVRTuint32 Twiddled=0;
	PVRTuint32 SrcBitPos=1;
	PVRTuint32 DstBitPos=1;
	int ShiftCount=0;

	//Check the sizes are valid.
	_ASSERT(YPos < YSize); //1493 in ABS 3.0.0
	_ASSERT(XPos < XSize); //1494 in ABS 3.0.0
	_ASSERT(isPowerOf2(YSize)); //1495 in ABS 3.0.0, Ok this function exists but it's not in DWARF?
	_ASSERT(isPowerOf2(XSize)); //1496 in ABS 3.0.0, Ok this function exists but it's not in DWARF?

	//If Y is the larger dimension - switch the min/max values.
	if(YSize < XSize)
	{
		MinDimension = YSize;
		MaxValue	 = XPos;
	}

	// Step through all the bits in the "minimum" dimension
	while(SrcBitPos < MinDimension)
	{
		if(YPos & SrcBitPos)
		{
			Twiddled |= DstBitPos;
		}

		if(XPos & SrcBitPos)
		{
			Twiddled |= (DstBitPos << 1);
		}

		SrcBitPos <<= 1;
		DstBitPos <<= 2;
		ShiftCount += 1;
	}

	// Prepend any unused bits
	MaxValue >>= ShiftCount;
	Twiddled |=  (MaxValue << (2*ShiftCount));

	return Twiddled;
}

static inline void mapDecompressedData(Pixel32* pOutput, int width, //1526
						 const Pixel32 *pWord,
						 const PVRTCWordIndices &words,
						 const PVRTuint8 ui8Bpp)
{
	PVRTuint32 ui32WordWidth=4;
	PVRTuint32 ui32WordHeight=4;
	if (ui8Bpp==2)
		ui32WordWidth=8;

	for (unsigned int y=0; y < ui32WordHeight/2; y++)
	{
		for (unsigned int x=0; x < ui32WordWidth/2; x++)
		{
			pOutput[(((words.P[1] * ui32WordHeight) + y + ui32WordHeight/2)
				* width + words.P[0] *ui32WordWidth + x + ui32WordWidth/2)]	= pWord[y*ui32WordWidth+x];			// map P

			pOutput[(((words.Q[1] * ui32WordHeight) + y + ui32WordHeight/2)	
				* width + words.Q[0] *ui32WordWidth + x)]					= pWord[y*ui32WordWidth+x+ui32WordWidth/2];		// map Q

			pOutput[(((words.R[1] * ui32WordHeight) + y)						
				* width + words.R[0] *ui32WordWidth + x + ui32WordWidth/2)]	= pWord[(y+ui32WordHeight/2)*ui32WordWidth+x];		// map R

			pOutput[(((words.S[1] * ui32WordHeight) + y)						
				* width + words.S[0] *ui32WordWidth + x)]					= pWord[(y+ui32WordHeight/2)*ui32WordWidth+x+ui32WordWidth/2];	// map S
		}
	}
}

static inline int pvrtcDecompress(	PVRTuint8 *pCompressedData, //1554
							Pixel32 *pDecompressedData,
							PVRTuint32 ui32Width,
							PVRTuint32 ui32Height,
							PVRTuint8 ui8Bpp)
{
	PVRTuint32 ui32WordWidth=4;
	PVRTuint32 ui32WordHeight=4;
	if (ui8Bpp==2)
		ui32WordWidth=8;

	PVRTuint32 *pWordMembers = (PVRTuint32 *)pCompressedData;
	Pixel32 *pOutData = pDecompressedData;

	// Calculate number of words
	int i32NumXWords = (int)(ui32Width / ui32WordWidth);
	int i32NumYWords = (int)(ui32Height / ui32WordHeight);

	// Structs used for decompression
	PVRTCWordIndices indices;
	Pixel32 *pPixels;
	pPixels = (Pixel32*)malloc(ui32WordWidth*ui32WordHeight*sizeof(Pixel32));
	
	// For each row of words
	for(int wordY=-1; wordY < i32NumYWords-1; wordY++)
	{
		// for each column of words
		for(int wordX=-1; wordX < i32NumXWords-1; wordX++)
		{
			indices.P[0] = wrapWordIndex(i32NumXWords, wordX);
			indices.P[1] = wrapWordIndex(i32NumYWords, wordY);
			indices.Q[0] = wrapWordIndex(i32NumXWords, wordX + 1); 
			indices.Q[1] = wrapWordIndex(i32NumYWords, wordY);
			indices.R[0] = wrapWordIndex(i32NumXWords, wordX); 
			indices.R[1] = wrapWordIndex(i32NumYWords, wordY + 1);
			indices.S[0] = wrapWordIndex(i32NumXWords, wordX + 1);
			indices.S[1] = wrapWordIndex(i32NumYWords, wordY + 1);

			//Work out the offsets into the twiddle structs, multiply by two as there are two members per word.
			PVRTuint32 WordOffsets[4] =
			{
				TwiddleUV(i32NumXWords,i32NumYWords,indices.P[0], indices.P[1])*2,
				TwiddleUV(i32NumXWords,i32NumYWords,indices.Q[0], indices.Q[1])*2,
				TwiddleUV(i32NumXWords,i32NumYWords,indices.R[0], indices.R[1])*2,
				TwiddleUV(i32NumXWords,i32NumYWords,indices.S[0], indices.S[1])*2,
			};

			//Access individual elements to fill out PVRTCWord
			PVRTCWord P,Q,R,S;
			P.u32ColourData = pWordMembers[WordOffsets[0]+1];
			P.u32ModulationData = pWordMembers[WordOffsets[0]];
			Q.u32ColourData = pWordMembers[WordOffsets[1]+1];
			Q.u32ModulationData = pWordMembers[WordOffsets[1]];
			R.u32ColourData = pWordMembers[WordOffsets[2]+1];
			R.u32ModulationData = pWordMembers[WordOffsets[2]];
			S.u32ColourData = pWordMembers[WordOffsets[3]+1];
			S.u32ModulationData = pWordMembers[WordOffsets[3]];
							
			// assemble 4 words into struct to get decompressed pixels from
			pvrtcGetDecompressedPixels(P,Q,R,S,pPixels,ui8Bpp);
			mapDecompressedData(pOutData, ui32Width, pPixels, indices, ui8Bpp);
			
		} // for each word
	} // for each row of words

	free(pPixels);
	//Return the data size
	return ui32Width * ui32Height / (PVRTuint32)(ui32WordWidth/2);
}

static int decompressPVRTC(const void *pCompressedData, //1595
				const int Do2bitMode,
				const int XDim,
				const int YDim,
				unsigned char* pResultImage)
{
	//Cast the output buffer to a Pixel32 pointer.
	Pixel32* pDecompressedData = (Pixel32*)pResultImage;

	//Check the X and Y values are at least the minimum size.
	int XTrueDim = PVRT_MAX(XDim,((Do2bitMode==1)?16:8));
	int YTrueDim = PVRT_MAX(YDim,8);

	//If the dimensions aren't correct, we need to create a new buffer instead of just using the provided one, as the buffer will overrun otherwise.
	if(XTrueDim!=XDim || YTrueDim!=YDim)
	{
		pDecompressedData=(Pixel32*)malloc(XTrueDim*YTrueDim*sizeof(Pixel32));
	}
		
	//Decompress the surface.
	int retval = pvrtcDecompress((PVRTuint8*)pCompressedData,pDecompressedData,XTrueDim,YTrueDim,(Do2bitMode==1?2:4));

	//If the dimensions were too small, then copy the new buffer back into the output buffer.
	if(XTrueDim!=XDim || YTrueDim!=YDim)
	{
		//Loop through all the required pixels.
		for (int x=0; x<XDim; ++x)
		{
			for (int y=0; y<YDim; ++y)
			{
				((Pixel32*)pResultImage)[x+y*XDim]=pDecompressedData[x+y*XTrueDim];
			}
		}

		//Free the temporary buffer.
		free(pDecompressedData);
	}
	return retval;
}

#define _CLAMP_(X,Xmin,Xmax) (  (X)<(Xmax) ?  (  (X)<(Xmin)?(Xmin):(X)  )  : (Xmax)    )

unsigned int ETC_FLIP = 0x01000000; //1625
unsigned int ETC_DIFF = 0x02000000; //1626
const int mod[8][4] = { { 2, 8, -2, -8 }, //1627
{ 5, 17, -5, -17 },
{ 9, 29, -9, -29 },
{ 13, 42, -13, -42 },
{ 18, 60, -18, -60 },
{ 24, 80, -24, -80 },
{ 33, 106, -33, -106 },
{ 47, 183, -47, -183 } };

static unsigned int modifyPixel(int red, int green, int blue, int x, int y, unsigned int modBlock, int modTable) //1636
{
	int index = x*4+y, pixelMod;
	unsigned int mostSig = modBlock<<1;

	if (index<8)
		pixelMod = mod[modTable][((modBlock>>(index+24))&0x1)+((mostSig>>(index+8))&0x2)];
	else
		pixelMod = mod[modTable][((modBlock>>(index+8))&0x1)+((mostSig>>(index-8))&0x2)];

	red = _CLAMP_(red+pixelMod,0,255);
	green = _CLAMP_(green+pixelMod,0,255);
	blue = _CLAMP_(blue+pixelMod,0,255);

	return ((red<<16) + (green<<8) + blue)|0xff000000;
}

static int ETCTextureDecompress(const void * const pSrcData, const int &x, const int &y, const void *pDestData,const int &/*nMode*/) //1653
{
	unsigned int blockTop, blockBot, *input = (unsigned int*)pSrcData, *output;
	unsigned char red1, green1, blue1, red2, green2, blue2;
	bool bFlip, bDiff;
	int modtable1,modtable2;

	for(int i=0;i<y;i+=4)
	{
		for(int m=0;m<x;m+=4)
		{
				blockTop = *(input++);
				blockBot = *(input++);

			output = (unsigned int*)pDestData + i*x +m;

			// check flipbit
			bFlip = (blockTop & ETC_FLIP) != 0;
			bDiff = (blockTop & ETC_DIFF) != 0;

			if(bDiff)
			{	// differential mode 5 colour bits + 3 difference bits
				// get base colour for subblock 1
				blue1 = (unsigned char)((blockTop&0xf80000)>>16);
				green1 = (unsigned char)((blockTop&0xf800)>>8);
				red1 = (unsigned char)(blockTop&0xf8);

				// get differential colour for subblock 2
				signed char blues = (signed char)(blue1>>3) + ((signed char) ((blockTop & 0x70000) >> 11)>>5);
				signed char greens = (signed char)(green1>>3) + ((signed char)((blockTop & 0x700) >>3)>>5);
				signed char reds = (signed char)(red1>>3) + ((signed char)((blockTop & 0x7)<<5)>>5);

				blue2 = (unsigned char)blues;
				green2 = (unsigned char)greens;
				red2 = (unsigned char)reds;

				red1 = red1 +(red1>>5);	// copy bits to lower sig
				green1 = green1 + (green1>>5);	// copy bits to lower sig
				blue1 = blue1 + (blue1>>5);	// copy bits to lower sig

				red2 = (red2<<3) +(red2>>2);	// copy bits to lower sig
				green2 = (green2<<3) + (green2>>2);	// copy bits to lower sig
				blue2 = (blue2<<3) + (blue2>>2);	// copy bits to lower sig
			}
			else
			{	// individual mode 4 + 4 colour bits
				// get base colour for subblock 1
				blue1 = (unsigned char)((blockTop&0xf00000)>>16);
				blue1 = blue1 +(blue1>>4);	// copy bits to lower sig
				green1 = (unsigned char)((blockTop&0xf000)>>8);
				green1 = green1 + (green1>>4);	// copy bits to lower sig
				red1 = (unsigned char)(blockTop&0xf0);
				red1 = red1 + (red1>>4);	// copy bits to lower sig

				// get base colour for subblock 2
				blue2 = (unsigned char)((blockTop&0xf0000)>>12);
				blue2 = blue2 +(blue2>>4);	// copy bits to lower sig
				green2 = (unsigned char)((blockTop&0xf00)>>4);
				green2 = green2 + (green2>>4);	// copy bits to lower sig
				red2 = (unsigned char)((blockTop&0xf)<<4);
				red2 = red2 + (red2>>4);	// copy bits to lower sig
			}
			// get the modtables for each subblock
			modtable1 = (blockTop>>29)&0x7;
			modtable2 = (blockTop>>26)&0x7;

			if(!bFlip)
			{	// 2 2x4 blocks side by side

				for(int j=0;j<4;j++)	// vertical
				{
					for(int k=0;k<2;k++)	// horizontal
					{
						*(output+j*x+k) = modifyPixel(red1,green1,blue1,k,j,blockBot,modtable1);
						*(output+j*x+k+2) = modifyPixel(red2,green2,blue2,k+2,j,blockBot,modtable2);
					}
				}

			}
			else
			{	// 2 4x2 blocks on top of each other
				for(int j=0;j<2;j++)
				{
					for(int k=0;k<4;k++)
					{
						*(output+j*x+k) = modifyPixel(red1,green1,blue1,k,j,blockBot,modtable1);
						*(output+(j+2)*x+k) = modifyPixel(red2,green2,blue2,k,j+2,blockBot,modtable2);
					}
				}
			}
		}
	}

	return x*y/2;
}

int decompressETC(const void * const pSrcData, //1732
						 const unsigned int &x,
						 const unsigned int &y,
						 void *pDestData,
						 const int &nMode)
{
	int i32read;

	if(x<ETC_MIN_TEXWIDTH || y<ETC_MIN_TEXHEIGHT)
	{	// decompress into a buffer big enough to take the minimum size
		char* pTempBuffer =	(char*)malloc(PVRT_MAX(x,ETC_MIN_TEXWIDTH)*PVRT_MAX(y,ETC_MIN_TEXHEIGHT)*4);
		i32read = ETCTextureDecompress(pSrcData,PVRT_MAX(x,ETC_MIN_TEXWIDTH),PVRT_MAX(y,ETC_MIN_TEXHEIGHT),pTempBuffer,nMode);

		for(unsigned int i=0;i<y;i++)
		{	// copy from larger temp buffer to output data
			memcpy((char*)(pDestData)+i*x*4,pTempBuffer+PVRT_MAX(x,ETC_MIN_TEXWIDTH)*4*i,x*4);
		}

		if(pTempBuffer) free(pTempBuffer);
	}
	else	// decompress larger MIP levels straight into the output data
		i32read = ETCTextureDecompress(pSrcData,x,y,pDestData,nMode);

	// swap r and b channels
	unsigned char* pSwap = (unsigned char*)pDestData, swap;

	for(unsigned int i=0;i<y;i++)
		for(unsigned int j=0;j<x;j++)
		{
			swap = pSwap[0];
			pSwap[0] = pSwap[2];
			pSwap[2] = swap;
			pSwap+=4;
		}

	return i32read;
}


} // img

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
