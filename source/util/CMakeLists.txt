project(util)

file(GLOB UTIL_SRC "*.cpp")

#if(IOS) #Not yet decompiled.
#    file(GLOB UTIL_IOS_SRC "ios/*.cpp" "ios/*.mm" "ios/*.m")
#    list(APPEND UTIL_SRC ${UTIL_IOS_SRC})
#endif()

add_compile_definitions(_LIB)
add_library(util STATIC ${UTIL_SRC})