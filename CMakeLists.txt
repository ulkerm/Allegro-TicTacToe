cmake_minimum_required(VERSION 3.26)
project(HelloAllegro VERSION 1.0.0 LANGUAGES C)

# set your executable name
set(EXECUTABLE_NAME TicTacToe)

# add your source files here
set(SOURCES
        src/game/main.c
        src/game/resources.h src/game/resources.c
        src/game/utils.h src/game/utils.c
        src/game/game.h src/game/game.c
        src/game/board.h src/game/board.c
)

# all listed resources files are copied to the binary directory, so the executable can find them at runtime
# add your fonts, images, ... here
set(RESOURCE_FILES
        resources/ARCADE.TTF
)

link_directories(/usr/local/Cellar/allegro/5.2.8.0_2/lib)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

# set compile options for executable
set(CMAKE_C_STANDARD 99)
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# Allegro
#
# find pkg-config

# Troubleshoot Problems:
# set(CMAKE_FIND_DEBUG_MODE TRUE)
# set(CMAKE_PREFIX_PATH "/opt/homebrew/lib")

INCLUDE(FindPkgConfig)
# search allegro libraries with pkg-config
# add other required addons here
pkg_check_modules(ALLEGRO5 REQUIRED
        allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_ttf-5 allegro_dialog-5)

# link against allegro libraries
target_link_libraries(${EXECUTABLE_NAME} ${ALLEGRO5_LIBRARIES})
# add allegro include directories
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${ALLEGRO5_INCLUDE_DIRS})

#copy resource files to binary dir, execute cmd after the executable was built
foreach( file_i ${RESOURCE_FILES})
    add_custom_command(TARGET ${EXECUTABLE_NAME}  POST_BUILD
            COMMAND "${CMAKE_COMMAND}"
            ARGS -E copy "${file_i}" "${PROJECT_BINARY_DIR}/${file_i}"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endforeach( file_i )

