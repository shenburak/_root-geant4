# ROOT Module Overview

Welcome to the ROOT practice track. Work through the directories in numeric order; each example builds on the previous one while introducing new features.

## Contents

1. `01_basic_histogram` – quickstart with histograms, canvases, and `.root` output files.
2. `02_ttree_analysis` – turn structured text into TTrees, use `RDataFrame` for analysis.
3. `03_pyroot_fitting` – conduct fitting and visualisation in Python with PyROOT.
4. `04_root_macros` – create parameterised macros and batch jobs.

## Getting Ready

- Verify `root-config --version` prints the expected version.
- Test Cling: `root -l -q 'std::cout<<"ROOT ready"<<std::endl;'`.
- Test PyROOT: `python3 -c 'import ROOT; print(ROOT.__version__)'`.

## Build & Run Pattern

- Each C++ project includes a `Makefile` using `root-config` for compile and link flags.
- Run `make` to compile, then execute the produced binary (e.g. `./basic_histogram`).
- Clean with `make clean`.

## Stretch Goals

- Swap histogram binning or axis labels and observe the resulting output.
- Convert the C++ histogram example into a PyROOT script.
- Add `RDataFrame` filters or snapshots to the TTree project.
- Experiment with `ROOT::Math::MinimizerOptions::SetDefaultTolerance()` inside the fitting example.
