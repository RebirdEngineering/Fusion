#include <img/ImageReader.h>
#include <lang/Throwable.h>
#include <lang/Exception.h>
#include <lang/Math.h>

USING_NAMESPACE(lang)

BEGIN_NAMESPACE(img)

//PVR SDK
//https://powervr-graphics.github.io/WebGL_SDK/WebGL_SDK/Documentation/Specifications/PVR%20File%20Format.Specification.Legacy.pdf
//https://powervr-graphics.github.io/WebGL_SDK/WebGL_SDK/Documentation/Specifications/PVR%20File%20Format.Specification.pdf
//https://imagination-technologies-cloudfront-assets.s3.amazonaws.com/website-files/documents/PVR+File+Format.Specification.pdf

struct PVRHeader2 //15
{
	uint32_t dwHeaderSize;
	uint32_t dwHeight;
	uint32_t dwWidth;
	uint32_t dwMipMapCount;
	uint32_t dwpfFlags;
	uint32_t dwTextureDataSize;
	uint32_t dwBitCount;
	uint32_t dwRBitMask;
	uint32_t dwGBitMask;
	uint32_t dwBBitMask;
	uint32_t dwAlphaBitMask;
	uint32_t dwPVR;
	uint32_t dwNumSurfs;
};

struct PVRHeader3 //35
{
	uint32_t u32Version;
	uint32_t u32Flags;
	uint64_t u64PixelFormat;
	uint32_t u32ColourSpace;
	uint32_t u32ChannelType;
	uint32_t u32Height;
	uint32_t u32Width;
	uint32_t u32Depth;
	uint32_t u32NumSurfaces;
	uint32_t u32NumFaces;
	uint32_t u32MIPMapCount;
	uint32_t u32MetaDataSize;
};

