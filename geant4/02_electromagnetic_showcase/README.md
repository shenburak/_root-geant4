# 02 – Electromagnetic Physics Showcase

Highlights how to tailor the physics list, use command-based primary configuration, and collect dose profiles in layered geometries.

## Build

```sh
cmake -S . -B build -DGeant4_DIR=$(geant4-config --prefix)/lib/Geant4-11.2.0
cmake --build build
```

## Run Examples

```sh
./build/emShowcase macros/run_electron.mac
./build/emShowcase macros/run_gamma.mac
```

## Learning Goals

- Switch between reference physics lists (`FTFP_BERT`, `FTFP_BERT_EMZ`, `QGSP_BERT_HP`).
- Configure the `G4GeneralParticleSource` (GPS) entirely via macro commands.
- Record dose in layered absorbers via a `G4MultiFunctionalDetector` with several primitives (`G4PSEnergyDeposit`, `G4PSDoseDeposit`).
- Demonstrate biasing controls for EM processes.

## Extend

- Add a thin lead layer and study shielding differences.
- Toggle the `UseEMPhysics` flag at runtime and compare outputs.
- Enable production cuts per region to explore range effects.
