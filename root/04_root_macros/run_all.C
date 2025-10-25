#include <TCanvas.h>
#include <TROOT.h>
#include <TSystem.h>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct RunConfig {
    std::string label;
    int entries{0};
    double mean{0.0};
    double sigma{1.0};
    double background{0.0};
};

TCanvas *spectrumMacro(int entries,
                       double mean,
                       double sigma,
                       double background,
                       const char *label,
                       const char *outDir);

std::string ReadFile(const std::string &path) {
    std::ifstream in{path};
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open config file: " + path);
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

std::string Trim(const std::string &input) {
    auto begin = std::find_if_not(input.begin(), input.end(), [](int ch) { return std::isspace(ch); });
    auto end = std::find_if_not(input.rbegin(), input.rend(), [](int ch) { return std::isspace(ch); }).base();
    if (begin >= end) {
        return {};
    }
    return std::string(begin, end);
}

std::string ExtractRaw(const std::string &object, const std::string &key) {
    auto needle = std::string("\"") + key + "\"";
    auto keyPos = object.find(needle);
    if (keyPos == std::string::npos) {
        throw std::runtime_error("Missing key: " + key);
    }
    auto colonPos = object.find(':', keyPos + needle.size());
    auto valueStart = object.find_first_not_of(" \t\n\r", colonPos + 1);
    auto valueEnd = valueStart;
    if (object[valueStart] == '"') {
        valueStart += 1;
        valueEnd = object.find('"', valueStart);
    } else {
        valueEnd = object.find_first_of(",}", valueStart);
    }
    return object.substr(valueStart, valueEnd - valueStart);
}

std::vector<RunConfig> LoadConfigs(const std::string &path) {
    auto content = ReadFile(path);
    std::vector<RunConfig> configs;
    std::size_t pos = 0;
    while (true) {
        auto start = content.find('{', pos);
        if (start == std::string::npos) {
            break;
        }
        auto end = content.find('}', start);
        if (end == std::string::npos) {
            throw std::runtime_error("Malformed JSON block");
        }
        auto block = content.substr(start, end - start + 1);
        RunConfig cfg;
        cfg.label = ExtractRaw(block, "label");
        cfg.entries = std::stoi(ExtractRaw(block, "entries"));
        cfg.mean = std::stod(ExtractRaw(block, "mean"));
        cfg.sigma = std::stod(ExtractRaw(block, "sigma"));
        cfg.background = std::stod(ExtractRaw(block, "background"));
        configs.push_back(cfg);
        pos = end + 1;
    }
    return configs;
}

void run_all(const char *configPath = "config.json") {
    // Makroyu derleme kipinde yükleyerek büyük hacimli çalıştırmalarda performans kazanıyoruz.
    gROOT->ProcessLine(".L spectrumMacro.C+");

    auto configs = LoadConfigs(configPath);
    if (configs.empty()) {
        std::cerr << "No configurations found in " << configPath << "\n";
        return;
    }

    // Tüm çıktıların tek bir dizine düşmesi dosya yönetimini kolaylaştırıyor.
    gSystem->mkdir("output", true);

    std::cout << "Running " << configs.size() << " configurations\n";
    for (const auto &cfg : configs) {
        std::cout << "-> " << cfg.label << ": entries=" << cfg.entries << " mean=" << cfg.mean << " sigma="
                  << cfg.sigma << " background=" << cfg.background << "\n";
        auto canvas = std::unique_ptr<TCanvas>(
            spectrumMacro(cfg.entries, cfg.mean, cfg.sigma, cfg.background, cfg.label.c_str(), "output"));
        if (canvas) {
            // Tuvali dosyaya yazmak daha sonra uyum sonuçlarını topluca incelemeye izin verir.
            canvas->Write();
        }
    }

    std::cout << "Done. Check the output/ directory for artefacts." << std::endl;
}
