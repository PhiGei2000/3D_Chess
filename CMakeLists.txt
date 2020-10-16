cmake_minimum_required(VERSION 3.12)
project(3DChess VERSION 0.1.0)

message("Using binary dir ${CMAKE_BINARY_DIR}")
message("Using project source dir ${VoxelGame_SOURCE_DIR}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_BUILD_TYPE Debug)

# include(CTest)
# enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CAMKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GCTHREADS:16")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO /NODEFAULTLIB:MSVCRT")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")

include_directories("C:/lib/entt-master/src")
include_directories("C:/lib/GLEW/include")
include_directories("C:/lib/GLFW/include")
include_directories("C:/lib/GLM/include")
include_directories("C:/lib/SOIL/src")
include_directories("C:/lib/nlohmannjson/single_include")

find_library(GLEW_LIBRARIES glew32 C:/lib/GLEW/lib/Release/Win32)
find_library(GLFW_LIBRARIES glfw3 C:/lib/GLFW/lib)
find_library(SOIL_LIBRARIES SOIL C:/lib/SOIL/lib)

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND) 
    message("OpenGL was found")
endif()

file(GLOB_RECURSE SOURCES 
    src/*.cpp 
    include/*.hpp)

add_executable(3DChess ${SOURCES})
target_link_libraries(3DChess "-SAFESEH:NO"
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${SOIL_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
