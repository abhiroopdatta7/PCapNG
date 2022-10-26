project(pcapng.app)

file(GLOB_RECURSE C_SOURCES CONFIGURE_DEPENDS "*.cc")

add_executable(${PROJECT_NAME} ${C_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC sub::pcapng)
