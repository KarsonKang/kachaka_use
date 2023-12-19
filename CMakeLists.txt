cmake_minimum_required(VERSION 3.8)
project(videoTest)

find_package(OpenCV REQUIRED)

add_executable(videotest video.cpp)

target_include_directories(videotest PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(videotest PRIVATE ${OpenCV_LIBRARIES})