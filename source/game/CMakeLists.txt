project(game)

file(GLOB GAME_SRC "*.cpp")

if(WIN32)
    #list(APPEND GAME_SRC "win32/SystemFontImpl_WIN32.cpp") #Potentially unofficial
endif()

#if(IOS) #Not yet decompiled.
#    file(GLOB GAME_IOS_SRC "iOS/*.mm")
#    list(APPEND GAME_SRC ${GAME_IOS_SRC})
#endif()
#
#if(ANDROID) #Not yet decompiled.
#    file(GLOB GAME_ANDROID_SRC "Android/SystemFontImpl_Android.cpp") #They don't have it capitalized huh
#    list(APPEND GAME_SRC ${GAME_ANDROID_SRC})
#endif()

if (${SYSFONT_IMPL})
    list(APPEND GAME_SRC "${SYSFONT_IMPL}/SystemFontImpl_${SYSFONT_IMPL}.cpp")
else()
    list(APPEND GAME_SRC "dummy/SystemFontImpl_DUMMY.cpp")
endif()

#if(WINDOWS_PHONE) #Not yet decompiled.
#    file(GLOB GAME_XGAME2_SRC "XAudio2/*.cpp")
#    list(APPEND GAME_SRC ${GAME_XGAME2_SRC})
#endif()

add_compile_definitions(_LIB)
add_library(game STATIC ${GAME_SRC})