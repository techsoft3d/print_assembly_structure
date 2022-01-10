cmake_minimum_required(VERSION 3.0.0)
project(he_basic_app VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(he_basic_app main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
if(WIN32)
    include_directories(X:/HOOPS_Exchange_Publish_2021_SP2_U2/include)
else(WIN32)
    include_directories(/opt/local/ts3d/HOOPS_Exchange_2021_SP2_U2/include)
    add_link_options(he_basic_app -ldl)
endif(WIN32)
