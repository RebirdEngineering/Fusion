if(APPLE) #Only exists on Apple
project(apprater)

if(IOS) #Not yet decompiled
    list(APPEND APPRATER_SRC "ios/*.mm")
#else #Unknown or reused?
#    list(APPEND APPRATER_SRC "osx/*.mm")
endif()

add_compile_definitions(_LIB)
add_library(apprater STATIC ${APPRATER_SRC})
endif()