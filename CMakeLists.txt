cmake_minimum_required(VERSION 3.18)
project(c-libs)

set(C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
        ${CMAKE_SOURCE_DIR}/libs/SDL2/include
)

add_executable(c-libs
        src/main.c
        src/Array.c
        src/GenericAllocator.c
        src/Rasterizer.c
        src/Color.c
		src/String.c
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
        )
else ()
        target_link_libraries(c-libs
                dl
                pthread
                ${CMAKE_SOURCE_DIR}/libs/SDL2/bin/libSDL2.a
                ${CMAKE_SOURCE_DIR}/libs/SDL2/bin/libSDL2main.a
        )
endif ()
