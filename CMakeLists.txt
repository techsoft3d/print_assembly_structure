cmake_minimum_required(VERSION 3.0.0)
project(he_basic_app)

add_executable(he_basic_app main.cpp)
target_link_libraries(he_basic_app ${CMAKE_DL_LIBS})

if(WIN32)
    target_include_directories(he_basic_app "X:/HOOPS_Exchange_Publish_2021_SP2_U2/include")
else()
    target_include_directories(he_basic_app "/opt/local/ts3d/HOOPS_Exchange_2021_SP2_U2/include")
endif()

