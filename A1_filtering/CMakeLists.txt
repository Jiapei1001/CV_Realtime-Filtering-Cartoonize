cmake_minimum_required(VERSION 3.15)

project(A1_FILTERING)
find_package(OpenCV REQUIRED)

# Include headers
include_directories(${OpenCV_INCLUDE_DIRS})
# Bring the headers, such as *.h into the project
include_directories(include)
# Include project compile path
include_directories(${PROJECT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Can manually add the sources using the set command as follows:
# set(SOURCES src/imgDisplay.cpp)

file(GLOB SOURCES "src/*.cpp")

add_executable(imgDisplay src/imgDisplay.cpp)
add_executable(vidDisplay src/filters.cpp src/vidDisplay.cpp)

target_link_libraries(imgDisplay ${OpenCV_LIBS})
target_link_libraries(vidDisplay ${OpenCV_LIBS})