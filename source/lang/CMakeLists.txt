project(lang)

file(GLOB LANG_SRC "*.cpp")

#if(APPLE) #Off for now
#    file(GLOB LANG_IOS_SRC "ios+osx/*.mm")
#    list(APPEND LANG_SRC ${LANG_IOS_SRC})
#else()
#    list(APPEND LANG_SRC "dummy/AutoReleasePool_dummy.cpp")
#endif()

add_compile_definitions(_LIB)
add_library(lang STATIC ${LANG_SRC})