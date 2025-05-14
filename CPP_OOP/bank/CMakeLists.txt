# Auto-generated CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(bank VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# === Source Files ===
set(SRC_FILES
    main.cpp
)

# === Executable Target ===
add_executable(bank_exec ${SRC_FILES})

# === Include Directories ===
target_include_directories(bank_exec PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# === Optional: Compiler Warnings ===
# Enable common compiler warnings (useful for development)
# target_compile_options(main_exec PRIVATE -Wall -Wextra -pedantic)

# === Link Libraries ===
# - To add more libraries, use additional `target_link_libraries()` calls.
# - To make this reusable: copy this as a template and change project name, source files, and paths.
# - For better structure, keep external paths in variables or use Find modules.
# target_link_libraries(bank_exec PRIVATE /home/cnc/Desktop/BUILD_2/raylib/build/raylib/libraylib.a)

# Include directories for header files
# We are adding two directories here, one from the source folder and one from a third-party library
# target_include_directories(my_tetris_game PRIVATE /include)
# target_include_directories(my_tetris_game PRIVATE /thirdparty/some_library/include)

# Link libraries to the executable
# Here, we're linking a static library (raylib) to the project
# target_link_libraries(my_tetris_game PRIVATE /libs/raylib.a)

# Custom command to copy a file after the build process
# add_custom_command(
#     TARGET my_tetris_game POST_BUILD
#     COMMAND  -E copy /Sounds/music.mp3 /build/Sounds/music.mp3
# )

# Create a custom target that will copy files automatically during the build
# add_custom_target(copy_files ALL
#     COMMAND  -E copy /Sounds/music.mp3 /build/Sounds/music.mp3
# )

# Add other build configurations or post-build actions as needed
# add_custom_command(
#     TARGET my_tetris_game POST_BUILD
#     COMMAND  -E echo "Build completed successfully!"
# )

# Set the installation directory for the project
# The default install directory is /usr/local, but you can change it
# set(CMAKE_INSTALL_PREFIX /install)

# Optionally, you can install the executable and/or libraries
# install(TARGETS my_tetris_game DESTINATION /install/bin)

# Optionally, install headers
# install(DIRECTORY /include/ DESTINATION /install/include)

# Check and print the compiler being used (useful for debugging)
# if(MSVC)
#     message("Using Visual Studio Compiler")
# elseif(CMAKE_COMPILER_IS_GNUCXX)
#     message("Using GCC Compiler")
# endif()

# Find packages for external dependencies
# This looks for OpenGL, for example
# find_package(OpenGL REQUIRED)

# Link the found OpenGL package to the target
# target_link_libraries(my_tetris_game PRIVATE OpenGL::GL)

# Check for other dependencies or external libraries
# find_library(RAYLIB_LIBRARY raylib PATHS /path/to/raylib)
# target_link_libraries(my_tetris_game PRIVATE )

# If you want to enable tests, you can use this:
# enable_testing()

# Create a simple test (example: test linking)
# add_test(NAME TestHello COMMAND my_tetris_game)

# Handle versioning
# Automatically makes the version accessible through the  variable
# project(MyTetrisGame VERSION 1.0 LANGUAGES CXX)

# Show some project info at configuration time
# message("Project Name: ")
# message("Project Version: ")
# message("C++ Standard: ")
# message("Build type: ")

