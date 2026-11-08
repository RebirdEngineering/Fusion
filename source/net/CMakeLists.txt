project(net)

file(GLOB NET_SRC "*.cpp" "std/*.cpp") #Std is used on Android OSX and iOS

if(IOS) #iOS impl
    file(GLOB NET_IOS_SRC "ios/*.mm")
    list(APPEND NET_SRC ${NET_IOS_SRC})
else() #Win32, Android, OSX
    file(GLOB NET_CURL_SRC "curl/*.cpp")
    list(APPEND NET_SRC ${NET_CURL_SRC})
endif()

add_compile_definitions(_LIB)
add_library(net STATIC ${NET_SRC})