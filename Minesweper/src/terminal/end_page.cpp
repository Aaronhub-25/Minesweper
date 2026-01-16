#include "end_page.h"
#include "input.h"
#include <ncurses.h>
#include <string>


std::string End_page(bool game_won) {
    init_input();
    
    const int NUM_OPTIONS = 3;
    const char* options[] = {
        "Play again",
        "Change Difficulty",
        "Exit"
    };
    
    int selected = 0;
    int key;
    
    while (true) {
        clear();
        
        //Result
        if (game_won == true) {
            mvprintw(5, 0, "You won!");
        }
        else if (game_won == false) {
            mvprintw(5, 0, "You Lost!");
        }

        // Display options
        for (int i = 0; i < NUM_OPTIONS; i++) {
            if (i == selected) {
                attron(A_REVERSE);  // Highlight selected option
                mvprintw(8 + i, 2, "> %s", options[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(8 + i, 2, "  %s", options[i]);
            }
        }
        
        mvprintw(12, 0, "Use UP/DOWN arrows to navigate, ENTER to select");
        refresh();
        
        key = get_key();
        
        switch (key) {
            case KEY_UP:
                selected = (selected - 1 + NUM_OPTIONS) % NUM_OPTIONS;
                break;
            case KEY_DOWN:
                selected = (selected + 1) % NUM_OPTIONS;
                break;
            case '\n':  // Enter key
            case KEY_ENTER:
            case 13:    // Alternative Enter code
                cleanup_input();
                return std::string(options[selected]);
            case 'e':
            case 'E':
            case 27:    // ESC key
                cleanup_input();
                return "Exit";  // Default
        }
    }
}