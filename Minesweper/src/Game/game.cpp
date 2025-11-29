// Jedes Spiel 
#include "game.h"
#include <fstream>
#include <iomanip>

// Konstruktor - initialisiert mit Standardwerten
game::game() : width(0), height(0), mine_count(0), difficulty("Beginner") {
}

void game::Enter_difficulty(const std::string& input) {
    difficulty = input;
}

void game::build_game() {
    // Setze Spielfeldgröße und Minenanzahl basierend auf Schwierigkeit
    if (difficulty == "Beginner") {
        width = 8;
        height = 8;
        mine_count = 10;
    }
    else if (difficulty == "Advanced") {
        width = 16;
        height = 16;
        mine_count = 40;
    }
    else if (difficulty == "Professional") {
        width = 30;
        height = 16;
        mine_count = 99;
    }
    else {
        // Default: Beginner
        width = 8;
        height = 8;
        mine_count = 10;
    }
    
    // Erstelle Grid mit Feldern
    grid.clear();
    grid.resize(height);
    for (int y = 0; y < height; y++) {
        grid[y].resize(width);
        for (int x = 0; x < width; x++) {
            grid[y][x] = feld({x, y});
        }
    }
}

void game::write_grid_to_file(const std::string& filename) const {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        return;
    }
    
    // Schreibe Grid
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const feld& current_field = grid[y][x];
            file << "(" << std::setw(2) << current_field.id[0] 
                 << "," << std::setw(2) << current_field.id[1] << ")";
            if (x < width - 1) {
                file << " ";
            }
        }
        file << "\n";
    }
    
    file.close();
}

