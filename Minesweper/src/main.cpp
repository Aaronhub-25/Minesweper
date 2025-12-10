#include <string>
#include "terminal/input.h"
#include "terminal/Difficulty_choser.h"
#include "terminal/grid_printer.h"
#include "Game/game.h"
#include <ncurses.h>



int main() {
    // Get difficulty from user
    std::string difficulty = Difficulty_choser();
    
    // Create game instance and build field with difficulty
    game minesweeper;
    minesweeper.build_game(difficulty);
    minesweeper.generate_plane();

    
    // Display selected difficulty and game parameters
    init_input();
    clear();
    
    int info_y = 0;
    clear();
    mvprintw(info_y + 4, 0, "Navigate with arrow keys, f: mark/unmark, r: reveal, ESC/q: quit");
    while (true) {  // Schleife wird über Return-Codes von hover_grid gesteuert
        // Start hover mode
        std::vector<int> selected = hover_grid(minesweeper, info_y + 6);
        
        clear();
        
        // Prüfe ob Spiel beendet wurde
        if (selected[0] == -2 && selected[1] == -2) {
            // Game Over - Mine wurde aufgedeckt
            clear();
            mvprintw(10, 0, "GAME OVER! You hit a mine!");
            mvprintw(11, 0, "Press any key to exit...");
            refresh();
            get_key();
            break;
        } else if (selected[0] == -3 && selected[1] == -3) {
            // Win - Alle Felder aufgedeckt
            clear();
            mvprintw(10, 0, "CONGRATULATIONS! You won!");
            mvprintw(11, 0, "Press any key to exit...");
            refresh();
            get_key();
            break;
        } else if (selected[0] >= 0 && selected[1] >= 0) {
            // Feld wurde ausgewählt (Enter gedrückt) - sollte nicht passieren im Spiel-Loop
            // Weiter zum nächsten Durchlauf
        } else {
            // ESC/q gedrückt - Spiel beenden
            break;
        }
    }
    
    // Cleanup am Ende des Programms - immer aufrufen
    cleanup_input();
    return 0;
}