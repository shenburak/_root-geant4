# 04 – ROOT Macros & Batch Automation

This module shows how to organise ROOT macros for batch execution, including parameter steering with JSON and lightweight shell wrappers.

## Files

- `spectrumMacro.C` – parameterised macro generating histograms and returning a `TCanvas*`.
- `config.json` – list of configurations used by the driver script.
- `run_all.C` – Cling-friendly macro that loads `spectrumMacro.C`, iterates over the JSON, and saves outputs.
- `batch.sh` – example shell script invoking ROOT in batch mode.

## Usage

```sh
root -l -q 'run_all.C("config.json")'
./batch.sh
```

Each run produces canvases inside `output/` with descriptive filenames and a summary ROOT file for later inspection.

## Notes

- The code uses ROOT's built-in `TJSON` helper to parse the configuration.
- `spectrumMacro.C` is written to be compiled (`.x spectrumMacro.C++`) or interpreted.
- Extend `config.json` with additional parameter sets to explore a wide range of spectra.
