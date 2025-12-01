#ifndef GRID_PRINTER_H
#define GRID_PRINTER_H

#include "../Game/game.h"
#include <string>

// Interaktive Grid-Anzeige mit Hover-Funktionalität
// Gibt die ausgewählte Position zurück (x, y) oder (-1, -1) bei ESC/q
// Kann Felder mit 'f' markieren/entmarkieren und 'r' aufdecken
std::vector<int> hover_grid(game& g, int start_offset_y = 0);

#endif // GRID_PRINTER_H
