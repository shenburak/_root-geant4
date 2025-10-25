# 03 – Multithreaded Run & In-Run Analysis

Showcases Geant4's multithreaded run manager with on-the-fly histogramming via `G4AnalysisManager` (ROOT backend). The target is a simple calorimeter hit by a customizable particle beam while recording run statistics.

## Build

```sh
cmake -S . -B build -DGeant4_DIR=$(geant4-config --prefix)/lib/Geant4-11.2.0 -DGEANT4_BUILD_MULTITHREADED=ON
cmake --build build
```

## Run

```sh
OMP_NUM_THREADS=4 ./build/mtCalorimeter macros/batch.mac
```

Outputs are written to `output/mt_run.root` and include per-layer energy histograms.

## Highlights

- `G4MTRunManager` usage with thread-local accumulation.
- `G4AnalysisManager` (ROOT backend) for thread-safe histogram fills and ntuple writing.
- Command macros to steer UI and adjust number of events.
- Hooks for per-thread initialisation in `ActionInitialization::BuildForMaster` / `Build`.

## Try Next

- Increase thread count and compare runtime scaling.
- Extend the ntuple with additional observables (track length, particle type).
- Replace the uniform beam with a spectrum defined in `macros/beam.mac`.
