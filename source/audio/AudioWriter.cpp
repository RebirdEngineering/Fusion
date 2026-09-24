#include <audio/AudioWriter.h>
#include <io/FileFormat.h>
#include <io/FileOutputStream.h>
#include <lang/Exception.h>
#include <io/IOException.h>

using namespace io;

namespace audio
{

static void writeLE4(FileOutputStream& stream, unsigned int size)
{
	stream.write(?, 4);
}

bool AudioWriter::writeWav(const std::string& filename, const AudioConfiguration& conf, const void* data, int size)
{
	FileOutputStream out(filename);
	//out.write("RIFF", 4);
	//writeLE4(out, size + 36);

	//out.write(1, 2);
	//out.write(&conf.m_channels, 2);

	//writeLE4(out, conf.m_samplesPerSecond);

	//out.write(&conf.m_bitsPerSample, 2);
	
	//out.write("data", 4);
	//writeLE4(out, size);
	//out.write(data, size);
}

bool AudioWriter::write(const std::string& filename, AudioConfiguration const&, void const*, FileFormat ff)
{	
	if (ff.guessFileFormat() != FILEFORMAT_WAV )
		throwError( IOException( Format("Trying to write unsupported audio fileformat") ) );
	return writeWav(filename, data, size);
}

}