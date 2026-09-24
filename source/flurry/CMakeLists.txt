project(flurry)

file(GLOB FLURRY_SRC "*.cpp" "${FLURRY_IMPL}/*.cpp")

#if(IOS) #Not yet decompiled.
#    file(GLOB FLURRY_IOS_SRC "ios/*.mm")
#    append(FLURRY_SRC ${FLURRY_IOS_SRC})
#endif()

#if(WINDOWS_PHONE) #Not yet decompiled.
#    file(GLOB FLURRY_WP7_SRC "wp7/*.cpp")
#    append(FLURRY_SRC ${FLURRY_WP7_SRC})
#endif()

add_compile_definitions(_LIB)
add_library(flurry STATIC ${FLURRY_SRC})