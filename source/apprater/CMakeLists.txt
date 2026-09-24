project(apprater)

file(GLOB PF_SRC "*.cpp")

if(IOS)
    file(GLOB APPRATER_SRC "ios/*.mm")
endif()

add_compile_definitions(_LIB)
add_library(apprater STATIC ${APPRATER_SRC})