#include <string>
#include "gui/input.h"
#include "gui/end_page.h"
#include "gui/round.h"
#include "gui/enter_user_name.h"
#include "gui/start_page.h"
#include "gui/coustum_difficulty.h"
#include "game_logic/game.h"
#include "gui/scoreboard_managment.h"
#include <ncurses.h>
#include <chrono>
#include <vector>




int main() {
    init_input();
    // Get difficulty from user
    std::string difficulty = Start_page();
    std::string user_name = enter_user_name();

    //Zeit messen
    double finish_time = 0.0; 

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
        std::chrono::steady_clock::time_point t_0 = std::chrono::steady_clock::now(); // Startzeit des Spiels 


        while (true) {  // Schleife wird über Return-Codes von hover_grid gesteuert
            // Start hover mode and check for game end conditions
            std::vector<int> selected = hover_grid(minesweeper, info_y + 6, t_0); // Start hover mode and get selected field ID

            // Check if the game has ended 
            if (selected.size() >= 2) {
            //Zeitspeichern
            finish_time = std::chrono::duration<double>(std::chrono::steady_clock::now() - t_0).count();
                if (selected == std::vector<int>{-2, -2}) {
                    // Lsot
                    end_result = "Lost";
                    break;
                } else if (selected == std::vector<int>{-3, -3}) {
                    // Win 
                    end_result = "Won";
                    save_high_score(user_name, finish_time);
                    break;
                } else if (selected == std::vector<int>{-1, -1}) {
                    // Exit Game
                    end_result = "Exited Game";
                    break;
                }
            }
            clear();
        }
        std::string result = End_page(end_result, user_name, finish_time, load_high_score() );
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