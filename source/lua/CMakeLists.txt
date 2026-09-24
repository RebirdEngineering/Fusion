project(lua)

file(GLOB LUA_SRC "*.cpp" "detail/*.cpp") #"detail/lua51/*.cpp" "${CMAKE_SOURCE_DIR}/external/lua51/src/*.c")

add_compile_definitions(USE_FLOAT)

add_library(lua STATIC ${LUA_SRC})