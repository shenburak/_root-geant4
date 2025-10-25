# ROOT & Geant4 Two-Day Prep Workspace

Welcome! This workspace groups together curated mini-projects, study notes, and build recipes to help you ramp up quickly for intensive ROOT and Geant4 sessions. The material is organised to mimic a short bootcamp so that in two focused days you can cover fundamentals, intermediate workflows, and integration topics.

## How to Use This Workspace

- Follow the suggested study itinerary below. Each module contains its own `README.md`, source code, and build instructions (`Makefile` or `CMakeLists.txt`).
- Every example is self-contained. You can build and run each project independently without affecting the others.
- Most projects target C++17. Optional Python (PyROOT) scripts are included where they provide quicker iteration loops.
- ROOT examples rely on `root-config`. Geant4 and combined projects use CMake with `find_package(ROOT)` or Geant4's cmake configuration.

## Suggested Two-Day Itinerary

### Day 1 – ROOT Focus (5–6 hrs)

1. **Quickstart & Environment** (`root/README.md`) – confirm ROOT installation, explore `root-config`, test Cling & PyROOT. *(30 min)*
2. **Histogramming & I/O** (`root/01_basic_histogram`) – create, fill, and persist histograms. *(45 min)*
3. **Structured Data & TTrees** (`root/02_ttree_analysis`) – load CSV into a `TTree`, perform simple queries, create friend trees. *(90 min)*
4. **Fitting & Visualisation** (`root/03_pyroot_fitting`) – perform fit workflows in PyROOT, export canvases. *(60 min)*
5. **ROOT Macros & Automation** (`root/04_root_macros`) – write modular macros, batch processing, and parameter steering. *(60 min)*

### Day 2 – Geant4 & Integration (6–7 hrs)

1. **Workspace Bootstrap** (`geant4/README.md`) – review detector components, run the minimal example. *(60 min)*
2. **Geometry & Sensitive Detectors** (`geant4/01_minimal_detector`) – inspect detector construction, scoring meshes. *(90 min)*
3. **Physics Lists & Primary Generators** (`geant4/02_electromagnetic_showcase`) – customise physics lists and particle guns. *(90 min)*
4. **Advanced Output & UI** (`geant4/03_multithread_run`) – introduce run managers, multithreading, UI commands. *(60 min)*
5. **ROOT ↔ Geant4 Integration** (`combined/README.md` & `combined/01_g4_to_root`) – pipe Geant4 hits into ROOT ntuples and analyse with ROOT/PyROOT. *(90 min)*

## Repository Layout

- `root/` – pure ROOT workflows with Makefiles and optional Python helpers.
- `geant4/` – Geant4-based detectors and scoring examples built with CMake.
- `combined/` – demonstrates dual ROOT + Geant4 pipelines.
- `docs/` – supplemental cheat-sheets and configuration references.

## Prerequisites

- ROOT 6.28+ compiled with C++17 support.
- Geant4 11.x with data sets configured (e.g. via `geant4-config --datasets`).
- CMake 3.18+, a modern C++ compiler (clang++ or g++), and Python 3.9+ for PyROOT utilities.

## Tips

- Each project `README.md` lists verification commands and optional extensions.
- The `docs/cheatsheets.md` file summarises common command-line invocations, environment variables, and debugging tricks.
- Use `cmake --build build` for Geant4 projects after configuring with `cmake -S . -B build`.

Happy exploring! Let me know if you want additional topics (e.g. GDML import/export, event display integrations, or batch farm deployment scripts).
