#include "input.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>

void PrintBanner(const std::string& filepath) {
    // Versuche verschiedene mögliche Pfade (abhängig vom Ausführungsverzeichnis)
    std::string paths[] = {
        filepath,                           // Originaler Pfad
        "../" + filepath,                   // Relativ zum build-Verzeichnis
        "../../" + filepath,                // Falls aus einem Unterverzeichnis
        "src/terminal/Banner.txt",          // Relativ zum Projektroot
        "../src/terminal/Banner.txt"        // Relativ zum build-Verzeichnis
    };
    
    std::ifstream file;
    bool opened = false;
    
    for (const auto& path : paths) {
        file.open(path);
        if (file.is_open()) {
            opened = true;
            std::string line;
            while (std::getline(file, line)) {
                std::cout << line << '\n';
            }
            file.close();
            break;
        }
        file.close();
    }
    
    if (!opened) {
        std::cerr << "Failed to open banner file. Tried paths:" << std::endl;
        for (const auto& path : paths) {
            std::cerr << "  - " << path << std::endl;
        }
    }
}