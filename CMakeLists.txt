cmake_minimum_required(VERSION 3.10)
project(app VERSION 1.0)


###########################
#      EXTERNAL LIBS      #
###########################

# --- CIMGUI ---
# Only linking imgui backends for opengl and glfw, extend the regex if additional ones are required
file(GLOB_RECURSE imgui_backends CONFIGURE_DEPENDS external/cimgui/imgui/backends/*.h external/cimgui/imgui/backends/*.cpp)
list(FILTER imgui_backends INCLUDE REGEX "^.*_(glfw|opengl3).*\.(h|cpp)$")

add_subdirectory(external/cimgui)

# --- OpenGL ---
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# --- GLFW ---
# Disable building of GLFW tests, examples and docs.
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)

# --- GLAD ---
add_subdirectory(external/glad)


##########################
#      PROJECT LIBS      #
##########################

# --- IO ---
add_subdirectory(lib/io)

# --- GUI ---
add_subdirectory(lib/gui)

# --- WINDOW ---
add_subdirectory(lib/window)


# --- GFX ---
add_subdirectory(lib/gfx)


##################################
#      LINKING ALL THE LIBS      #
##################################

add_executable(${PROJECT_NAME} src/main.c ${imgui_backends})
target_link_libraries(${PROJECT_NAME}
  OpenGL::GL
  glad
  glfw
  cimgui
  io
  gui
  window
  gfx
)