# Geant4 Module Overview

These examples progress from a minimal detector construction to more advanced physics configurations and multithreaded runs. Build each project with CMake (out-of-source builds recommended).

## Projects

1. `01_minimal_detector` – basic box detector with scoring mesh and particle gun macro.
2. `02_electromagnetic_showcase` – explores physics list customisation and primary generator actions.
3. `03_multithread_run` – demonstrates multithreaded execution, command macros, and analysis manager usage.

## Build Pattern

```sh
cmake -S . -B build -DGeant4_DIR=$(geant4-config --prefix)/lib/Geant4-11.2.0
cmake --build build
```

Run the executables from their respective directories, passing the provided macro files (e.g. `./build/minimalDetector macros/run.mac`).

## Suggested Reading

- Geant4 Application Developers Guide (chapters on detector construction, primary generators, run/action classes).
- Examples B1, B3, and extended/analysis from the Geant4 distribution for complementary context.
