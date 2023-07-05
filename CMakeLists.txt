cmake_minimum_required(VERSION 3.2)
project(IpTool LANGUAGES CXX)

set(PROJECT_VERSION 1.0.0)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/IpTools-${PROJECT_VERSION}")
include(GNUInstallDirs)

add_subdirectory(lib)
#add_subdirectory(cli)
add_subdirectory(src)

add_subdirectory(cpack)