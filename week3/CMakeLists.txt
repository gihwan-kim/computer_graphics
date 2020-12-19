CMAKE_MINIMUM_REQUIRED (VERSION 3.15 )

# project setting
SET ( PROJ_NAME week3 )
PROJECT ( ${PROJ_NAME} )
SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR} )

# C++ settings
SET(CMAKE_CXX_STANDARD 17)

# set source and headers
SET (SRC_FILES
    src/vbo_2_triangle_4_vertices.cpp
)

# 이미 설치된 패키지를 찾는 기능
find_package(OpenGL REQUIRED)

#GLFW 라이브러리 설정
set(GLFW_LIBRARIES libglfw.dylib)
set(GLFW_INCLUDE_DIRS /usr/local/Cellar/glfw/3.3.2/include)
set(GLFW_LIBRARY_DIRS /usr/local/Cellar/glfw/3.3.2/lib)

#GLEW 라이브러리 설정
set(GLEW_LIBRARIES libGLEW.dylib)
set(GLEW_INCLUDE_DIRS /usr/local/Cellar/glew/2.2.0/include)
set(GLEW_LIBRARY_DIRS /usr/local/Cellar/glew/2.2.0/lib)


#GLM 라이브러리 설정
# set(GLEW_LIBRARIES libGLEW.dylib)
set(GLM_INCLUDE_DIRS /usr/local/Cellar/glm/0.9.9.8/include)
# set(GLEW_LIBRARY_DIRS /usr/local/Cellar/glm/0.9.9.8/lib)


INCLUDE_DIRECTORIES ( ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
LINK_LIBRARIES( ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})
LINK_DIRECTORIES ( ${OPENGL_LIBRARY_DIRS} ${GLFW_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS})

# build 
ADD_EXECUTABLE( ${PROJ_NAME} ${SRC_FILES} )