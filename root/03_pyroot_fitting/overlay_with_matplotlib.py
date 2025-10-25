#!/usr/bin/env python3
"""ROOT histogramını matplotlib ile yayın kalitesinde görselleştirir."""

import argparse
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
import ROOT


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Overlay a ROOT histogram using matplotlib")
    # ROOT dosyasını ve histogram ismini dışarıdan alarak betiği yeniden kullanılabilir kılıyoruz.
    parser.add_argument("--input", type=Path, default=Path("spectrum.root"), help="Input ROOT file")
    parser.add_argument("--hist", default="h_spectrum", help="Histogram name inside the ROOT file")
    parser.add_argument("--out", type=Path, default=Path("spectrum_matplotlib.png"), help="Output image file")
    return parser.parse_args()


def main() -> None:
    args = parse_args()

    root_file = ROOT.TFile.Open(str(args.input), "READ")
    if not root_file or root_file.IsZombie():
        raise RuntimeError(f"Cannot open {args.input}")

    hist = root_file.Get(args.hist)
    if not hist:
        raise RuntimeError(f"Histogram {args.hist} not found in {args.input}")

    nbins = hist.GetNbinsX()
    # ROOT histogramından bin merkezlerini, değerlerini ve hatalarını NumPy dizilerine aktarıyoruz.
    bin_centres = np.array([hist.GetBinCenter(i) for i in range(1, nbins + 1)])
    bin_values = np.array([hist.GetBinContent(i) for i in range(1, nbins + 1)])
    bin_errors = np.array([hist.GetBinError(i) for i in range(1, nbins + 1)])

    plt.style.use("seaborn-v0_8-darkgrid")
    fig, ax = plt.subplots(figsize=(8, 5))
    ax.errorbar(bin_centres, bin_values, yerr=bin_errors, fmt="o", color="tab:blue", label="ROOT bins")

    fit = root_file.Get("fit_model")
    if fit:
        # Uyum eğrisini matplotlib tarafında pürüzsüz çizmek için yoğun bir x ızgarası örnekliyoruz.
        x_vals = np.linspace(hist.GetXaxis().GetXmin(), hist.GetXaxis().GetXmax(), 400)
        y_vals = np.array([fit.Eval(x) for x in x_vals])
        ax.plot(x_vals, y_vals, color="tab:red", linewidth=2.0, label="Fit model")

    ax.set_xlabel(hist.GetXaxis().GetTitle())
    ax.set_ylabel(hist.GetYaxis().GetTitle())
    ax.set_title("Toy Spectrum Fit")
    ax.legend()
    fig.tight_layout()
    fig.savefig(args.out, dpi=160)
    print(f"Saved overlay to {args.out}")


if __name__ == "__main__":
    main()
