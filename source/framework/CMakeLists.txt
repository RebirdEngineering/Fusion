project(framework)

file(GLOB FRAMEWORK_SRC "*.cpp") #TODO make this so win32 uses VisualStudioLogger

if(WIN32)
    list(APPEND FRAMEWORK_SRC "win32/WinMain.cpp") #WIP
endif()

#if(ANDROID) #Not yet decompiled.
#    file(GLOB FRAMEWORK_ANDROID_SRC "android/*.cpp")
#    list(APPEND FRAMEWORK_SRC ${FRAMEWORK_ANDROID_SRC})
#endif()

#if(IOS) #Not yet decompiled.
#    file(GLOB FRAMEWORK_IOS_SRC "iOS/*.cpp" "iOS/*.m" "iOS/*.mm")
#    list(APPEND FRAMEWORK_SRC ${FRAMEWORK_IOS_SRC})
#endif()

#if(OSX) #Not yet decompiled.
#    file(GLOB FRAMEWORK_OSX_SRC "osx/*.cpp" "osx/*.m" "iOS/*.mm")
#    list(APPEND FRAMEWORK_SRC ${FRAMEWORK_OSX_SRC})
#endif()

add_compile_definitions(_LIB)
add_library(framework STATIC ${FRAMEWORK_SRC})