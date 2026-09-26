project(net)

file(GLOB NET_SRC "*.cpp" "std/*.cpp") #Std is used on Android OSX and iOS

if(IOS)
    file(GLOB NET_IOS_SRC "curl/*.cpp" "ios/*.mm")
    list(APPEND NET_SRC ${NET_IOS_SRC})
endif()

#if(ANDROID OR IOS OR OSX) #On legacy use iOS
#    file(GLOB NET_CURL_SRC "curl/*.cpp")
#    list(APPEND NET_SRC ${NET_CURL_SRC})
#endif()

add_compile_definitions(_LIB)
add_library(net STATIC ${NET_SRC})
#target_include_directories(net PRIVATE ${FUSION_DIR}/external/Fusion/include)