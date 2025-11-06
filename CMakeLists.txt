cmake_minimum_required(VERSION 3.10)
project(Cubanoid)

set(CMAKE_CXX_STANDARD 17)

# Поиск всех необходимых компонентов SDL2
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

add_executable(Cubanoid main.cpp)

# Линковка через pkg-config
target_link_libraries(Cubanoid 
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

target_include_directories(Cubanoid PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)

target_compile_options(Cubanoid PRIVATE ${SDL2_CFLAGS})