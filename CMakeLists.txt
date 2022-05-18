cmake_minimum_required(VERSION 3.7)
project(SDL_GUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set (TARGET_NAME TicketControl)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(_sources    "main.cpp" 
                "Controller.cpp"
                "Display.cpp")

include_directories(${TARGET_NAME} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR})

add_executable(${TARGET_NAME} ${_sources})

target_link_libraries(${TARGET_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})

#################### test programs ###################
set(TEST_TARGET client)
set(_test_source "test/client.cpp")

add_executable(${TEST_TARGET} "test/client.cpp")
