cmake_minimum_required(VERSION 3.18)
project(PrintAssemblyStructure)

set(EXCHANGE_PACKAGE_PATH "" CACHE PATH "Path to Exchange")
if(NOT EXCHANGE_PACKAGE_PATH)
    message(FATAL_ERROR "EXCHANGE_PACKAGE_PATH must be set to a valid folder path.")
endif()

set(HE_DATA_DIRECTORY "${EXCHANGE_PACKAGE_PATH}/samples/data")
if(WIN32)
    set(HE_BINARY_DIRECTORY_NAME win32_v142)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(HE_BINARY_DIRECTORY_NAME win64_v142)
    endif()
elseif(APPLE)
    set(HE_BINARY_DIRECTORY_NAME macos)
else()
    set(HE_BINARY_DIRECTORY_NAME linux32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(HE_BINARY_DIRECTORY_NAME linux64)
    endif()
endif()

set(HE_BINARY_DIRECTORY ${EXCHANGE_PACKAGE_PATH}/bin/${HE_BINARY_DIRECTORY_NAME})

add_executable(PrintAssemblyStructure main.cpp)
target_include_directories(PrintAssemblyStructure PRIVATE 
    "${EXCHANGE_PACKAGE_PATH}/include"
)
target_compile_definitions(PrintAssemblyStructure PRIVATE 
    HE_BINARY_DIRECTORY="${HE_BINARY_DIRECTORY}"
    HE_DATA_DIRECTORY="${HE_DATA_DIRECTORY}"
)
