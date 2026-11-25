cmake_minimum_required(VERSION 3.20)
project(forja_cero C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Habilitar AddressSanitizer y UBSan" OFF)

# Descarga y compila Raylib automáticamente
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)

# Ejecutable principal (después se van sumando los demás .c acá)
add_executable(${PROJECT_NAME}
    src/main.c
    src/core/logs.c
    src/core/clock.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Warnings estrictos solo para tu código
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
    if(ENABLE_SANITIZERS)
        target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined -g)
        target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
    endif()
endif()