#include "banner.h"
#include <fstream>
#include <string>
#include <ncurses.h>

int PrintBanner(const std::string& filepath, int start_y) {
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
    int current_line = start_y;
    
    for (const auto& path : paths) {
        file.open(path);
        if (file.is_open()) {
            opened = true;
            std::string line;
            while (std::getline(file, line)) {
                mvprintw(current_line, 0, "%s", line.c_str());
                current_line++;
            }
            file.close();
            break;
        }
        file.close();
    }
    
    if (!opened) {
        mvprintw(start_y, 0, "Failed to open banner file");
        return start_y + 1;
    }
    
    return current_line;  // Gibt die nächste freie Zeile zurück
}

