cmake_minimum_required(VERSION 3.28)
project(modbus_lesson)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    #    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/O2")
    #    set(CMAKE_CXX_FLAGS_RELEASE  "/O2")

    add_definitions(-D_WIN32_WINNT=0x0A00)
    add_definitions(-DWINVER=0x0A00)

    add_definitions(-D_WIN32)

endif()

include(env.cmake)

set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

find_package (Boost REQUIRED)

file(GLOB_RECURSE SRC
        src/*.cpp
        src/connection/*.cpp
        src/connection/impls/*.cpp
        src/connection/factories/*.cpp

        src/libs/libmodbus/*.h
        src/libs/libmodbus/*.c
)

add_executable(${PROJECT_NAME} ${SRC} main.cpp
        src/wrappers/modbus_wrapper.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(modbus_lesson ws2_32)


# Если библиотека найдена, то
if (Boost_FOUND)
    include_directories (${Boost_INCLUDE_DIR}) # подключаем заголовочные файлы
    target_link_libraries (${PROJECT_NAME}  ${Boost_LIBRARIES}) # подключаем библиотеку
endif ()

