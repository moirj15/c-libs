cmake_minimum_required(VERSION 3.18)
project(c-libs)

set(C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(c-libs
        src/main.c
        src/Array.c
        src/GenericAllocator.c
    )

if (WIN32)
    target_link_libraries(c-libs PRIVATE
            ${CMAKE_SOURCE_DIR}/libs/SDL2/bin/SDL2-static.lib
            ${CMAKE_SOURCE_DIR}/libs/SDL2/bin/SDL2main.lib
            Setupapi.lib
            msvcrtd.lib
            imm32.lib
            version.lib
            winmm.lib
            opengl32
            gdi32

            utility_libs
            fmt
            )
else ()
    target_link_libraries(c-libs
            dl
            pthread
            )
endif ()
