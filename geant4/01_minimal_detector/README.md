# 01 – Minimal Detector & Scoring Mesh

A compact Geant4 application demonstrating the essential user classes: detector construction, primary generator, physics list selection, and run/action initialisation. It records energy deposition in a scoring mesh and prints basic statistics.

## Build

```sh
cmake -S . -B build -DGeant4_DIR=$(geant4-config --prefix)/lib/Geant4-11.2.0
cmake --build build
```

## Run

```sh
./build/minimalDetector macros/init_vis.mac
./build/minimalDetector macros/run.mac
```

## Key Files

- `src/DetectorConstruction.cc` – world volume and scoring mesh.
- `src/PrimaryGeneratorAction.cc` – configurable particle gun.
- `src/RunAction.cc`, `src/EventAction.cc` – accumulate statistics.
- `macros/` – UI command files for visualisation (`init_vis.mac`) and batch runs (`run.mac`).

## Try This

- Edit `macros/run.mac` to change particle energy or type.
- Enable visualisation by launching `init_vis.mac` and using the UI.
- Add a `SteppingAction` to print the first few steps for debugging.
