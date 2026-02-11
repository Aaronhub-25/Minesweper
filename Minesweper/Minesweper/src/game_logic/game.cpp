// Jedes Spiel 
#include "game.h"
#include "../gui/coustum_difficulty.h"
#include <random>
#include <algorithm>



// Konstruktor - initialisiert mit Standardwerten
game::game() : width(0), height(0), mine_count(0), number_of_fields(0), difficulty("Beginner"), openfields(0), first_guess_id(-1), game_state(true), first_guess_done(false) {
    grid.clear(); // Stelle sicher, dass grid leer ist
    mines_ids.clear(); // Stelle sicher, dass mines_ids leer ist
    available_ids.clear(); // Stelle sicher, dass available_ids leer ist
    fields_to_reveal.clear(); // Stelle sicher, dass fields_to_reveal leer ist
}



// Setze Spielfeldgröße und Minenanzahl basierend auf Schwierigkeit
void game::build_game(const std::string& difficulty) {
    set_difficulty(difficulty);
    
    if (difficulty == "Beginner") {
        set_width(8);
        set_height(8);
        set_number_of_fields(get_width() * get_height());
        set_mine_count(7);
        set_openfields(get_number_of_fields() - get_mine_count());
    }
    else if (get_difficulty() == "Advanced") {
        set_width(16);
        set_height(16);
        set_number_of_fields(get_width() * get_height());
        set_mine_count(40);
        set_openfields(get_number_of_fields() - get_mine_count());
    }
    else if (get_difficulty() == "Professional") {
        set_width(30);
        set_height(16);
        set_number_of_fields(get_width() * get_height());
        set_mine_count(99);    
        set_openfields(get_number_of_fields() - get_mine_count());
    }
    else {
        // Default: Beginner
        set_width(8);
        set_height(8);
        set_number_of_fields(get_width() * get_height());
        set_mine_count(10);
        set_openfields(get_number_of_fields() - get_mine_count());
    }
    // build_game() setzt nur die Parameter, das Grid wird von generate_plane() erstellt
}

void game::build_game_coustom(const CustomSettings& settings) {
    set_width(settings.width);
    set_height(settings.height);
    set_number_of_fields(get_width() * get_height());
    set_mine_count(settings.mines);
    set_openfields(get_number_of_fields() - get_mine_count());
    // build_game() setzt nur die Parameter, das Grid wird von generate_plane() erstellt
}   

void game::generate_plane() {
    // Erstelle Grid mit Feldern - stelle sicher, dass alle Felder zurückgesetzt sind
    grid.clear();
    mines_ids.clear(); // Leere die Liste der Minen-IDs
    available_ids.clear(); // Leere die Liste der verfügbaren IDs
    grid.resize(number_of_fields);
    // Erstelle alle Felder und füge ihre IDs zur Liste hinzu
    for (int id = 0; id < number_of_fields; id++) {
        grid[id] = feld(id); // Erstelle neues Feld mit mine=false (Standard)
        available_ids.push_back(id); // Füge ID zur Liste hinzu
    }
}

