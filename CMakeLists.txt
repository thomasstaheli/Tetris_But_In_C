cmake_minimum_required(VERSION 3.26)
project(name C)

# Spécifie la version du standard C à utiliser
set(CMAKE_C_STANDARD 17)  # ou 17 si tu préfères

# Liste des fichiers source du projet en C
set(PRJ_SOURCE_FILES
        main.c
        display.h
        display.c
        tetris.c
        tetris.h
        board.h
        board.c
        settings.h
        shape.c
        shape.h
)

# Création de l'exécutable
add_executable(${PROJECT_NAME}
        ${PRJ_SOURCE_FILES}
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(SDL2_INCLUDE_DIR c:/libs/sdl2/include)
    set(SDL2_LIB_DIR path c:/libs/sdl2/lib/x64)
    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIB_DIR})

    target_link_libraries(${PROJECT_NAME}
            c:/libs/sdl2/lib/x64/SDL2main.lib
            c:/libs/sdl2/lib/x64/SDL2.lib
    )
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(
            ${PROJECT_NAME} PRIVATE
            ${SDL2_LIBRARIES}
    )
    target_include_directories(
            ${PROJECT_NAME} PRIVATE
            ${SDL2_LIBRARIES}
    )
endif()
