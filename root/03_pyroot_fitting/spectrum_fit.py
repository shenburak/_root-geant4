#!/usr/bin/env python3
"""Oyuncak bir spektrumu üretip uyumlayarak sonuçları arşivler."""

import argparse
import math
import random
from pathlib import Path

import ROOT


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Fit a toy spectrum with PyROOT")
    # Kullanıcının deney parametrelerini esnek biçimde belirleyebilmesi için argümanlar tanımlıyoruz.
    parser.add_argument("--events", type=int, default=20000, help="Number of events to generate")
    parser.add_argument("--noise", type=float, default=0.25, help="Background contamination level")
    parser.add_argument("--out", type=Path, default=Path("spectrum.root"), help="Output ROOT file")
    parser.add_argument("--batch", action="store_true", help="Disable interactive canvas display")
    return parser.parse_args()


def generate_events(n_events: int, noise_scale: float) -> ROOT.TH1F:
    hist = ROOT.TH1F("h_spectrum", "Toy Spectrum;Energy [MeV];Counts", 120, 0.0, 12.0)
    rng = random.Random()
    # Her olay için gürültü veya sinyal dağılımından örnek çekiyoruz.
    for _ in range(n_events):
        if rng.random() < noise_scale:
            value = rng.expovariate(1.5) + 2.0
        else:
            value = rng.gauss(6.0, 0.9)
        hist.Fill(value)
    return hist


def build_model() -> ROOT.TF1:
    model = ROOT.TF1("f_model", "gaus(0) + expo(3)", 0.0, 12.0)
    # Başlangıç parametreleri uyum hızını artırmak için makul fiziksel değerlerden seçildi.
    model.SetParameters(500.0, 6.0, 0.9, 1.0, -0.5)
    model.SetParNames("Amplitude", "Mean", "Sigma", "Norm", "Slope")
    model.SetParLimits(2, 0.1, 2.5)
    return model


def main() -> None:
    args = parse_args()
    ROOT.gROOT.SetBatch(args.batch)

    hist = generate_events(args.events, args.noise)

    model = build_model()
    # "S" seçeneği ile uyum sonuç nesnesini (TFitResultPtr) geri alıyoruz.
    fit_result = hist.Fit(model, "S")

    canvas = ROOT.TCanvas("c_fit", "Fit", 800, 600)
    hist.SetLineColor(ROOT.kAzure + 1)
    hist.SetMarkerStyle(20)
    hist.Draw("E")
    model.SetLineColor(ROOT.kRed)
    model.Draw("same")

    legend = ROOT.TLegend(0.6, 0.7, 0.88, 0.88)
    legend.AddEntry(hist, "Toy data", "lep")
    legend.AddEntry(model, "Fit", "l")
    legend.Draw()

    canvas.SaveAs("spectrum_fit.png")

    # Fit çıktısını hem görsel hem de sayısal olarak arşivliyoruz.
    out_file = ROOT.TFile(str(args.out), "RECREATE")
    hist.Write()
    model.Write("fit_model")
    canvas.Write()
    out_file.Close()

    print("Chi2/NDF:", fit_result.Chi2() / fit_result.Ndf())
    for idx in range(model.GetNpar()):
        print(f"{model.GetParName(idx)} = {model.GetParameter(idx):.4f} ± {model.GetParError(idx):.4f}")

    with open("fit_report.txt", "w", encoding="ascii") as report:
        report.write("Fit summary\n")
        report.write(f"Chi2 = {fit_result.Chi2():.3f}\n")
        report.write(f"Ndf = {fit_result.Ndf()}\n")
        for idx in range(model.GetNpar()):
            report.write(
                f"{model.GetParName(idx)} = {model.GetParameter(idx):.6f} ± {model.GetParError(idx):.6f}\n"
            )

    if not args.batch:
        canvas.Update()
            # Etkileşimli modda kullanıcı grafiği inceleyebilsin diye çıkışı geciktiriyoruz.
        input("Press <Enter> to exit...")


if __name__ == "__main__":
    main()
