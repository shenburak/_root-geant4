# 01 – Piping Geant4 Hits into ROOT

Simulates a silicon telescope with Geant4, stores hit information in a ROOT ntuple, and analyses the output with ROOT/PyROOT helpers.

## Build

```sh
cmake -S . -B build \
  -DGeant4_DIR=$(geant4-config --prefix)/lib/Geant4-11.2.0 \
  -DROOT_DIR=$(root-config --prefix)
cmake --build build
```

## Run Simulation

```sh
./build/telescope macros/proton.mac
```

This writes `output/telescope_hits.root` containing an ntuple with one entry per hit (event id, layer id, energy deposition, position, time).

## Analyse with ROOT

```sh
root -l -q 'analysis/viewHits.C("output/telescope_hits.root")'
python3 analysis/plot_hits.py --input output/telescope_hits.root
```

## Files

- `src/` – Geant4 application with custom hit class and ROOT analysis manager wiring.
- `macros/` – command macros for beam configuration and visualisation.
- `analysis/` – ROOT macro + PyROOT script to inspect the generated dataset.

## Extensions

- Add more layers or materials to the telescope to test different configurations.
- Record whole tracks by adding a `SteppingAction` that writes to the ntuple.
- Use the PyROOT script to compute signal-to-noise ratios or apply selection/filter steps.
