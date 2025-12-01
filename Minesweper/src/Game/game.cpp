// Jedes Spiel 
#include "game.h"
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// Konstruktor - initialisiert mit Standardwerten
game::game() : width(0), height(0), mine_count(0), difficulty("Beginner") {
}

// Enter difficulty String via ncurses input
void game::Enter_difficulty(const std::string& input) {
    difficulty = input;
}

// Setze Spielfeldgröße und Minenanzahl basierend auf Schwierigkeit
void game::build_game() {
    if (difficulty == "Beginner") {
        width = 8;
        height = 8;
        number_of_fields = width * height;
        mine_count = 10;
        openfields = number_of_fields - mine_count;
    }
    else if (difficulty == "Advanced") {
        width = 16;
        height = 16;
        number_of_fields = width * height;
        mine_count = 40;
        openfields = number_of_fields - mine_count;
    }
    else if (difficulty == "Professional") {
        width = 30;
        height = 16;
        number_of_fields = width * height;
        mine_count = 99;    
        openfields = number_of_fields - mine_count;
    }
    else {
        // Default: Beginner
        width = 8;
        height = 8;
        number_of_fields = width * height;
        mine_count = 10;
        openfields = number_of_fields - mine_count;
    }
    // build_game() setzt nur die Parameter, das Grid wird von generate_plane() erstellt
}

void game::generate_plane() {
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

void game::place_mines() {
    srand(time(nullptr));  // Seed für Zufallszahlen
    int mines_placed = 0;
    mines_ids.clear();
    while (mines_placed < mine_count) {
        int x = rand() % width;
        int y = rand() % height;
        if (!grid[y][x].is_mine()) {
            grid[y][x].set_mine(true);
            mines_placed++;
            mines_ids.push_back(y * width + x);
        }
    }
}
