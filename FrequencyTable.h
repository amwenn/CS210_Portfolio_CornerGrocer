//Ambren Cavazos
#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

#include <map>
#include <string>
#include <vector>

class FrequencyTable {
public:
    // Build the table from an input file (one item name per line).
    // Returns true on success.
    bool LoadFromFile(const std::string& inputPath);

    // Write backup file "word count" pairs (e.g., Apples 12)
    // Returns true on success.
    bool WriteBackup(const std::string& backupPath) const;

    // Get frequency of a single item (case-insensitive match).
    int GetCount(const std::string& item) const;

    // Get all (item, count) pairs for printing lists/histograms.
    std::vector<std::pair<std::string, int>> GetAll() const;

private:
    // Store canonical names (lowercased keys) => counts.
    std::map<std::string, int> counts_;

    // Keep original-casing display names for nicer output (first seen wins).
    std::map<std::string, std::string> displayNameByKey_;

    static std::string ToLower(std::string s);
    static std::string Trim(const std::string& s);

    // Convert user/item to canonical key (lowercase trimmed).
    static std::string Canonicalize(const std::string& s);
};

#endif // FREQUENCY_TABLE_H
