project(a7d-pcapng)

cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 17)

# Generate Comile Commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/pcapng-lib)
add_subdirectory(${PROJECT_SOURCE_DIR}/example-app)