#include <framework/FileLogger.h>
#include <lang/Format.h>
#include <time.h>

using namespace lang;

namespace framework
{

FileLogger::FileLogger()
{
	addListener(this);
}

FileLogger::~FileLogger()
{
	removeListener(this);
}

void FileLogger::onLogEvent(const log::Event& e)
{
	time_t timer = e.timestamp / 1000;
	tm* lp = localtime(&timer);
	char tbuf[128];
	strftime(tbuf, sizeof(tbuf), "%Y/%m/%d %H:%M:%S", lp);
	if (e.filename)
	{
		if (!e.tag.empty())
			m_output->write(Format("{0}.{1,0000} [{2}] ({3}): {4}\n", tbuf, (_mm_unpacklo_epi32(_mm_cvtsi32_si128(e.timestamp % 1000), _mm_cvtsi32_si128((e.timestamp % 1000) >> 32)).m128i_i64[0]), log::priorityToString(e.priority), e.tag, e.message).format().c_str(), e.message.size());
		else
			m_output->write(Format("{0}.{1,0000} [{2}]: {3}\n", tbuf, (_mm_unpacklo_epi32(_mm_cvtsi32_si128(e.timestamp % 1000), _mm_cvtsi32_si128((e.timestamp % 1000) >> 32)).m128i_i64[0]), log::priorityToString(e.priority), e.message).format().c_str(), e.message.size());
	}

	else
		m_output->write(e.message.c_str(), e.message.size());
}

}