cmake_minimum_required(VERSION 4.1.2)
project(totally_not_italian)

set(CMAKE_CXX_STANDARD 26)

add_subdirectory(dependencies)
add_subdirectory(src)

target_link_libraries(totally_not_italian PRIVATE
    SFML::Graphics
    SFML::Audio
)

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
        "${CMAKE_CURRENT_BINARY_DIR}/src/assets"
        COMMENT "Copying data"
)

add_dependencies(totally_not_italian copy_assets)
