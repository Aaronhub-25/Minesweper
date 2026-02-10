#include "start_page.h"
#include "input.h"
#include <ncurses.h>
#include <string>


std::string Start_page() {
    
    const int NUM_OPTIONS = 4;
    const char* options[] = {
        "Beginner",
        "Advanced",
        "Professional",
        "Coustom"
    };
    
    int selected = 0;
    int key;
    
    while (true) {
        clear();
        
        // Display title
        mvprintw(5, 0, "Select Difficulty:");
        mvprintw(6, 0, "==================");
        
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
                return std::string(options[selected]);
            case 'q':
            case 'Q':
            case 27:    // ESC key
                return "Beginner";  // Default
        }
    }
}

