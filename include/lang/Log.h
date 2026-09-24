#ifndef _LANG_LOG_H
#define _LANG_LOG_H

#include <lang/LogListener.h>

BEGIN_NAMESPACE(lang)
BEGIN_NAMESPACE(analytics)

void log(const std::string& eventname, const std::map<std::string, std::string>& params);
void addListener(Listener* listener);
void removeListener(Listener* listener);

}

BEGIN_NAMESPACE(log)

#define LANG_LOG_PRIORITY_AUDIT   0
#define LANG_LOG_PRIORITY_ERROR   1
#define LANG_LOG_PRIORITY_WARN    2
#define LANG_LOG_PRIORITY_INFO    3
#define LANG_LOG_PRIORITY_DEBUG   4
#define LANG_LOG_PRIORITY_VERBOSE 5

//LANG_LOG("Lua", 2, "%s");

std::string stringify(const char* fmt, va_list args);
void addListener(Listener* listener);
void removeListener(Listener* listener);
void log(const std::string& tag, const char* file, const char* function, int line, int priority, const char* message, ...); //Unofficial?
const char* priorityToString(int prio); //Unofficial?

//const std::string& tag, const char* file, const char* function, int line, int priority, const char* message, ...



}
}

//#define LANG_LOG(tag, priority, message) ::lang::log::log(tag, __FILE__, __func__, __LINE__, priority, message)


//#define LANG_LOG(tag, priority, message) lang::log::log(tag ? tag : "", __FILE__, __func__, __LINE__, priority, message)

#define LANG_LOG(tag, priority, message, ...) lang::log::log(tag, __FILE__, __func__, __LINE__, priority, message, ##__VA_ARGS__) //CUSTOM

//Specific logs
// 
// todo debug only?
// 
//#define LANG_LOG_AUDIT(tag, message, ...) lang::log::log(tag, LANG_LOG_PRIORITY_AUDIT, __FILE__, __func__, __LINE__, priority, message, ##__VA_ARGS__) //CUSTOM
//#define LANG_LOG_ERROR(tag, message, ...) lang::log::log(tag, LANG_LOG_PRIORITY_ERROR, __FILE__, __func__, __LINE__, priority, message, ##__VA_ARGS__) //CUSTOM
//#define LANG_LOG_WARN(tag, message, ...) lang::log::log(tag, LANG_LOG_PRIORITY_WARN, __FILE__, __func__, __LINE__, priority, message, ##__VA_ARGS__) //CUSTOM
//#define LANG_LOG_INFO(tag, message, ...) lang::log::log(tag, LANG_LOG_PRIORITY_INFO, __FILE__, __func__, __LINE__, priority, message, ##__VA_ARGS__) //CUSTOM
//#define LANG_LOG_DEBUG(tag, message, ...) lang::log::log(tag, LANG_LOG_PRIORITY_DEBUG, __FILE__, __func__, __LINE__, priority, message, ##__VA_ARGS__) //CUSTOM
//#define LANG_LOG_VERBOSE(tag, message, ...) lang::log::log(tag, LANG_LOG_PRIORITY_VERBOSE, __FILE__, __func__, __LINE__, priority, message, ##__VA_ARGS__) //CUSTOM


//LOG_DEBUG //?

#ifdef _DEBUG //Log only on Debug | ABS 4.1.0: 1 and 2 only
#define LANG_LOG_DEBUG(tag, priority, message, ...) lang::log::log(tag, __FILE__, __func__, __LINE__, priority, message, ##__VA_ARGS__) //CUSTOM
#else
#define LANG_LOG_DEBUG(tag, priority, message, ...) //CUSTOM
#endif

//#define LANG_LOG(tag, priority, message, ...) lang::log::log(tag, __FILE__, __func__, __LINE__, priority, message)

//#define LANG_LOG(tag, priority, message, ...) lang::log::log(tag, __FILE__, __func__, __LINE__, priority, message, ##__VA_ARGS__)

//#define LANG_LOG(tag, priority, message) lang::log::log(tag, __FILE__, __func__, __LINE__, priority, message)

#endif // !_LANG_LOG_H