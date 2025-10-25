#!/usr/bin/env python3
"""Plot Geant4 telescope hits stored in ROOT."""

import argparse
from pathlib import Path

import ROOT


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Plot telescope hit distributions")
    parser.add_argument("--input", type=Path, default=Path("output/telescope_hits.root"), help="ROOT file path")
    parser.add_argument("--batch", action="store_true", help="Disable canvas display")
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    ROOT.gROOT.SetBatch(args.batch)

    file = ROOT.TFile.Open(str(args.input), "READ")
    if not file or file.IsZombie():
        raise RuntimeError(f"Cannot open {args.input}")

    tree = file.Get("hits")
    if not tree:
        raise RuntimeError("Tree 'hits' not found")

    canvas = ROOT.TCanvas("c_py", "PyROOT Hit Plots", 900, 600)
    canvas.Divide(2, 1)

    canvas.cd(1)
    tree.Draw("energy_keV>>hEnergy(120,0,400)", "", "hist")
    h_energy = ROOT.gPad.GetPrimitive("hEnergy")
    if h_energy:
        h_energy.SetLineColor(ROOT.kAzure + 1)
        h_energy.SetFillColorAlpha(ROOT.kAzure - 9, 0.35)
        h_energy.SetXTitle("Energy [keV]")
        h_energy.SetYTitle("Counts")

    canvas.cd(2)
    tree.Draw("y_mm:x_mm>>hXY(80,-50,50,80,-50,50)", "", "colz")
    h_xy = ROOT.gPad.GetPrimitive("hXY")
    if h_xy:
        h_xy.SetTitle("Impact map;x [mm];y [mm]")

    canvas.SaveAs("telescope_hits_py.png")

    if not args.batch:
        canvas.Update()
        input("Press <Enter> to close...")

    file.Close()


if __name__ == "__main__":
    main()
