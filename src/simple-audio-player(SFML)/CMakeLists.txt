#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.5)

project(SFML-project) #project name

set(EXECUTABLE_NAME "sfml_project")
add_executable(${EXECUTABLE_NAME} main.cpp) # compile main.cpp to generate executable EXECUTABLE_NAME

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
include(CPack)
