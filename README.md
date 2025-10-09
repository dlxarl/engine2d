# project-pgk

Minimal C++ project that demonstrates Allegro initialization.

Requirements
- macOS with Homebrew
- Allegro (install with `brew install allegro`)

Build
1. Ensure pkg-config can find Allegro (Homebrew usually does this automatically).
2. Run:

```sh
make
```

Run

```sh
./bin/project-pgk
```

If the program fails to compile because headers are missing, install Allegro with Homebrew and ensure `/usr/local` or `/opt/homebrew` pkg-config paths are in PKG_CONFIG_PATH.
