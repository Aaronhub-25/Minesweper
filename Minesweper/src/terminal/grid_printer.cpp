#include "grid_printer.h"
#include "../terminal/input.h"
#include <fstream>
#include <iomanip>
#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> hover_grid(game& g, int start_offset_y) {
    int width = g.get_width();
    int height = g.get_height();
    auto& grid = g.get_grid();  // Non-const reference to allow modification
    
    int cursor_x = 0;
    int cursor_y = 0;
    int key;
    
    // Berechne Startposition für das Grid
    int grid_start_y = start_offset_y;
    int grid_start_x = 0;
    
    while (true) {
        clear();
        
        // Header mit x-Koordinaten
        mvprintw(grid_start_y, grid_start_x, "   ");  // Offset für y-Achse
        for (int x = 0; x < width; x++) {
            mvprintw(grid_start_y, grid_start_x + 3 + x * 4, "%2d ", x);
        }
        
        // Zeichne obere Linie
        int line_y = grid_start_y + 1;
        mvprintw(line_y, grid_start_x, "  +");
        for (int x = 0; x < width; x++) {
            mvprintw(line_y, grid_start_x + 3 + x * 4, "---");
        }
        mvprintw(line_y, grid_start_x + 3 + width * 4, "+");
        
        // Zeichne Grid mit Feldern
        int field_start_y = grid_start_y + 2;
        for (int y = 0; y < height; y++) {
            mvprintw(field_start_y + y, grid_start_x, "%2d|", y);
            for (int x = 0; x < width; x++) {
                const feld& current_field = grid[y][x];
                
                // Wenn dies das aktuelle Feld ist, hebe es hervor
                if (x == cursor_x && y == cursor_y) {
                    attron(A_REVERSE);  // Hervorhebung
                }
                
                // Zeige Feld-Status basierend auf marked und reveald
                if (current_field.marked) {
                    mvprintw(field_start_y + y, grid_start_x + 3 + x * 4, " ! ");  // Flag
                } else if (current_field.reveald) {
                    mvprintw(field_start_y + y, grid_start_x + 3 + x * 4, " . ");  // Leer später zahl der grenzen
                } else {
                    mvprintw(field_start_y + y, grid_start_x + 3 + x * 4, " # ");  // Verdeckt
                }
                
                if (x == cursor_x && y == cursor_y) {
                    attroff(A_REVERSE);
                }
            }
            mvprintw(field_start_y + y, grid_start_x + 3 + width * 4, "|");
        }
        
        // Zeichne untere Linie
        int bottom_y = field_start_y + height;
        mvprintw(bottom_y, grid_start_x, "  +");
        for (int x = 0; x < width; x++) {
            mvprintw(bottom_y, grid_start_x + 3 + x * 4, "---");
        }
        mvprintw(bottom_y, grid_start_x + 3 + width * 4, "+");
        
        // Zeige aktuelle Position und Anweisungen
        mvprintw(bottom_y + 2, grid_start_x, "Position: (%d, %d)", cursor_x, cursor_y);
        mvprintw(bottom_y + 3, grid_start_x, "Arrow keys: move | f: mark/unmark | ENTER: select | ESC/q: quit");
        mvprintw(bottom_y + 4, grid_start_x, "Open fields: %d", g.openfields);
        
        refresh();
        
        key = get_key();
        
        switch (key) {
            case KEY_UP:
                cursor_y = (cursor_y - 1 + height) % height;
                break;
            case KEY_DOWN:
                cursor_y = (cursor_y + 1) % height;
                break;
            case KEY_LEFT:
                cursor_x = (cursor_x - 1 + width) % width;
                break;
            case KEY_RIGHT:
                cursor_x = (cursor_x + 1) % width;
                break;
            case 'r':
            case 'R':
                grid[cursor_y][cursor_x].reveal(g);
                // Prüfe ob Spiel beendet wurde (Mine aufgedeckt)
                if (g.game_state == 0 or g.openfields == 0) {
                    return {-2, -2};  // Spezieller Code für Game Over
                }
                break;
            case 'f':
            case 'F':
                // Markiere/entmarkiere das aktuelle Feld
                grid[cursor_y][cursor_x].mark();
                break;
            case '\n':  // Enter key
            case KEY_ENTER:
            case 13:    // Alternative Enter code
                return {cursor_x, cursor_y};
            case 'q':
            case 'Q':
            case 27:    // ESC key
                return {-1, -1};
        }
    }
}
