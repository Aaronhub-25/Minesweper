#include "end_page.h"
#include "input.h"
#include <ncurses.h>
#include <string>
#include "scoreboard_managment.h"
#include <vector>


std::string End_page(std::string end_result, std::string user_name, double finish_time, std::vector<Score> scores) {

    // Options to continue after game end
    const int NUM_OPTIONS = 3;
    const char* options[] = {
        "Play again",
        "Change Difficulty",
        "Exit"
    };
    
    // Load high scores
    scores = load_high_score();

    // Display high scores
    int selected = 0;
    int key;
    
    while (true) {
        clear();
        
        //Aktuelles Ergebnis und Spielername anzeigen
        mvprintw(2, 0, "Resultat: %s | Spieler: %s | Zeit: %.2f Sek.", end_result.c_str(), user_name.c_str(), finish_time);
        
        //Show highscores
        mvprintw(3, 0, "--- TOP 5 HIGHSCORES ---");
        if (scores.empty()) {
            mvprintw(4, 0, "Noch keine Eintraege vorhanden.");
        } else {
        for (size_t i = 0; i < scores.size(); ++i) {
  
            mvprintw(4 + i, 0, "%zu. %-15s | %.2f sek", 
                     i + 1, 
                     scores[i].name, 
                     scores[i].time);
        }
    }


        // Display options
        for (int i = 0; i < NUM_OPTIONS; i++) {
            if (i == selected) {
                attron(A_REVERSE);  // Highlight selected option
                mvprintw(11 + i, 2, "> %s", options[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(11 + i, 2, "  %s", options[i]);
            }
        }
        
        mvprintw(14, 0, "Use UP/DOWN arrows to navigate, ENTER to select");
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
            case 'e':
            case 'E':
            case 27:    // ESC key
                return "Exit";  // Default
        }
    }
}