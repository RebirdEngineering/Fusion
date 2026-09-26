project(grgl)

find_package(OpenGL REQUIRED)

#ios uses GLES1 and GLES2

file(GLOB GRGL_SRC "GL_*.cpp")
file(GLOB GRGL2_SRC "*.cpp")
add_compile_definitions(_LIB)
#add_library(grgl1 STATIC ${GRGL_SRC})
#add_library(grgl2 STATIC ${GRGL_SRC} ${GRGL2_SRC})
#add_library(grgles1 STATIC ${GRGL_SRC})
add_library(grgles2 STATIC ${GRGL_SRC} ${GRGL2_SRC})

#target_link_libraries(gl2 PUBLIC OpenGL::GL)

#target_compile_definitions(grgl1 PRIVATE GL1)
#target_compile_definitions(grgl2 PRIVATE GL2)
#target_compile_definitions(grgles1 PRIVATE GLES1)
target_compile_definitions(grgles2 PRIVATE GLES2)