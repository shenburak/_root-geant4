# ROOT + Geant4 Integration Track

These examples show how to bridge Geant4 simulations with ROOT analysis pipelines. The standard flow is:

1. Geant4 application writes hit/ntuple data using `G4AnalysisManager` or custom output classes.
2. ROOT / PyROOT scripts consume those outputs for fast inspection and fitting.

## Projects

1. `01_g4_to_root` – Geant4 simulation writing hit collections to ROOT, plus a companion ROOT macro for analysis.

## Suggested Workflow

- Build the Geant4 application first to generate `.root` files.
- Use the provided ROOT scripts to plot distributions, apply cuts, and compute derived quantities.
- Extend by adding more branches or aligning the schema with your real detector geometry.
