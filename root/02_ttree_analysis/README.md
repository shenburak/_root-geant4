# 02 – TTree Ingestion & RDataFrame Analysis

Convert structured text into ROOT objects, then explore the dataset with modern analysis tools.

## Workflow

1. Build the helper executable and run it to generate `events.root`.
2. Inspect the stored tree interactively in ROOT.
3. Run the included RDataFrame analysis to produce summary histograms and tables.

## Build & Run

```sh
make
./ingest --csv data/events.csv --out events.root
root -l events.root
```

Inside ROOT:

```cpp
TTree *tree = nullptr;
file->GetObject("events", tree);
tree->Print();
tree->Draw("energy>>h(40,0,8)");
```

## Files

- `main.cpp` – reads CSV, fills a `TTree`, triggers `RDataFrame` analysis step.
- `analysis.cpp` – optional standalone tool for additional RDataFrame cuts.
- `data/events.csv` – toy dataset.

## Experiments

- Add more columns (e.g. `temperature`) to the CSV and extend the branch definitions.
- Replace the CSV reader with a `ROOT::RDF::MakeCsvDataFrame` pipeline.
- Observe how `RDataFrame::Snapshot` writes filtered trees for later processing.
