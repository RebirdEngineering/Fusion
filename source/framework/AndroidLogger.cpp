#include <framework/AndroidLogger.h>

#include <android/log.h>

using namespace lang;

static int androidLogPrio[5] = { ANDROID_LOG_ERROR, ANDROID_LOG_WARN, ANDROID_LOG_INFO, ANDROID_LOG_DEBUG, ANDROID_LOG_VERBOSE };

namespace framework
{

AndroidLogger::AndroidLogger()
{
	addListener(this);
}

AndroidLogger::~AndroidLogger()
{
	removeListener(this);
}

void AndroidLogger::onLogEvent(const log::Event& e)
{
	__android_log_print(e.priority - 1 <= ANDROID_LOG_INFO ? androidLogPrio[e.priority - 1] : ANDROID_LOG_INFO, e.tag, "%s", e.message);
}

}