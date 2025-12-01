#include <iostream>
#include <string>
#include "terminal/input.h"
#include "terminal/grid_printer.h"
#include "Game/game.h"
#include <ncurses.h>

std::string Enter_difficulty() {
    init_input();
    
    const int NUM_OPTIONS = 3;
    const char* options[] = {
        "Beginner",
        "Advanced",
        "Professional"
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
                cleanup_input();
                return std::string(options[selected]);
            case 'q':
            case 'Q':
            case 27:    // ESC key
                cleanup_input();
                return "Beginner";  // Default
        }
    }
}

int main() {
    // Get difficulty from user
    std::string difficulty = Enter_difficulty();
    
    // Create game instance and set difficulty
    game minesweeper;
    minesweeper.Enter_difficulty(difficulty);
    
    // Build game field based on difficulty
    minesweeper.build_game();
    minesweeper.generate_plane();
    minesweeper.place_mines();
    
    // Display selected difficulty and game parameters
    init_input();
    clear();
    
    int info_y = 0;
    // Print grid in nice format with hover functionality
    mvprintw(info_y + 4, 0, "Navigate with arrow keys, ENTER to select, ESC/q to quit");
    while (minesweeper.game_state == 1 or minesweeper.openfields > 0){
        // Start hover mode
        std::vector<int> selected = hover_grid(minesweeper, info_y + 6);
        
        clear();
        
        // Prüfe ob Spiel beendet wurde
        if (selected[0] == -2 && selected[1] == -2) {
            // Game Over - Mine wurde aufgedeckt
            mvprintw(10, 0, "GAME OVER! You hit a mine!");
            mvprintw(11, 0, "Press any key to exit...");
            refresh();
            get_key();
            cleanup_input();
            break;
        } else if (selected[0] >= 0 && selected[1] >= 0) {
            mvprintw(10, 0, "Selected position: (%d, %d)", selected[0], selected[1]);
            refresh();
            get_key();
        } else {
            mvprintw(10, 0, "Selection cancelled");
            refresh();
            get_key();
        }
        cleanup_input();
    }
    
    // Prüfe ob Spiel gewonnen wurde
    if (minesweeper.game_state == 1 && minesweeper.openfields == 0) {
        clear();
        mvprintw(10, 0, "CONGRATULATIONS! You won!");
        mvprintw(11, 0, "Press any key to exit...");
        refresh();
        get_key();
        cleanup_input();
    }
    return 0;
}