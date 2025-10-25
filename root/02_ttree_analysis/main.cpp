#include <ROOT/RDataFrame.hxx>
#include <ROOT/RDFHelpers.hxx>
#include <TFile.h>
#include <TTree.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

struct Options {
    std::string csvPath{"data/events.csv"};
    std::string outPath{"events.root"};
    bool enableSnapshot{true};
};

Options ParseArgs(int argc, char **argv) {
    Options opts;
    for (int i = 1; i < argc; ++i) {
        std::string arg{argv[i]};
        if (arg == "--csv" && i + 1 < argc) {
            opts.csvPath = argv[++i];
        } else if (arg == "--out" && i + 1 < argc) {
            opts.outPath = argv[++i];
        } else if (arg == "--no-snapshot") {
            opts.enableSnapshot = false;
        } else {
            std::cerr << "Warning: ignoring unknown argument '" << arg << "'\n";
        }
    }
    return opts;
}

void IngestCsv(const Options &opts) {
    std::ifstream input{opts.csvPath};
    if (!input.is_open()) {
        throw std::runtime_error{"Failed to open CSV file: " + opts.csvPath};
    }

    std::string header;
    std::getline(input, header);

    auto file = std::unique_ptr<TFile>{TFile::Open(opts.outPath.c_str(), "RECREATE")};
    if (!file || file->IsZombie()) {
        throw std::runtime_error{"Failed to create output ROOT file: " + opts.outPath};
    }

    TTree tree{"events", "Toy detector events"};

    int eventId = 0;
    float energy = 0.F;
    float timeNs = 0.F;
    int detectorId = 0;

    tree.Branch("event_id", &eventId, "event_id/I");
    tree.Branch("energy", &energy, "energy/F");
    tree.Branch("time_ns", &timeNs, "time_ns/F");
    tree.Branch("detector_id", &detectorId, "detector_id/I");

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream ss{line};
        std::string token;

        std::getline(ss, token, ',');
        eventId = std::stoi(token);
        std::getline(ss, token, ',');
        energy = std::stof(token);
        std::getline(ss, token, ',');
        timeNs = std::stof(token);
        std::getline(ss, token, ',');
        detectorId = std::stoi(token);

        tree.Fill();
    }

    tree.Write();
    file->Write();
    file->Close();

    std::cout << "Wrote " << tree.GetEntries() << " entries to " << opts.outPath << "\n";
}

void RunRDataFrame(const Options &opts) {
    ROOT::EnableImplicitMT();

    ROOT::RDataFrame df{"events", opts.outPath};

    auto nEntries = df.Count();
    auto meanEnergy = df.Mean("energy");
    auto histEnergy = df.Histo1D({"h_energy", "Energy;E [MeV];Counts", 40, 0., 8.}, "energy");

    auto efficiencyByDetector = df.Define("isHigh", "energy>4.5")
        .GroupBy("detector_id")
        .Define("highFraction", [](const ROOT::RVec<int> &detIds, const ROOT::RVec<char> &mask) {
            std::unordered_map<int, std::pair<int, int>> counts;
            for (std::size_t i = 0; i < detIds.size(); ++i) {
                auto &entry = counts[detIds[i]];
                ++entry.first;
                if (mask[i]) {
                    ++entry.second;
                }
            }
            return counts;
        }, {"detector_id", "isHigh"});

    efficiencyByDetector.Foreach([](const std::unordered_map<int, std::pair<int, int>> &counts) {
        for (const auto &[det, stat] : counts) {
            double fraction = (stat.first == 0) ? 0.0 : static_cast<double>(stat.second) / static_cast<double>(stat.first);
            std::cout << "Detector " << det << ": high-energy fraction = " << fraction << "\n";
        }
    });

    std::cout << "Entries: " << *nEntries << "\n";
    std::cout << "Mean energy: " << *meanEnergy << " MeV\n";

    auto out = std::unique_ptr<TFile>{TFile::Open("analysis.root", "RECREATE")};
    if (out && !out->IsZombie()) {
        histEnergy->Write();
        out->Write();
    }

    if (opts.enableSnapshot) {
        df.Filter("energy>4.5").Snapshot("events_high", "events_high.root", {"event_id", "energy", "time_ns", "detector_id"});
        std::cout << "Snapshots stored in events_high.root\n";
    }
}

int main(int argc, char **argv) {
    try {
        auto opts = ParseArgs(argc, argv);
        IngestCsv(opts);
        RunRDataFrame(opts);
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
