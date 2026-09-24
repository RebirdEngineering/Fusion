project(pf) #Platform functions.

file(GLOB PF_SRC "*.cpp" "detail/*.cpp")

#if(APPLE)  #Not yet decompiled.
    #file(GLOB PF_APPLE_SRC "ios+osx/*.cpp" "ios+osx/*.mm" "ios+osx/*.m")
    #list(APPEND PF_SRC ${PF_APPLE_SRC})
#endif()

#if(IOS) #Not yet decompiled.
#    file(GLOB PF_IOS_SRC "iOS/*.cpp" "iOS/*.mm" "iOS/*.m")
#    list(APPEND PF_SRC ${PF_IOS_SRC})
#endif()

#if(OSX) #Not yet decompiled.
    #file(GLOB PF_OSX_SRC "osx/*.cpp" "osx/*.mm" "osx/*.m")
    #list(APPEND PF_SRC ${PF_OSX_SRC})
#endif()

#if(ANDROID) #Not yet decompiled.
    #file(GLOB PF_ANDROID_SRC "android/*.cpp")
    #list(APPEND PF_SRC ${PF_ANDROID_SRC})
#endif()

#if(WINDOWS_STORE) #Not yet decompiled.
#    file(GLOB PF_WP8_SRC "wp8/*.cpp")
#    list(APPEND PF_SRC ${PF_WP8_SRC})
#endif()

if(WIN32)
    file(GLOB PF_DUMMY_SRC "dummy/*.cpp")
    list(APPEND PF_SRC ${PF_DUMMY_SRC})
endif()

add_compile_definitions(_LIB)
add_library(pf STATIC ${PF_SRC})