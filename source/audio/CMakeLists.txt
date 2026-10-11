project(audio)

set(AUDIO_SRC
    "AudioClip.cpp"
    "AudioClipInstance.cpp"
    "AudioMixer.cpp"
    "AudioReader.cpp"
    "AudioReader_mp3.cpp"
    "AudioReader_wav.cpp"
    "CompositeAudioClip.cpp"
    "${AUDIO_IMPL}/AudioOutputImpl_${AUDIO_IMPL}" #Win32, OpenAL [Apple]
)

#todo

#set(AUDIO_EXTERNAL_SRC
#    ${FUSION_DIR}/external/mpg123/src/compat/compat.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/dct64.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/dct64_neon.S
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/equalizer.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/format.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/frame.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/id3.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/index.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/layer3.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/libmpg123.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/optimize.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/parse.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/readers.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/synth.c
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/synth_neon.S
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/synth_stereo_neon.S
#    ${FUSION_DIR}/external/mpg123/src/libmpg123/tabinit.c
#)
#
#list(APPEND AUDIO_SRC ${AUDIO_EXTERNAL_SRC})

if(ANDROID OR FORCE_OGG) #Appears in Android and iOS, Space v2.1.0 on Steam forgot to remove it
    list(APPEND AUDIO_SRC "AudioReader_ogg_vorbis.cpp")
endif()

#if(IOS) #Not yet decompiled.
#    file(GLOB AUDIO_IOS_SRC "iOS/*.mm")
#    list(APPEND AUDIO_SRC ${AUDIO_IOS_SRC})
#endif()

#if(OSX) #Not yet decompiled.
#    file(GLOB AUDIO_OSX_SRC ${FUSION_DIR}/external/mpg123/src/libmpg123/*.c)
#    list(APPEND AUDIO_SRC ${AUDIO_OSX_SRC})
#endif()

#if(WINDOWS_PHONE) #Not yet decompiled.
#    file(GLOB AUDIO_XAUDIO2_SRC "XAudio2/*.cpp")
#    list(APPEND AUDIO_SRC ${AUDIO_XAUDIO2_SRC})
#endif()

if(${AudioWriting})
    list(APPEND AUDIO_SRC "AudioWriter.cpp" "${AUDIO_IMPL}/AudioInputImpl_${AUDIO_IMPL}") #HACK FROM KA3D
else()
    list(APPEND AUDIO_SRC "dummy/AudioInputImpl_DUMMY.cpp")
endif()

add_compile_definitions(_LIB)
add_library(audio STATIC ${AUDIO_SRC})
#target_include_directories(audio PRIVATE ${FUSION_DIR}/external/mpg123 ${FUSION_DIR}/external/mpg123/src ${FUSION_DIR}/external/mpg123/src/compat ${FUSION_DIR}/external/mpg123/src/libmpg123)