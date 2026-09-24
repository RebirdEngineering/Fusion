file(GLOB MATH_SRC "*.cpp") #Float2x3 is never built as a cpp file ASIDE FROM TRILOGII and ABCTW
add_compile_definitions(_LIB)
add_library(math STATIC ${MATH_SRC})