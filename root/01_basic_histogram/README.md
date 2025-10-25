# 01 – Basic Histogram & Canvas

This starter showcases how to create histograms, manage canvases, and store results in `.root` files. Run it first to ensure your ROOT toolchain works end-to-end.

## Build

```sh
make
```

## Run

```sh
./basic_histogram
root -l output.root
```

Inside the ROOT shell, try `.ls` to see saved objects, and `hist->Draw()` to check the histogram.

## Key Concepts

- `TApplication` bootstrapping for headless or batch mode.
- `TH1F` histogram creation and filling.
- Persisting results via `TFile`.
- Exporting canvases to image formats.

## Exercises

- Change the distribution to Gaussian noise and compare shapes.
- Add a second histogram and overlay it with `hist->SetLineColor()`.
- Try running the program with `./basic_histogram --batch` to skip the GUI draw step.
