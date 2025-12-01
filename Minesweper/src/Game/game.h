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
    int number_of_fields;
    std::vector<std::vector<feld>> grid;  // 2D Grid aus Feldern
    
    public:
    std::string difficulty;
    int openfields; // number of open fields
    bool game_state = 1; // game state 1 = running, 0 = game over
    
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
    void generate_plane();// Generates the plane with the correct number of fields
    void place_mines();// Places mines on the grid
};

#endif // GAME_H

