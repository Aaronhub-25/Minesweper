// Jedes Spiel 
#include "game.h"
#include <cstdlib>
#include <ctime>
#include <random>

// Konstruktor - initialisiert mit Standardwerten
game::game() : width(0), height(0), mine_count(0), number_of_fields(0), difficulty("Beginner"), openfields(0), game_state(true) {
    mines_ids.clear(); // Stelle sicher, dass mines_ids leer ist
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
        set_openfields(number_of_fields - mine_count);
    }
    else if (difficulty == "Advanced") {
        width = 16;
        height = 16;
        number_of_fields = width * height;
        mine_count = 40;
        set_openfields(number_of_fields - mine_count);
    }
    else if (difficulty == "Professional") {
        width = 30;
        height = 16;
        number_of_fields = width * height;
        mine_count = 99;    
        set_openfields(number_of_fields - mine_count);
    }
    else {
        // Default: Beginner
        width = 8;
        height = 8;
        number_of_fields = width * height;
        mine_count = 10;
        set_openfields(number_of_fields - mine_count);
    }
    // build_game() setzt nur die Parameter, das Grid wird von generate_plane() erstellt
}

void game::generate_plane() {
    // Erstelle Grid mit Feldern - stelle sicher, dass alle Felder zurückgesetzt sind
    grid.clear();
    mines_ids.clear(); // Leere die Liste der Minen-IDs
    grid.resize(number_of_fields);
    for (int id = 0; id < number_of_fields; id++) {
        grid[id] = feld(id); // Erstelle neues Feld mit mine=false (Standard)
    }
}

void game::place_mines(int first_guess_id) {
    // Validierung: Prüfe ob Grid richtig initialisiert ist
    if (grid.size() != number_of_fields || number_of_fields == 0) {
        return; // Grid nicht richtig initialisiert
    }
    
    // Validierung: Prüfe ob mine_count gesetzt ist
    if (mine_count == 0 || mine_count >= number_of_fields) {
        return; // Ungültige mine_count
    }
    
    // Validierung: Prüfe ob first_guess_id gültig ist
    if (first_guess_id < 0 || first_guess_id >= number_of_fields) {
        return; // Ungültige first_guess_id
    }
    
    // Stelle sicher, dass alle Minen zurückgesetzt sind (für neues Spiel)
    for (int id = 0; id < number_of_fields; id++) {
        grid[id].set_mine(false);
    }
    mines_ids.clear(); // Leere die Liste der Minen-IDs
    
    std::vector<int> available_ids;
    available_ids.reserve(number_of_fields - 1);
    // Add all IDs except first_guess_id
    for (int id = 0; id < number_of_fields; id++) {
        if (id != first_guess_id) {
            available_ids.push_back(id);
        }
    }
    
    // Validierung: Stelle sicher, dass genug Felder verfügbar sind
    if (available_ids.size() < mine_count) {
        return; // Nicht genug verfügbare Felder
    }
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(available_ids.begin(), available_ids.end(), g);
    
    // Place mines on first mine_count fields
    mines_ids.reserve(mine_count); // Reserve space for mine IDs
    for (int i = 0; i < mine_count; i++) {
        int mine_id = available_ids[i];
        grid[mine_id].set_mine(true);
        mines_ids.push_back(mine_id); // Speichere die ID der Mine
    }
    
    // Nach dem Platzieren der Minen: Berechne für jedes Feld die Anzahl der benachbarten Minen
    for (int id = 0; id < number_of_fields; id++) {
        grid[id].count_mines_arround(*this);
    }
}
