
## engine2d (project-pgk)

A small 2D engine written in C++ using Allegro 5. The project contains a simple renderer, input handling and a minimal scene with shapes (line, rectangle, circle).

This README explains how to build and run the project on macOS / Linux and Windows, how to install dependencies, and how to troubleshoot common issues (Allegro main shim, duplicate windows, runtime crashes).

Table of contents
- Description
- Requirements
- Build (macOS / Linux)
- Build (Windows with vcpkg)
- Makefile quick build
- Troubleshooting
- CMake presets example
- License

Description
-----------
The engine demonstrates a basic structure for a software renderer and uses Allegro 5 for the display, input and some primitives. Source code is under `src/`, headers are under `include/engine`.

Requirements
------------
- A C++17-capable compiler (clang, gcc or MSVC)
- CMake >= 3.15 (recommended)
- Allegro 5 (primitives, image, font, ttf, audio, acodec)
- pkg-config (on macOS / Linux)
- On Windows: vcpkg is recommended for dependency management

Build and run (macOS / Linux)
-----------------------------
Recommended approach: CMake

1. Install dependencies (macOS Homebrew example):

```bash
brew install pkg-config
brew install allegro
```

On Linux (Debian/Ubuntu) you can install development packages if available:

```bash
sudo apt update
sudo apt install build-essential cmake pkg-config liballegro5-dev
```

2. Configure and build:

```bash
cmake -S . -B build
cmake --build build --config Release
```

3. Run the binary:

```bash
./build/engine2d
```

Quick build with the provided Makefile (macOS / Linux)
-----------------------------------------------------
If you prefer a fast local workflow, a `Makefile` is provided which uses `pkg-config` to obtain Allegro flags.

```bash
make
./bin/engine2d
```

Build and run (Windows via vcpkg + CMake)
----------------------------------------
Recommended: use vcpkg to install Allegro and let CMake pick it up via the vcpkg toolchain file.

1. Install and bootstrap vcpkg:

```powershell
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg.exe integrate install
.\vcpkg.exe install allegro:x64-windows
```

2. Configure and build from the project root:

```powershell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake -A x64
cmake --build build --config Release
.
```

Troubleshooting
---------------

- Duplicate windows (two displays open)
	- Cause: `al_create_display` is called more than once. In this project `Engine` creates the display in its constructor (`src/engine/engine.cpp`). Do not call `al_create_display` again from `main.cpp` or other modules. Keep a single owner of the display.

- dyld / symbol not found: `__al_mangled_main` (macOS)
	- Explanation: Allegro provides a shim `allegro_main` that remaps `main` to a different symbol. If the shim isn't linked or the remapping conflicts, macOS can fail with a missing symbol.
	- Fixes:
		- Define `ALLEGRO_NO_MAGIC_MAIN` before including Allegro headers to disable the magic remapping:

			```cpp
			#define ALLEGRO_NO_MAGIC_MAIN
			#include <allegro5/allegro.h>
			```

		- Or ensure you link `allegro_main` (pkg-config / CMake may provide it as `allegro_main-5`). In the cross-platform CMake we added an option `ALLEGRO_NO_MAGIC_MAIN` so you can choose.

- Program crashes with `trace trap` or immediate abort
	- Collect a backtrace with `lldb` or `gdb` to find where the crash happens. On macOS:

	```bash
	lldb -- ./build/engine2d
	(lldb) run
	(lldb) bt
	```

- Missing Allegro headers at compile time
	- Ensure Allegro is installed and pkg-config can find it. On macOS Homebrew installs Allegro and its pkg-config files to `/opt/homebrew` or `/usr/local`. Confirm `pkg-config --cflags allegro-5` prints include paths.

CMakePresets example
---------------------
You can create `CMakePresets.json` to simplify builds. Minimal example:

```json
{
	"version": 3,
	"configurePresets": [
		{ "name": "mac-clang", "generator": "Unix Makefiles" },
		{ "name": "windows-msvc", "generator": "Ninja", "cacheVariables": { "CMAKE_TOOLCHAIN_FILE": "C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake" } }
	]
}
```

Then configure with `cmake --preset mac-clang` or `cmake --preset windows-msvc`.

Developer notes
---------------
- Project layout: `src/` — sources, `include/engine` — headers. Keep platform-specific code in conditional blocks in `CMakeLists.txt` so the single build file works on macOS/Linux and Windows.
- For CI: add separate jobs for macOS and Windows and use the appropriate preset/toolchain.
