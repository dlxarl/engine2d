cmake_minimum_required(VERSION 3.15)
project(engine2d LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to avoid Allegro's magic main shim (useful on some platforms)
option(ALLEGRO_NO_MAGIC_MAIN "Define ALLEGRO_NO_MAGIC_MAIN to avoid allegro_main shim" OFF)
if(ALLEGRO_NO_MAGIC_MAIN)
  add_compile_definitions(ALLEGRO_NO_MAGIC_MAIN)
endif()

include(GNUInstallDirs)

# Find source files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(engine2d ${SOURCES}
        include/engine/TriangleShape.h
        src/engine/TriangleShape.cpp
        include/engine/BitmapShape.h
        src/engine/BitmapShape.cpp
        include/engine/AnimatedBitmap.h
        src/engine/AnimatedBitmap.cpp
        src/scenes/headers/Scene.h
        src/scenes/headers/Scene1.h
        src/scenes/Scene1.cpp
        src/SceneManager.cpp
        src/SceneManager.h
        src/scenes/headers/Scene2.h
        src/scenes/Scene2.cpp)

# Include our headers
target_include_directories(engine2d PRIVATE
  ${CMAKE_SOURCE_DIR}/include/engine
  ${CMAKE_SOURCE_DIR}/src/engine
)

if(WIN32)
  # --- Windows: recommend using vcpkg or prebuilt Allegro CMake targets ---
  # Recommended workflow:
  # 1) Install vcpkg: https://github.com/microsoft/vcpkg
  # 2) Install Allegro:  vcpkg install allegro:x64-windows
  # 3) Configure CMake with vcpkg toolchain file:
  #    cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake

  # Try to find Allegro via CMake package config (if provided by the distro/vcpkg)
  find_package(Allegro5 CONFIG QUIET)
  if(Allegro5_FOUND)
    # Link against typical imported targets (names may vary depending on packaging)
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
  # --- macOS / Linux: use pkg-config (Homebrew on macOS provides .pc files) ---
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

  # Use pkg_check_modules to gather include dirs and libs
  pkg_check_modules(ALLEGRO5 REQUIRED ${ALLEGRO_PKG})

  target_include_directories(engine2d PRIVATE ${ALLEGRO5_INCLUDE_DIRS})
  target_link_directories(engine2d PRIVATE ${ALLEGRO5_LIBRARY_DIRS})
  target_link_libraries(engine2d PRIVATE ${ALLEGRO5_LIBRARIES})

  # On some Unix/macOS setups you may need to link allegro_main; if you don't want
  # allegro to remap main, set ALLEGRO_NO_MAGIC_MAIN option above and don't link allegro_main.
  if(NOT ALLEGRO_NO_MAGIC_MAIN)
    # If the allegro_main pkg-config exists you can link it explicitly; pkg_check_modules
    # above may have already included it depending on packaging.
    # target_link_libraries(engine2d PRIVATE allegro_main)
  endif()
endif()

message(STATUS "Sources: ${SOURCES}")

# Simple install target
install(TARGETS engine2d RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# End of CMakeLists
