cmake_minimum_required(VERSION 3.10)
project(app VERSION 1.0)

# -------------
# EXTERNAL LIBS
# -------------
# Find OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

set(EXTERNAL_DIR external)

# Collecting imgui backend sources to link to target
# Only linking imgui backends for opengl and glfw, extend the regex if additional ones are required
file(GLOB_RECURSE imgui_backends CONFIGURE_DEPENDS
  ${EXTERNAL_DIR}/cimgui/imgui/backends/*.h
  ${EXTERNAL_DIR}/cimgui/imgui/backends/*.cpp
)
list(FILTER imgui_backends INCLUDE REGEX "^.*_(glfw|opengl3).*\.(h|cpp)$")

# Disable building of GLFW tests, examples and docs.
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

add_subdirectory(${EXTERNAL_DIR}/cimgui)
add_subdirectory(${EXTERNAL_DIR}/glfw)
add_subdirectory(${EXTERNAL_DIR}/glad)
add_subdirectory(${EXTERNAL_DIR}/cglm)

# ------------
# PROJECT LIBS
# ------------
set(LIB_DIR lib)
add_subdirectory(${LIB_DIR}/io)
add_subdirectory(${LIB_DIR}/gui)
add_subdirectory(${LIB_DIR}/window)
add_subdirectory(${LIB_DIR}/gfx)
add_subdirectory(${LIB_DIR}/image)

# --------------------
# LINKING ALL THE LIBS
# --------------------
add_executable(${PROJECT_NAME} src/main.c ${imgui_backends})
target_link_libraries(${PROJECT_NAME}
  image
  OpenGL::GL
  glad
  glfw
  cimgui
  io
  gui
  window
  gfx
  cglm
)