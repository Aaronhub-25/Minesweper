#include "grid_printer.h"
#include "../terminal/input.h"
#include <ncurses.h>
#include <string>
#include <vector>

std::vector<int> hover_grid(game& g, int start_offset_y) {
    int width = g.get_width();
    int height = g.get_height();
    const auto& grid = g.get_grid();  // Const reference for reading
    
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
                int field_id = y * width + x;
                const feld& current_field = grid[field_id];
                
                // Wenn dies das aktuelle Feld ist, hebe es hervor
                if (x == cursor_x && y == cursor_y) {
                    attron(A_REVERSE);  // Hervorhebung
                }
                
                // Zeige Feld-Status basierend auf marked und reveald
                if (current_field.is_marked()) {
                    mvprintw(field_start_y + y, grid_start_x + 3 + x * 4, " ! ");  // Flag
                } else if (current_field.is_reveald()) {
                    if (current_field.is_mine()) {
                        mvprintw(field_start_y + y, grid_start_x + 3 + x * 4, " * ");  // Mine
                    } else {
                        int mines_around = current_field.get_mines_arround();
                        if (mines_around == 0) {
                            mvprintw(field_start_y + y, grid_start_x + 3 + x * 4, " . ");  // Leer
                        } else {
                            mvprintw(field_start_y + y, grid_start_x + 3 + x * 4, " %d ", mines_around);  // Zahl der benachbarten Minen
                        }
                    }
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
        mvprintw(bottom_y + 4, grid_start_x, "Open fields: %d", g.get_openfields());
        
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
                {
                    int field_id = cursor_y * width + cursor_x;
                    g.get_grid(field_id).reveal(g);
                    // Prüfe ob Spiel beendet wurde
                    if (!g.get_game_state()) {
                        return {-2, -2};  // Spezieller Code für Game Over (Mine aufgedeckt)
                    }
                    if (g.get_openfields() == 0) {
                        return {-3, -3};  // Spezieller Code für Win (alle Felder aufgedeckt)
                    }
                }
                break;
            case 'f':
            case 'F':
                {
                    // Markiere/entmarkiere das aktuelle Feld
                    int field_id = cursor_y * width + cursor_x;
                    g.get_grid(field_id).mark();
                }
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
