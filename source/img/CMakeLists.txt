project(img)

file(GLOB IMG_SRC "*.cpp")

#file(GLOB IMG_JPEG_SRC ${FUSION_DIR}/external/jpeg/*.cpp )
file(GLOB IMG_JPEG_SRC 
	${FUSION_DIR}/external/jpeg/jaricom.c
    ${FUSION_DIR}/external/jpeg/jcapimin.c
    ${FUSION_DIR}/external/jpeg/jcapistd.c
    ${FUSION_DIR}/external/jpeg/jcarith.c
    ${FUSION_DIR}/external/jpeg/jccoefct.c
    ${FUSION_DIR}/external/jpeg/jccolor.c
    ${FUSION_DIR}/external/jpeg/jcdctmgr.c
    ${FUSION_DIR}/external/jpeg/jchuff.c
    ${FUSION_DIR}/external/jpeg/jcinit.c
    ${FUSION_DIR}/external/jpeg/jcmainct.c
    ${FUSION_DIR}/external/jpeg/jcmarker.c
    ${FUSION_DIR}/external/jpeg/jcmaster.c
    ${FUSION_DIR}/external/jpeg/jcomapi.c
    ${FUSION_DIR}/external/jpeg/jcparam.c
    ${FUSION_DIR}/external/jpeg/jcprepct.c
    ${FUSION_DIR}/external/jpeg/jcsample.c
    ${FUSION_DIR}/external/jpeg/jdapimin.c
    ${FUSION_DIR}/external/jpeg/jdapistd.c
    ${FUSION_DIR}/external/jpeg/jdarith.c
    ${FUSION_DIR}/external/jpeg/jdcoefct.c
    ${FUSION_DIR}/external/jpeg/jdcolor.c
    ${FUSION_DIR}/external/jpeg/jddctmgr.c
    ${FUSION_DIR}/external/jpeg/jdhuff.c
    ${FUSION_DIR}/external/jpeg/jdinput.c
    ${FUSION_DIR}/external/jpeg/jdmainct.c
    ${FUSION_DIR}/external/jpeg/jdmarker.c
    ${FUSION_DIR}/external/jpeg/jdmaster.c
    ${FUSION_DIR}/external/jpeg/jdmerge.c
    ${FUSION_DIR}/external/jpeg/jdpostct.c
    ${FUSION_DIR}/external/jpeg/jdsample.c
    ${FUSION_DIR}/external/jpeg/jerror.c
    ${FUSION_DIR}/external/jpeg/jfdctflt.c
    ${FUSION_DIR}/external/jpeg/jfdctfst.c
    ${FUSION_DIR}/external/jpeg/jfdctint.c
    ${FUSION_DIR}/external/jpeg/jidctflt.c
    ${FUSION_DIR}/external/jpeg/jidctfst.c
    ${FUSION_DIR}/external/jpeg/jidctint.c
    ${FUSION_DIR}/external/jpeg/jmemansi.c
    ${FUSION_DIR}/external/jpeg/jmemmgr.c
    ${FUSION_DIR}/external/jpeg/jquant1.c
    ${FUSION_DIR}/external/jpeg/jquant2.c
    ${FUSION_DIR}/external/jpeg/jutils.c
)

file(GLOB IMG_PNG_SRC 
    ${FUSION_DIR}/external/libpng/png.c
    ${FUSION_DIR}/external/libpng/pngerror.c
    ${FUSION_DIR}/external/libpng/pngget.c
    ${FUSION_DIR}/external/libpng/pnginfo.c
    ${FUSION_DIR}/external/libpng/pngmem.c
    ${FUSION_DIR}/external/libpng/pngread.c
    ${FUSION_DIR}/external/libpng/pngrio.c
    ${FUSION_DIR}/external/libpng/pngrtran.c
    ${FUSION_DIR}/external/libpng/pngrutil.c
    ${FUSION_DIR}/external/libpng/pngset.c
    ${FUSION_DIR}/external/libpng/pngtrans.c
    ${FUSION_DIR}/external/libpng/pngwio.c
    ${FUSION_DIR}/external/libpng/pngwrite.c
    ${FUSION_DIR}/external/libpng/pngwtran.c
    ${FUSION_DIR}/external/libpng/pngwutil.c
)

#file(GLOB IMG_PNG_SRC ${FUSION_DIR}/external/libpng/*.c )
file(GLOB_RECURSE IMG_WEBP_SRC ${FUSION_DIR}/external/webp/*.c )
list(APPEND IMG_EXTERNAL_SRC ${IMG_JPEG_SRC} ${IMG_PNG_SRC})
#list(APPEND IMG_EXTERNAL_SRC ${IMG_JPEG_SRC} ${IMG_PNG_SRC} ${IMG_WEBP_SRC})

add_compile_definitions(IMG_JPG_SUPPORT IMG_PNG_SUPPORT IMG_IL_SUPPORT IMG_WRITER_SUPPORT IMG_WEBP_SUPPORT WIN32) #Image writing is on PC GR-MDD DLL
add_library(img STATIC ${IMG_SRC} ${IMG_EXTERNAL_SRC})
target_include_directories(img PRIVATE ${FUSION_DIR}/external/zlib ${FUSION_DIR}/external/libpng ${FUSION_DIR}/external/jpeg)