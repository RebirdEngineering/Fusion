project(img)

file(GLOB IMG_SRC "*.cpp")

file(GLOB IMG_JPEG_SRC ${CMAKE_SOURCE_DIR}/external/jpeg/*.c )
file(GLOB IMG_PNG_SRC ${CMAKE_SOURCE_DIR}/external/libpng/*.c )
file(GLOB IMG_PNG_SRC ${CMAKE_SOURCE_DIR}/external/webp/*.c )
list(APPEND IMG_EXTERNAL_SRC ${IMG_JPEG_SRC} ${IMG_PNG_SRC})

add_compile_definitions(IMG_JPG_SUPPORT IMG_PNG_SUPPORT IMG_IL_SUPPORT IMG_WRITER_SUPPORT IMG_WEBP_SUPPORT) #Image writing is on PC GR-MDD DLL
add_library(img STATIC ${IMG_SRC} ${IMG_EXTERNAL_SRC})