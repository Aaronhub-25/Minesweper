#include "feld.h"
#include "game.h"
#include <iostream>

void feld::mark() {
    // Toggle marked status; don't mark if already revealed
    if (!reveald) {
        marked = !marked;
    }
}

void feld::reveal(game& g) {
    // Reveal only if not already revealed
    if (!reveald) {
        reveald = true;
        g.openfields--;
        // Unmark field if it was marked, since it is now revealed
        if (marked) {
            marked = false;
        }
        if (ismine) {
            g.game_state = 0; // Game over
        }
        // hier noch zahl der nachbar mines
    }
}

void feld::count_mines_arround(game& g) {
    mines_arround = 0;
    for (int y=0; y<g.get_height(); y++){
        for (int x=0; x<g.get_width(); x++){ 
        const feld& current_field = g.get_grid()[y][x]; 
        // FRage warum hier get function im grid printe nur die Variable !!!!!!
        // male 3x3 Box um jede und checke für alle ob sie eine mine sind
        }
    }
}