void ImageReader::readHeader_pvr() //342 | TODO
{
	/*uint32_t id; //349
	readFully(m_in, &id, sizeof(id));

	if (id == 0x3525650) //PVRV3
	{
		PVRHeader3 header; //355

		//readFully(m_in, &header, sizeof(header)); //Ok this is just stupid why do you read everything one at a time? You could just do this!

		//readFully(m_in, &header.u32Version, sizeof(header.u32Version)); //Assuming this is ignored since the header contains all that
		readFully(m_in, &header.u32Flags, sizeof(header.u32Flags));
		//PixFmt
		uint32_t hipart; //376 | Format
		uint32_t lopart; //377 | Channels

		//readFully(m_in, &hipart, sizeof(hipart));
		//readFully(m_in, &lopart, sizeof(lopart));
		readFully(m_in, (&hipart + lopart), sizeof(header.u64PixelFormat));
		readFully(m_in, &header.u32ColourSpace, sizeof(header.u32ColourSpace));
		readFully(m_in, &header.u32ChannelType, sizeof(header.u32ChannelType));
		readFully(m_in, &header.u32Height, sizeof(header.u32Height));
		readFully(m_in, &header.u32Width, sizeof(header.u32Width));
		readFully(m_in, &header.u32Depth, sizeof(header.u32Depth));
		readFully(m_in, &header.u32NumSurfaces, sizeof(header.u32NumSurfaces));
		readFully(m_in, &header.u32NumFaces, sizeof(header.u32NumFaces));
		readFully(m_in, &header.u32MIPMapCount, sizeof(header.u32MIPMapCount));
		readFully(m_in, &header.u32MetaDataSize, sizeof(header.u32MetaDataSize));

		m_width = header.u32Width;
		m_height = header.u32Height;
		m_mipLevels = header.u32MIPMapCount;
		m_palfmt = SurfaceFormat::SURFACE_UNKNOWN; //?
		m_cubeMap = header.u32Flags == 6;
		m_surfaces = m_mipLevels * header.u32NumSurfaces;

		if (lopart == 0x8080808)
		{
			switch (hipart)
			{
			case 'argb': m_fmt = SurfaceFormat::SURFACE_A8R8G8B8; break;
			case 'abgr': m_fmt = SurfaceFormat::SURFACE_A8B8G8R8; break;
			default: throwError(Exception(Format("Unsupported surface format {0,x}{1,x} while reading PVR texture: {1}", hipart, lopart, m_in->toString()))); //?
			}
		}

		else if (lopart == 0x4040404)
		{
			hipart == 'abgr' ? m_fmt = SurfaceFormat::SURFACE_A4B4G4R4 : throwError(Exception(Format("Unsupported surface format {0,x}{1,x} while reading PVR texture: {1}", hipart, lopart, m_in->toString())));
		}

		else if (lopart >= 0x1050504)
		{
			hipart == 'abgr' ? m_fmt = SurfaceFormat::SURFACE_R5G5B5A1 : throwError(Exception(Format("Unsupported surface format {0,x}{1,x} while reading PVR texture: {1}", hipart, lopart, m_in->toString())));
		}

		else if (lopart >= 0x80808)
		{
			hipart == 'bgr' ? m_fmt = SurfaceFormat::SURFACE_B8G8R8 : throwError(Exception(Format("Unsupported surface format {0,x}{1,x} while reading PVR texture: {1}", hipart, lopart, m_in->toString())));
		}

		else if (lopart >= 0x50604)
		{
			hipart == 'bgr' ? m_fmt = SurfaceFormat::SURFACE_R5G6B5 : throwError(Exception(Format("Unsupported surface format {0,x}{1,x} while reading PVR texture: {1}", hipart, lopart, m_in->toString()))); //?
		}

		else
		{
			switch (hipart)
			{
			case 0:
				switch (lopart)
				{
				case 0: m_fmt = SurfaceFormat::SURFACE_PVRTC_RGB_2BPP; break;
				case 1: m_fmt = SurfaceFormat::SURFACE_PVRTC_RGBA_2BPP; break;
				case 2: m_fmt = SurfaceFormat::SURFACE_PVRTC_RGB_4BPP; break;
				case 3: m_fmt = SurfaceFormat::SURFACE_PVRTC_RGBA_4BPP; break;
				case 6: m_fmt = SurfaceFormat::SURFACE_ETC1_RGB_4BPP; break;
				case 7: m_fmt = SurfaceFormat::SURFACE_DXT1; break;
				case 9: m_fmt = SurfaceFormat::SURFACE_DXT3; break;
				case 11: m_fmt = SurfaceFormat::SURFACE_DXT5; break;
				default: throwError(Exception(Format("Unsupported surface format {0} while reading PVR texture: {1}", lopart, m_in->toString()))); //?
				}
			case 8:
				switch (lopart)
				{
				case 'a': m_fmt = SurfaceFormat::SURFACE_A8; break;
				case 'l': m_fmt = SurfaceFormat::SURFACE_L8; break;
				default: throwError(Exception(Format("Unsupported surface format {0,x}{1,x} while reading PVR texture: {1}", hipart, lopart, m_in->toString()))); //?
				}
				m_bitsPerPixel = m_fmt.bitsPerPixel();
				m_in->skip(header.u32MetaDataSize);
			case 2056:
				hipart == 'al' ? m_fmt = SurfaceFormat::SURFACE_A8L8 : throwError(Exception(Format("Unsupported surface format {0,x}{1,x} while reading PVR texture: {1}", hipart, lopart, m_in->toString()))); //?
		}

		//m_fmt = SurfaceFormat::
		
		uint8_t depths[];
		uint8_t channels[];
		uint32_t mipIndex;
		uint32_t surfaceIndex;

		uint32_t faceIndex;

		uint32_t sliceIndex;

		Surface& s = m_surfaceBuffer[sliceIndex];

		//m_surfaceBuffer.resize()

		//m_surfaceBuffer.push_back(s);

		//Math::max()
		//Math::max()

		//m_scanlinebuffer.resize();

		//uint32_t faces[4];
		uint32_t size;
        //?
        assert(!m_cubeMap || faces == 6); //[NOTE] DF 326 / AA 327
	}
	else //PVR2
	{
		PVRHeader2 header;
		int faces;


		m_width = header.dwWidth;
		m_height = header.dwWidth;
		m_mipLevels = header.dwMipMapCount + 1;
		int size;

		m_cubeMap = (header.dwpfFlags & 0x1000) != 0;
		m_surfaces = m_mipLevels * header.dwNumSurfs; //?
		m_bitsPerPixel = header.dwBitCount;

		//uint8_t hipart[4];
		//readFully(m_in, &header, sizeof(header));

		int i;
		int k;
		Surface& s = m_surfaceBuffer[i];
		m_palfmt = s;

		switch (? )
		{
		case 0: SurfaceFormat(SURFACE_PVRTC_RGB_2BPP); break;
		case 1: SurfaceFormat(SURFACE_PVRTC_RGBA_2BPP); break;
		case 2: SurfaceFormat(SURFACE_PVRTC_RGB_4BPP); break;
		case 3: SurfaceFormat(SURFACE_PVRTC_RGBA_4BPP); break;
		case 6: SurfaceFormat(SURFACE_ETC1_RGB_4BPP); break;
		case 7: SurfaceFormat(SURFACE_DXT1); break;
		case 9: SurfaceFormat(SURFACE_DXT3); break;
		case 11: SurfaceFormat(SURFACE_DXT5); break;
		default: throwError(Exception(Format("Unsupported surface format {0} while reading PVR texture: {1}")));
		}

		//Math::max()
		//Math::max()

		//m_scanlinebuffer.resize()
	}
	//todo*/
	assert("void img::ImageReader::readHeader_pvr() was not yet decompiled.");
}

}