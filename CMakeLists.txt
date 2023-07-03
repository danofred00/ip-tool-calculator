cmake_minimum_required(VERSION 3.2)
project(IpTool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib)
#add_subdirectory(cli)
add_subdirectory(src)
