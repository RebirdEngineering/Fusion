project(io)

file(GLOB IO_SRC "*.cpp" "std/*.cpp" "detail/*.cpp" ${FUSION_DIR}/external/zlib/*.c) #Std is used on Android OSX and iOS, according to OSX zlib is embedded in the lib

if(WIN32 OR WINDOWS_PHONE OR WINDOWS_STORE)
    file(GLOB IO_WIN32_SRC "win32/*.cpp")
    list(APPEND IO_SRC ${IO_WIN32_SRC})
endif()

if(ANDROID) #On iOS only used in Seasons 4.1.0?
    file(GLOB IO_ANDROID_SRC "android/*.cpp")
    list(APPEND IO_SRC ${IO_ANDROID_SRC})
endif()

if(ANDROID OR APPLE) #On iOS only used in Seasons 4.1.0?
    file(GLOB IO_POSIX_SRC "posix/*.cpp")
    list(APPEND IO_SRC ${IO_POSIX_SRC})
endif()

if (LINUX) #or apple
	file(GLOB IO_LINUX_SRC "linux/*.cpp")
	file(APPEND IO_SRC {IO_LINUX_SRC})
endif()

add_compile_definitions(_LIB)
add_library(io STATIC ${IO_SRC})
target_include_directories(io PRIVATE ${FUSION_DIR}/external/zlib) #According to OSX zlib is embedded in the lib