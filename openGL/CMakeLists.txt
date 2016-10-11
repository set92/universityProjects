cmake_minimum_required(VERSION 3.6)
project(openGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)

file(GLOB SOURCE_FILES
        exercise2/*.c
        exercise2/*.h
        )

add_executable(openGL ${SOURCE_FILES} exercise2/main.c )

link_directories(${OPENGL_gl_LIBRARY})

target_link_libraries (openGL ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARIES})
