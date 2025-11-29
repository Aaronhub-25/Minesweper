#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "feld.h"

class game
{
private:
    int width;
    int height;
    int mine_count;
    std::vector<std::vector<feld>> grid;  // 2D Grid aus Feldern
    void genrate_plane(); // Uses paramters to assaign felds their mines

public:
    std::string difficulty;
    bool game_state = 1; // 
    
    // Konstruktor - erstellt Grid basierend auf width und height
    game();
    
    void Enter_difficulty(const std::string& input);
    void build_game();  // Uses the difficulty member variable to define width hight mine count
    
    // Getter methods to access game parameters
    int get_width() const { return width; }
    int get_height() const { return height; }
    int get_mine_count() const { return mine_count; }
    const std::vector<std::vector<feld>>& get_grid() const { return grid; }
    std::vector<std::vector<feld>>& get_grid() { return grid; }  // Non-const version for modification
    
    // Schreibt das Grid in eine txt-Datei
    void write_grid_to_file(const std::string& filename) const;
};

#endif // GAME_H

