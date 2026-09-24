cmake_minimum_required(VERSION 3.10)
project(Fusion)

set (CMAKE_CXX_STANDARD 11)

link_directories($ENV{DXSDK_DIR}/Lib/x86) #DirectX 11/+ SDK libs must be installed, won't be distributed, otherwise modify this
include_directories($ENV{DXSDK_DIR}/Include ${CMAKE_SOURCE_DIR}) #DirectX 11/+ SDK must be installed, won't be distributed, otherwise modify this, yeah we include the root too for includes, that way we can use #include <external/*.h>, which is probably what they did.

#link_directories(${CMAKE_SOURCE_DIR}/lib/msvc17)

#option(RFusion "Build official (Angry Birds) Fusion" ON)
#option(LegacyFusion "Build legacy Fusion" OFF)
#option(ABC520Fusion "Build ABC520/+ Fusion" OFF)
#option(FunFusion "Build FunLabs Fusion Fork" OFF)
#option(XGSFusion "Build XGS Fusion Fork" OFF)
#option(SeasideFusion "Build Fruit Nibblers Fusion Fork" OFF)
option(BuildTests "Build tests for supported modules" OFF)
option(AudioPlayback "Build audio playback implementations" ON)
option(AudioWriting "Build audio writing implementations" OFF)
#option(RestoreStrippedLegacyCode "Restores stripped (and/or potentially debug) code from legacy releases" OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib) #Realistically we'd use msvc17 or xcode4 [apple], given this is CMake

set(FUSION_DIR ${CMAKE_CURRENT_SOURCE_DIR}) #So io won't get mad

add_compile_definitions(_CRT_SECURE_NO_DEPRECATE HGR_NOPARTICLES WEBP_USE_THREAD UNICODE GLEW_STATIC ) #USE_THREAD is off?

set(AUDIO_IMPL "Win32" CACHE STRING "The implementation for audio.")
set(SYSFONT_IMPL "DUMMY" CACHE STRING "The implementation for system fonts.") #TEMP
set(FLURRY_IMPL "DUMMY" CACHE STRING "The implementation for flurry.") #TEMP
#set(GAMERSERVICES_IMPL "DUMMY.cpp" CACHE STRING "The implementation for fusiongamerservices.")

if(NOT PLATFORM)
    if(WIN32) # THIS ASSUMES VCPKG OR SOURCES !!!!!!!
        set(PLATFORM "Win32" CACHE STRING "The platform to compile for.")
    elseif(ANDROID)
        set(PLATFORM "Android" CACHE STRING "The platform to compile for.")
        set(SYSFONT_IMPL "Android")
    elseif(IOS)
        set(PLATFORM "iOS" CACHE STRING "The platform to compile for.")
        set(AUDIO_IMPL "OpenAL") #We'd use iOS, but we haven't decompiled iOS yet.
        set(SYSFONT_IMPL "iOS")
        set(FLURRY_IMPL "iOS")
    elseif(OSX)
        set(PLATFORM "OSX" CACHE STRING "The platform to compile for.")
        set(AUDIO_IMPL "OpenAL" CACHE STRING "The implementation for audio.")
    elseif(WINDOWS_STORE)
        set(PLATFORM "WinRT" CACHE STRING "The platform to compile for.")
    else()
        set(PLATFORM ${CMAKE_SYSTEM_NAME} CACHE STRING "The platform to compile for.")
    endif()
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/external)

add_subdirectory(source)

#Original engine developed by Pixelgene (now Rovio) and its semi-open-source releases can be found @ https://sourceforge.net/projects/ka3d/ (KA3D 1.4) and https://github.com/kajala/making-game-demo-book (KA3D 1.0)