# 03 – PyROOT Fitting & Visualisation

This module uses PyROOT to perform function fits, propagate uncertainties, and export polished plots. Python lets you iterate quickly while still leveraging ROOT's fitting backend.

## Requirements

- Python 3.9+
- PyROOT available on the `PYTHONPATH` (`python3 -c "import ROOT"`).
- Optional: `matplotlib` for comparison plots (used in `overlay_with_matplotlib.py`).

## Usage

```sh
python3 spectrum_fit.py --events 50000 --noise 0.4
python3 overlay_with_matplotlib.py --input spectrum.root
```

The first script generates synthetic data, performs a Gaussian + background fit, and writes both the histogram and the fit results to `spectrum.root`. The second script overlays the ROOT histogram with a matplotlib rendering for publication-ready figures.

## Highlights

- `TF1` fitting with parameter constraints.
- Uncertainty extraction via covariance matrix.
- Styled canvases and legend management.
- Interoperation with numpy/matplotlib for alternative representations.

## Try This

- Change the model to a double Gaussian to mimic detector resolution effects.
- Save the fit parameters to JSON using `json` module for downstream workflows.
- Explore `RooFit` by wrapping the histogram into a `RooDataHist` (see inline comment in `spectrum_fit.py`).
