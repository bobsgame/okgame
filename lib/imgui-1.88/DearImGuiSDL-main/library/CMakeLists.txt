add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cimgui)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/imgui_software)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/imnodes)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_libraries(${SDL2_LIBRARIES})
link_libraries(thirdParty_cimgui)
link_libraries(thirdParty_imgui_software)
link_libraries(thirdParty_cimnodes)
add_library(DearImGuiSDL 
DearImGuiSDL.cpp
DearImGuiSDL.h)
set_property(TARGET DearImGuiSDL PROPERTY FOLDER "DearImGuiSDL")
set_property(TARGET DearImGuiSDL PROPERTY CXX_STANDARD 11)