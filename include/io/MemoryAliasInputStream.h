#ifndef _IO_MEMORYALIASINPUTSTREAM_H
#define _IO_MEMORYALIASINPUTSTREAM_H

#include <io/InputStream.h>

BEGIN_NAMESPACE(io)

/**
 *
 *
 * @ingroup io
 */
class MemoryAliasInputStream :
	public InputStream
{
public:
	/**
	 *
	 */
	MemoryAliasInputStream(const void* data, int size, const std::string& name);

	///
	~MemoryAliasInputStream();

	/**
	 * Resets with new input buffer.
	 * Note that the contents of the buffer is duplicated so the buffer
	 * can be freed immediately after MemoryAliasInputStream constructor returns.
	 */
	void					reset(const void* data, int size);

	/**
	 * Tries to read specified number of bytes from the stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 * @return Number of bytes actually read.
	 * @exception IOException
	 */
	int				read(void* data, int size);

	/**
	 * Tries to skip over n bytes from the stream.
	 * @return Number of bytes actually skipped.
	 * @exception IOException
	 */
	int				skip(int n);

	/**
	 * 
	 * @return 
	 * @exception IOException
	 */
	bool				seek(int offset, SeekMode origin);

	const void* data() const;

	/**
	 * Returns the number of bytes that can be read from the stream without blocking.
	 */
	int available() const;

	std::string toString() const;

private:
	const void* m_data;
	size_t m_size;
	std::string m_name;
	int m_index;

	const void* byteIndex(size_t index) const { //99 | Only exists in ABS410 DWARF, correct
		const char* data = "";
		memcpy(&data, &m_data + m_index, index);
		return data;
	}

	MemoryAliasInputStream(const MemoryAliasInputStream&);
	MemoryAliasInputStream& operator=(const MemoryAliasInputStream&);
};


END_NAMESPACE() // io


#endif // _IO_MEMORYALIASINPUTSTREAM_H
