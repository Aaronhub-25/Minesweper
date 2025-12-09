#include "feld.h"
#include "game.h"

int feld::get_id_x(const game& g) const {
    return id % g.get_width();
}

int feld::get_id_y(const game& g) const {
    return id / g.get_width();
}

void feld::mark() {
    // Toggle marked status; don't mark if already revealed
    if (!is_reveald()) {
        set_marked(!is_marked());
    }
}

void feld::reveal(game& g) {
    // Reveal only if not already revealed
    if (!is_reveald()) {
        set_reveald(true);
        g.decrement_openfields();
        // Unmark field if it was marked, since it is now revealed
        if (is_marked()) {
            set_marked(false);
        }
        if (is_mine()) {
            g.set_game_state(false); // Game over
            return; // Stop here if mine was revealed
        }
        
        // Wenn das Feld keine benachbarten Minen hat, decke automatisch alle Nachbarn auf
        if (get_mines_arround() == 0) {
            g.reveal_open_adjacent_fields(id);
        }
    }
}

void feld::count_mines_arround(game& g) {
    int mines_arround = 0;
    int current_y = get_id_y(g);
    int current_x = get_id_x(g);
    int width = g.get_width();
    
    // Zähle nur Nachbarn, nicht das aktuelle Feld selbst
    for (int y = current_y - 1; y <= current_y + 1; y++) {
        for (int x = current_x - 1; x <= current_x + 1; x++) {
            // Überspringe das aktuelle Feld
            if (y == current_y && x == current_x) {
                continue;
            }
            if (y >= 0 && y < g.get_height() && x >= 0 && x < width) {
                int neighbor_id = y * width + x;
                if (g.get_grid(neighbor_id).is_mine()) {
                    mines_arround++;
                }
            }
        }
    }
    set_mines_arround(mines_arround);
}
