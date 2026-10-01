project(apprater)

if(IOS) #Only exists on Apple
    list(APPEND APPRATER_SRC "ios/*.mm")
endif()

add_compile_definitions(_LIB)
add_library(apprater STATIC ${APPRATER_SRC})