void game::place_mines(int first_guess_id) {
    
    // Validierung: Prüfe ob mine_count gesetzt ist
    if (mine_count == 0 || mine_count >= number_of_fields) {
        return; // Ungültige mine_count
    }
    
    // Validierung: Prüfe ob first_guess_id gültig ist
    if (first_guess_id < 0 || first_guess_id >= number_of_fields) {
        return; // Ungültige first_guess_id
    }

    // WICHTIG: Setze alle Minen und mines_arround zurück, bevor neue platziert werden
    // Dies verhindert, dass alte Minen-Status bestehen bleiben
    for (int id = 0; id < number_of_fields; id++) {
        grid[id].set_mine(false);
        grid[id].set_mines_arround(0);
    }
    
    mines_ids.clear(); // Leere die Liste der Minen-IDs
    
    // Erstelle Kopie der verfügbaren IDs (die bereits in generate_plane() erstellt wurden)
    std::vector<int> available_ids_copy = available_ids;
    // Remove first_guess_id from the list
    available_ids_copy.erase(std::remove(available_ids_copy.begin(), available_ids_copy.end(), first_guess_id), available_ids_copy.end());
    
    // Validierung: Stelle sicher, dass genug Felder verfügbar sind
    if (available_ids_copy.size() < mine_count) {
        return; // Nicht genug verfügbare Felder
    }
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(available_ids_copy.begin(), available_ids_copy.end(), g);
    
    // Place mines on first mine_count fields
    mines_ids.reserve(mine_count); // Reserve space for mine IDs
    for (int i = 0; i < mine_count; i++) {
        int mine_id = available_ids_copy[i];
        grid[mine_id].set_mine(true);
        mines_ids.push_back(mine_id); // Speichere die ID der Mine
    }
    
    // Nach dem Platzieren der Minen: Berechne für jedes Feld die Anzahl der benachbarten Minen
    for (int id = 0; id < number_of_fields; id++) {
        grid[id].count_mines_arround(*this);
    }
}

void game::add_fields_to_reveal_if_0_mines_arround(int id) {
    // Add fields to reveal if 0 mines around
    // This implements the standard Minesweeper behavior: empty fields automatically reveal neighbors
    
    // Prüfe ob Feld gültig ist
    if (id < 0 || id >= number_of_fields) {
        return;
    }
    
    feld& current_field = grid[id];
    
    // WICHTIG: Nur aufdecken wenn Feld bereits aufgedeckt ist und keine benachbarten Minen hat
    // Dies verhindert Endlosschleifen und das Aufdecken von Minen
    if (!current_field.is_reveald()) {
        return;
    }
    
    int current_y = current_field.get_id_y(*this);
    int current_x = current_field.get_id_x(*this);
    int width = get_width();

    // Add alle benachbarten Felder zur Reveal-Liste rekursiv
    for (int y = current_y - 1; y <= current_y + 1; y++) {
        for (int x = current_x - 1; x <= current_x + 1; x++) {
            // Überspringe das aktuelle Feld
            if (y == current_y && x == current_x) {
                continue;
            }
            // Prüfe Grenzen
            if (y >= 0 && y < get_height() && x >= 0 && x < width) {
                int neighbor_id = y * width + x;
                feld& neighbor = grid[neighbor_id];
                
                // Add fields to reveal if not already revealed, not marked, and not a mine
                if (!neighbor.is_reveald() && !neighbor.is_marked() && !neighbor.is_mine()) {
                    // Prüfe ob Feld bereits in der Liste ist (vermeide Duplikate)
                    bool already_in_list = false;
                    for (int existing_id : fields_to_reveal) {
                        if (existing_id == neighbor_id) {
                            already_in_list = true;
                            break;
                        }
                    }
                    if (!already_in_list) {
                        add_field_to_reveal(neighbor_id);
                        // Wenn das Nachbarfeld auch 0 Minen hat, füge dessen Nachbarn rekursiv hinzu
                        if (neighbor.get_mines_arround() == 0) {
                            add_fields_to_reveal_if_0_mines_arround(neighbor_id);
                        }
                    }
                }
            }
        }
    }
}

void game::reveal_open_adjacent_fields(int id) {
    // Reveal a single field (used for delayed reveal from fields_to_reveal list)
    if (id < 0 || id >= number_of_fields) {
        return;
    }
    
    feld& field = grid[id];
    if (!field.is_reveald() && !field.is_marked()) {
        field.reveal(*this);
        // Wenn das Feld 0 Minen hat, füge Nachbarn zur Reveal-Liste hinzu
        if (field.get_mines_arround() == 0) {
            add_fields_to_reveal_if_0_mines_arround(id);
        }
    }
}

void game::remove_field_to_reveal(int id) {
    // Remove field from reveal list
    fields_to_reveal.erase(
        std::remove(fields_to_reveal.begin(), fields_to_reveal.end(), id),
        fields_to_reveal.end()
    );
}
