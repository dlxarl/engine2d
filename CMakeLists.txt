cmake_minimum_required(VERSION 3.15)
project(engine2d LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ALLEGRO_NO_MAGIC_MAIN "Define ALLEGRO_NO_MAGIC_MAIN to avoid allegro_main shim" OFF)
if(ALLEGRO_NO_MAGIC_MAIN)
  add_compile_definitions(ALLEGRO_NO_MAGIC_MAIN)
endif()

include(GNUInstallDirs)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(engine2d ${SOURCES})

target_include_directories(engine2d PRIVATE
        ${CMAKE_SOURCE_DIR}/include/engine
        ${CMAKE_SOURCE_DIR}/src/engine
)

if(WIN32 AND NOT MINGW)
  find_package(Allegro5 CONFIG QUIET)
  if(Allegro5_FOUND)
    target_link_libraries(engine2d PRIVATE
            Allegro::allegro
            Allegro::allegro_primitives
            Allegro::allegro_image
            Allegro::allegro_font
            Allegro::allegro_ttf
            Allegro::allegro_audio
            Allegro::allegro_acodec
    )
  else()
    message(FATAL_ERROR "Allegro not found on Windows. Install via vcpkg and set CMAKE_TOOLCHAIN_FILE or provide Allegro CMake config.")
  endif()

else()
  find_package(PkgConfig REQUIRED)

  set(ALLEGRO_PKG
          allegro-5
          allegro_main-5
          allegro_primitives-5
          allegro_image-5
          allegro_font-5
          allegro_ttf-5
          allegro_audio-5
          allegro_acodec-5
  )

  pkg_check_modules(ALLEGRO5 REQUIRED ${ALLEGRO_PKG})

  target_include_directories(engine2d PRIVATE ${ALLEGRO5_INCLUDE_DIRS})
  target_link_directories(engine2d PRIVATE ${ALLEGRO5_LIBRARY_DIRS})
  target_link_libraries(engine2d PRIVATE ${ALLEGRO5_LIBRARIES})

  if(NOT ALLEGRO_NO_MAGIC_MAIN)
  endif()
endif()

message(STATUS "Sources: ${SOURCES}")

install(TARGETS engine2d RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})