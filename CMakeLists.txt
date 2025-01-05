# Requires CMake version greater than or equal to the following
cmake_minimum_required(VERSION 3.20)

# We indicate the name of the project and the language used
project(sprite-animation-web-win-sdl3-c LANGUAGES C)

# We write the name of the application. The file app.exe will be created
add_executable(app)

# Specify where the application source files are stored
target_sources(app
PRIVATE
    src/main.c
)

# Check for WebAssembly
if (CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    target_link_options("app" PRIVATE "SHELL:--embed-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/sprites/spritesheet.png@/assets/sprites/spritesheet.png")
    set_property(TARGET "app" APPEND PROPERTY LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/sprites/spritesheet.png")
endif()

# Check for Windows
if (WIN32)
    # Copy the assets folder to the dist folder
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:app>/assets)

    # This code copies DLL's to the dist directory
    #[===[
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:app> $<TARGET_FILE_DIR:app>
    )
    ]===]

    target_link_options(app PRIVATE -static)
endif()

# We search for the library at the specified path in -Dlib_DIR
find_package(SDL3)
find_package(SDL3_image)

# Linking libraries
target_link_libraries(app PRIVATE SDL3_image::SDL3_image SDL3::SDL3)
