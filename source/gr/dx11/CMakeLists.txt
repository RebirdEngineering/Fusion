project(grdx11)

file(GLOB GRDX11_SRC "DX11_*.cpp")
add_library(grdx11 STATIC ${GRDX11_SRC})

target_include_directories(grdx11 PRIVATE ${FUSION_DIR}/external/FX11/inc ${FUSION_DIR}/external/FX11/Binary)

#target_compile_definitions(grdx11 PRIVATE DirectX)