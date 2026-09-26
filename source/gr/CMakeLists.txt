project(gr)

file(GLOB GR_SRC "*.cpp")

if(WIN32)
	#add_subdirectory(dx11) #NOT YET DECOMPILED
	add_subdirectory(gl)
endif()

if(IOS)
	add_subdirectory(gl)
endif()

#if(WINDOWS_PHONE)
#	add_subdirectory(xna)
#endif()

add_compile_definitions(_LIB)
add_library(gr STATIC ${GR_SRC}) #grgl2 does not have build type appended and named grgl