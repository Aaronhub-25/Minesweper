#include "enter_user_name.h"
#include "input.h"
#include <ncurses.h>
#include <string>


std::string enter_user_name() {
    // 1. WICHTIG: Alten Input wegwerfen, damit getnstr nicht sofort schließt
    flushinp(); 
    
    // 2. Bildschirm leeren und dem Terminal mitteilen
    clear();
    refresh(); 

    char buffer[128] = {0}; // Puffer sicherheitshalber nullen
    
    curs_set(1); 
    echo();      
    
    mvprintw(3, 0, "Enter user name. Press Enter to confirm.");
    mvprintw(4, 0, "Username: "); 
    
    // 3. Cursor steht jetzt nach "Username: "
    refresh(); 
    
    getnstr(buffer, sizeof(buffer) - 1); 
    
    noecho();
    curs_set(0);
    
    return std::string(buffer);
}
