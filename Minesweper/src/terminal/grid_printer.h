#ifndef GRID_PRINTER_H
#define GRID_PRINTER_H

#include "../Game/game.h"
#include <string>

// Gibt das Grid in einem schönen, spielbaren Format aus
void print_grid(const game& g);

// Liest grid.txt und gibt es aus (falls benötigt)
void print_grid_from_file(const std::string& filename);

// Interaktive Grid-Anzeige mit Hover-Funktionalität
// Gibt die ausgewählte Position zurück (x, y) oder (-1, -1) bei ESC/q
// Kann Felder mit 'f' markieren/entmarkieren
std::vector<int> hover_grid(game& g, int start_offset_y = 0);

#endif // GRID_PRINTER_H
