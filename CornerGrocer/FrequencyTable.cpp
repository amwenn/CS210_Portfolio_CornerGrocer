//Ambren Cavazos
#include "FrequencyTable.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

std::string FrequencyTable::ToLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}

std::string FrequencyTable::Trim(const std::string& s) {
    const auto first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    const auto last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, last - first + 1);
}

std::string FrequencyTable::Canonicalize(const std::string& s) {
    return ToLower(Trim(s));
}

bool FrequencyTable::LoadFromFile(const std::string& inputPath) {
    counts_.clear();
    displayNameByKey_.clear();

    std::ifstream in(inputPath);
    if (!in.is_open()) {
        return false;
    }

    // Each line should be a single item purchased (e.g., "Apples")
    // We read WHOLE LINES so multi-word items still work.
    std::string line;
    while (std::getline(in, line)) {
        const std::string trimmed = Trim(line);
        if (trimmed.empty()) continue;

        const std::string key = Canonicalize(trimmed);
        ++counts_[key];

        // Store a nice display name for this key if we haven't yet.
        if (displayNameByKey_.find(key) == displayNameByKey_.end()) {
            displayNameByKey_[key] = trimmed;
        }
    }

    return true;
}

bool FrequencyTable::WriteBackup(const std::string& backupPath) const {
    std::ofstream out(backupPath);
    if (!out.is_open()) {
        return false;
    }
    for (const auto& kv : counts_) {
        const std::string& key = kv.first;
        int count = kv.second;

        // Use the preserved original casing if we have it.
        auto itDisp = displayNameByKey_.find(key);
        const std::string nameForPrint = (itDisp != displayNameByKey_.end())
            ? itDisp->second
            : key;

        out << nameForPrint << " " << count << "\n";
    }
    return true;
}

int FrequencyTable::GetCount(const std::string& item) const {
    const std::string key = Canonicalize(item);
    auto it = counts_.find(key);
    if (it == counts_.end()) return 0;
    return it->second;
}

std::vector<std::pair<std::string, int>> FrequencyTable::GetAll() const {
    std::vector<std::pair<std::string, int>> result;
    result.reserve(counts_.size());
    for (const auto& kv : counts_) {
        const std::string& key = kv.first;
        const int count = kv.second;

        auto itDisp = displayNameByKey_.find(key);
        const std::string nameForPrint = (itDisp != displayNameByKey_.end())
            ? itDisp->second
            : key;

        result.emplace_back(nameForPrint, count);
    }

    // Optional: sort by name ascending (case-insensitive already preserved in mapping)
    std::sort(result.begin(), result.end(),
        [](const auto& a, const auto& b) { return a.first < b.first; });

    return result;
}
