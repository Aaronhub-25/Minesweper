#include "coustum_difficulty.h"
#include "input.h"
#include <ncurses.h>

// Funktion zum Erfragen der Custom-Einstellungen
CustomSettings ask_coustum_settings() {

    CustomSettings settings = {10, 10, 10};
    int selected = 0;  // 0 = width, 1 = height, 2 = mines
    int key;
    
    const char* labels[] = {"Width", "Height", "Mines"};
    int min_values[] = {5, 5, 1};
    int max_values[] = {50, 50, 200000}; // Minen maximal 1 weniger als Felder

    while (true) {
        clear();
        
        // Title
        mvprintw(2, 0, "Custom Difficulty Settings");
        mvprintw(3, 0, "============================");
        
        // Display width
        if (selected == 0) attron(A_REVERSE);
        mvprintw(5, 2, "Width:  %d", settings.width);
        if (selected == 0) attroff(A_REVERSE);
        
        // Display height
        if (selected == 1) attron(A_REVERSE);
        mvprintw(6, 2, "Height: %d", settings.height);
        if (selected == 1) attroff(A_REVERSE);
        
        // Display mines
        if (selected == 2) attron(A_REVERSE);
        mvprintw(7, 2, "Mines:  %d", settings.mines);
        if (selected == 2) attroff(A_REVERSE);
        
        mvprintw(9, 0, "UP/DOWN: Navigate | LEFT/RIGHT: Adjust | ENTER: Confirm");
        refresh();
        
        key = get_key();
        
        switch (key) {
            case KEY_UP:
                selected = (selected - 1 + 3) % 3;
                break;
            case KEY_DOWN:
                selected = (selected + 1) % 3;
                break;
            case KEY_LEFT:
                if (selected == 0) {
                    if (settings.width > min_values[0])
                        settings.width -= 1;
                } else if (selected == 1) {
                    if (settings.height > min_values[1])
                        settings.height -= 1;
                } else if (selected == 2) {
                    if (settings.mines > min_values[2])
                        settings.mines -= 1;
                }
                break;
            case KEY_RIGHT:
                if (selected == 0) {
                    if (settings.width < max_values[0])
                        settings.width += 1;
                } else if (selected == 1) {
                    if (settings.height < max_values[1])
                        settings.height += 1;
                } else if (selected == 2) {
                    if (settings.mines < settings.width * settings.height - 1) // Max mines = total fields - 1
                        settings.mines += 1;
                }
                break;
            case '\n':  // Enter key
            case KEY_ENTER:
            case 13:
                return settings;
            case 'q':
            case 'Q':
            case 27:  // ESC
                return settings;  // Return current settings
        }
    }
}
