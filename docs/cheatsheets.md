# ROOT & Geant4 Quick Reference

## Environment Helpers

- `source /path/to/thisroot.sh` – configure ROOT (updates `PATH`, `LD_LIBRARY_PATH`, `PYTHONPATH`).
- `source /path/to/geant4.sh` – configure Geant4 data sets and CMake package paths.
- `root-config --help` – list available switches (`--incdir`, `--libs`, `--ldflags`, `--features`).
- `geant4-config --help` – analogous helper for Geant4 builds.
- `echo $G4INSTALL` – confirm Geant4 install root.

## ROOT Essentials

- Interactive shell: `root -l` (use `.x macro.C` to run macros, `.L` to load libraries).
- Build flags: `$(shell root-config --cflags --libs)`.
- Write histograms: `TH1F hist("h", "Title", nbins, xmin, xmax); hist.Fill(value); hist.Write();`.
- Trees: `TTree tree("events", "Event data"); tree.Branch("energy", &energy); tree.Fill();`.
- RDataFrame: `ROOT::RDataFrame df("events", "file.root"); auto stats = df.Filter("energy>1").Mean("energy");`.
- PyROOT: `python3 - <<'PY'` block to test import quickly.

## Geant4 Essentials

- Configure: `cmake -S . -B build -DGeant4_DIR=$(geant4-config --prefix)/lib/Geant4-11.2.0` (update version as needed).
- Run: `cmake --build build && ./build/exampleApp run.mac`.
- Geometry viewer: add `vis.mac` (e.g. `/control/execute vis.mac`).
- Physics list toggle: `/control/verbose 2`, `/run/initialize`, `/process/list`. Use modular physics list `FTFP_BERT` or others.
- Particle gun: `/gun/particle proton`, `/gun/energy 200 MeV`, `/run/beamOn 10`.

## Integration Tips

- Use `G4AnalysisManager` (requires `Geant4_USE_GDML=ON` for certain features).
- For high-throughput output, prefer `TTree` over ASCII log.
- Use command macros to steer runs (store `.mac` files under `macros/`).
- Parallel jobs: `G4MTRunManager` plus `G4WorkerThread` environment; set `OMP_NUM_THREADS` when launching.

## Debugging

- ROOT: enable stack traces with `gSystem->StackTrace()`. Use `gInterpreter->ProcessLine(".ls")` to list objects.
- Geant4: run with `G4BACKTRACE=1` for extra crash diagnostics.
- Combine `valgrind --tool=memcheck` with `--log-file=valgrind.log` for memory checks.
- Use `G4EmCalculator` for quick stopping power queries inside user actions.

Keep this file open while you work; add personal notes as new commands become familiar.
