project(audio)

set(AUDIO_SRC
    "AudioClip.cpp"
    "AudioClipInstance.cpp"
    "AudioMixer.cpp"
    "AudioReader.cpp"
    "AudioReader_mp3.cpp"
    "AudioReader_wav.cpp"
    "CompositeAudioClip.cpp"
    "${AUDIO_IMPL}/AudioOutputImpl_${AUDIO_IMPL}" #Win32, OpenAL
)

if(ANDROID OR FORCE_OGG) #Appears in Android and iOS, Space v2.1.0 on Steam forgot to remove it
    list(APPEND AUDIO_SRC "AudioReader_ogg_vorbis.cpp")
endif()

#if(IOS) #Not yet decompiled.
#    file(GLOB AUDIO_IOS_SRC "iOS/*.mm")
#    list(APPEND AUDIO_SRC ${AUDIO_IOS_SRC})
#endif()

#if(WINDOWS_PHONE) #Not yet decompiled.
#    file(GLOB AUDIO_XAUDIO2_SRC "XAudio2/*.cpp")
#    list(APPEND AUDIO_SRC ${AUDIO_XAUDIO2_SRC})
#endif()

if(${AudioWriting})
    list(APPEND AUDIO_SRC "AudioWriter.cpp" "${AUDIO_IMPL}/AudioInputImpl_${AUDIO_IMPL}")
else()
    list(APPEND AUDIO_SRC "dummy/AudioInputImpl_DUMMY.cpp")
endif()

add_compile_definitions(_LIB)
add_library(audio STATIC ${AUDIO_SRC})