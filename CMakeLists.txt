cmake_minimum_required(VERSION 3.10)
project(engine2d)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Allegro через pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(ALLEGRO5 REQUIRED
    allegro-5
    allegro_main-5
    allegro_primitives-5
    allegro_image-5
    allegro_font-5
    allegro_ttf-5
    allegro_audio-5
    allegro_acodec-5
)

# Шляхи до include Allegro та наших заголовків
include_directories(
    ${ALLEGRO5_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include/engine
    ${CMAKE_SOURCE_DIR}/src/engine
)

link_directories(${ALLEGRO5_LIBRARY_DIRS})

# Усі .cpp файли з src/
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(engine2d ${SOURCES})

# Підключаємо бібліотеки Allegro
target_link_libraries(engine2d ${ALLEGRO5_LIBRARIES})
