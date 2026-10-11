#ifndef _IO_MEMORYALIASINPUTSTREAM_H
#define _IO_MEMORYALIASINPUTSTREAM_H

#include <io/InputStream.h>

namespace io
{

/**
 *
 * 
 *
 * @ingroup io
 */
class MemoryAliasInputStream : //15
	public InputStream
{
public:
	/**
	 *
	 */
	MemoryAliasInputStream(const void* data, int size, const std::string& name); //48

	///
	~MemoryAliasInputStream(); //48

	/**
	 * Resets with new input buffer.
	 * Note that the contents of the buffer is duplicated so the buffer
	 * can be freed immediately after ByteArrayInputStream constructor returns.
	 */
	void					reset(const void* data, int size); //57

	/**
	 * Tries to read specified number of bytes from the stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 * @return Number of bytes actually read.
	 * @exception IOException
	 */
	int				read(void* data, int size); //64

	/**
	 * Tries to skip over n bytes from the stream.
	 * @return Number of bytes actually skipped.
	 * @exception IOException
	 */
	int				skip(int n); //71

	/**
	 * 
	 * @return 
	 * @exception IOException
	 */
	bool				seek(int offset, SeekMode origin); //78

	const void* data() const; //83

	/**
	 * Returns the number of bytes that can be read from the stream without blocking.
	 */
	int available() const; //88

	std::string toString() const; //91

private:
	const void* m_data; //94
	size_t m_size; //95
	std::string m_name; //96
	int m_index; //97

	const void* byteIndex(size_t index) const { //99 | Symbol only exists in ABS410 DWARF, correct
		const char* data = ""; //100
		memcpy(&data, &m_data + m_index, index);
		return data;
	}

	MemoryAliasInputStream(const MemoryAliasInputStream&); //104
	MemoryAliasInputStream& operator=(const MemoryAliasInputStream&); //105
};


} // io


#endif // _IO_MEMORYALIASINPUTSTREAM_H
