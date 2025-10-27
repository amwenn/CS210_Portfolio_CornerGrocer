//Ambren Cavazos

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "FrequencyTable.h"

static void PrintMenu() {
    std::cout << "\n==== Corner Grocer: Item Tracking ====\n";
    std::cout << "1 - Search item frequency\n";
    std::cout << "2 - Print all item frequencies\n";
    std::cout << "3 - Print histogram\n";
    std::cout << "4 - Exit\n";
    std::cout << "Choose an option: ";
}

// Safe integer input (1–4). Keeps prompting until valid.
static int ReadMenuChoice() {
    int choice;
    while (true) {
        if (std::cin >> choice && choice >= 1 && choice <= 4) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        std::cout << "Invalid choice. Enter 1, 2, 3, or 4: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Read a full line (for item names with spaces); trims nothing here—FrequencyTable handles it.
static std::string ReadLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

static void HandleSearch(const FrequencyTable& ft) {
    const std::string item = ReadLine("Enter item to search: ");
    const int count = ft.GetCount(item);
    std::cout << item << " " << count << "\n";
}

static void HandlePrintAll(const FrequencyTable& ft) {
    const auto all = ft.GetAll();
    for (const auto& p : all) {
        std::cout << p.first << " " << p.second << "\n";
    }
}

static void HandleHistogram(const FrequencyTable& ft) {
    const auto all = ft.GetAll();
    for (const auto& p : all) {
        std::cout << p.first << " ";
        for (int i = 0; i < p.second; ++i) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
}

int main() {
    // You can replace this with an absolute/relative path if needed:
    const std::string kInputFile = "CS210_Project_Three_Input_File.txt";
    const std::string kBackup = "frequency.dat";

    FrequencyTable ft;

    // Load purchases from the input file at startup.
    if (!ft.LoadFromFile(kInputFile)) {
        std::cerr << "ERROR: Could not open input file: " << kInputFile << "\n";
        std::cerr << "Make sure it is next to the executable or update the path.\n";
        return 1;
    }

    // Immediately write backup (no user action required).
    if (!ft.WriteBackup(kBackup)) {
        std::cerr << "WARNING: Could not write backup file: " << kBackup << "\n";
        // Continue running program—backup failure shouldn’t block the menu.
    }

    // Main menu loop.
    while (true) {
        PrintMenu();
        const int choice = ReadMenuChoice();

        switch (choice) {
        case 1:
            HandleSearch(ft);
            break;
        case 2:
            HandlePrintAll(ft);
            break;
        case 3:
            HandleHistogram(ft);
            break;
        case 4:
            std::cout << "Goodbye!\n";
            return 0;
        default:
            // Should never happen due to input validation.
            break;
        }
    }
}
