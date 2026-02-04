#include <string>
#include "terminal/input.h"
#include "terminal/end_page.h"
#include "terminal/round.h"
#include "terminal/start_page.h"
#include "terminal/coustum_difficulty.h"
#include "Game/game.h"
#include <ncurses.h>



int main() {
    // Get difficulty from user
    std::string difficulty = Start_page();
    
    while (true){
        game minesweeper;

        // Check if custom difficulty was selected
        if (difficulty == "Coustom") {
            CustomSettings custom = ask_coustum_settings();
            minesweeper.build_game_coustom(custom);
        }
        else if (difficulty == "Beginner" || difficulty == "Advanced" || difficulty == "Professional") {
            //
            minesweeper.build_game(difficulty);
        
        }
        minesweeper.generate_plane();

    
        // Display selected difficulty and game parameters
        init_input();
        clear();
    
        int info_y = 0;
        clear();
        mvprintw(info_y + 4, 0, "Navigate with arrow keys, f: mark/unmark, r: reveal, ESC/q: quit");


        std::string end_result;
        while (true) {  // Schleife wird über Return-Codes von hover_grid gesteuert
            // Start hover mode and check for game end conditions
            std::vector<int> selected = hover_grid(minesweeper, info_y + 6);

            // Check if the game has ended 
            if (selected.size() >= 2) {
                if (selected == std::vector<int>{-2, -2}) {
                    // Lsot
                    end_result = "Lost";
                    break;
                } else if (selected == std::vector<int>{-3, -3}) {
                    // Win 
                    end_result = "Won";
                    break;
                } else if (selected == std::vector<int>{-1, -1}) {
                    // Exit Game
                    end_result = "Exited Game";
                    break;
                }
            }
            clear();
        }
        std::string result = End_page(end_result);
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