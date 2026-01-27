#include <string>
#include "terminal/input.h"
#include "terminal/end_page.h"
#include "terminal/grid_printer.h"
#include "terminal/start_page.h"
#include "Game/game.h"
#include <ncurses.h>



int main() {
    // Get difficulty from user
    std::string difficulty = Start_page();
    
    while (true){
        // Construkt minesweper spiel
        game minesweeper;
        minesweeper.build_game(difficulty);
        minesweeper.generate_plane();

    
        // Display selected difficulty and game parameters
        init_input();
        clear();
    
        int info_y = 0;
        clear();
        mvprintw(info_y + 4, 0, "Navigate with arrow keys, f: mark/unmark, r: reveal, ESC/q: quit");

        bool game_finished = false;
        while (!game_finished) {  // Schleife wird über Return-Codes von hover_grid gesteuert
            // Start hover mode and check for game end conditions
            std::vector<int> selected = hover_grid(minesweeper, info_y + 6);

            // Check if the game has ended 
            if (selected.size() >= 2) {
                if (selected == std::vector<int>{-2, -2}) {
                    // Lsot
                    game_finished = true;
                } else if (selected == std::vector<int>{-3, -3}) {
                    // Win 
                    game_finished = true;
                }
            }
            clear();
        }
        std::string result = End_page(minesweeper.get_game_state());
        if (result == "Play again") {
            continue;
        }
        else if (result == "Change Difficulty") {
            difficulty = Start_page();
            continue;
        }
        else if (result == "Exit") {
            break;
        }
    }
    cleanup_input();
    return 0;
}