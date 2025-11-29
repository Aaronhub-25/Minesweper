// Jedes Feld erhält eine public id mit 3 private Zuständen

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
        if (ismine) {
            g.game_state = 0; // Game over
        }
        // hier noch zahl der nachbar mines 
    }
}

