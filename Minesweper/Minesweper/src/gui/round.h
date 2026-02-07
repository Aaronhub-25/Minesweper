#ifndef GRID_PRINTER_H
#define GRID_PRINTER_H

#include "../game_logic/game.h"


// Interaktive Grid-Anzeige mit Hover-Funktionalität
// Gibt die ausgewählte Position zurück (x, y) oder (-1, -1) bei ESC/q
// Kann Felder mit 'f' markieren/entmarkieren und 'r' aufdecken
std::vector<int> hover_grid(game& g, int start_offset_y = 0, std::chrono::steady_clock::time_point t_0 = std::chrono::steady_clock::now());

#endif // GRID_PRINTER_H
