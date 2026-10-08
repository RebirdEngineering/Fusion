#ifndef _IO_DATAINPUTSTREAM_H
#define _IO_DATAINPUTSTREAM_H

#include <io/DataInput.h>
#include <io/InputStream.h>

namespace io
{ 

/**
 * Class for reading primitive types from the input stream in portable way.
 * 
 * @ingroup io
 */
class DataInputStream : //16
	public InputStream,
	public DataInput
{
public:
	///
	explicit DataInputStream( InputStream& source); //22
	explicit DataInputStream( P(InputStream) in ); //23

	///
	~DataInputStream(); //28

	/**
	 * Tries to skip over n bytes from the stream.
	 *
	 * @return Number of bytes actually skipped.
	 * @exception IOException
	 */
	int skip( int n ); //36
	
	/**
	 * 
	 *
	 * @return 
	 * @exception IOException
	 */
	bool seek( int n, SeekMode origin); //43

	/**
	 * Tries to read specified number of bytes from the source stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 *
	 * @return Number of bytes actually read.
	 * @exception IOException
	 */
	int read( void* data, int size ); //52

	/**
	 * Reads specified number of bytes from the stream.
	 *
	 * @exception IOException
	 */
	void readFully( void* data, int size ); //59

	/**
	 * Reads boolean from the stream.
	 *
	 * @exception IOException
	 */
	bool readBoolean(); //66

	/**
	 * Reads 8-bit signed integer from the stream.
	 *
	 * @exception IOException
	 */
	uint8_t readByte(); //73

	/**
	 * Reads character from the stream.
	 *
	 * @exception IOException
	 */
	char 	readChar(); //80

	/**
	 * Reads character sequence from the stream.
	 *
	 * @param n Number of characters to read.
	 * @exception IOException
	 */
	std::string readChars( int n ); //88

	/**
	 * Reads double value from the stream.
	 *
	 * @exception IOException
	 */
	double readDouble(); //95

	/**
	 * Reads float from the stream.
	 *
	 * @exception IOException
	 */
	float readFloat(); //102

	/**
	 * Reads 32-bit signed integer from the stream.
	 *
	 * @exception IOException
	 */
	int readInt(); //109

	/**
	 * Reads 16-bit signed integer from the stream.
	 *
	 * @exception IOException
	 */
	int readShort(); //116

	/**
	 * Reads string encoded in UTF-8 from the stream.
	 *
	 * @exception EOFException
	 * @exception IOException
	 */
	std::string readUTF(); //124

	/**
	 * Reads string encoded in UTF-8 from the stream.
	 *
	 * @param buf [out] Receives 0-terminated UTF-8 string.
	 * @param bufsize Maximum size for the string. IOException is thrown if buffer too small.
	 * @exception EOFException
	 * @exception IOException
	 */
	void readUTF( char* buf, int bufsize ); //134

	/**
	 * Reads string encoded in UTF-8 from the stream. Buffer size is adjusted accordingly.
	 *
	 * @param buf [out] Receives 0-terminated UTF-8 string.
	 * @exception EOFException
	 * @exception IOException
	 */
	void readUTF( std::vector<char>& buf ); //143

private:
	void	readBE( void* data, int size ); //146

	DataInputStream(); //148
	DataInputStream( const DataInputStream& ); //149
	DataInputStream& operator=( const DataInputStream& ); //150
};


} // io


#endif // _IO_DATAINPUTSTREAM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
