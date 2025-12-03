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
    std::vector<feld> grid;  // 2D Grid aus Feldern
    std::string difficulty;
    int openfields; // number of open fields
    bool game_state; // game state 1 = running, 0 = game over
    std::vector<int> mines_ids; // ids of the mines werden auf der gerade f(x,y)=y*width+x gespeichert
    
public:
    // Konstruktor - erstellt Grid basierend auf width und height
    game();
    
    void Enter_difficulty(const std::string& input);
    void build_game();  // Uses the difficulty member variable to define width hight mine count
    void generate_plane();// Generates the plane with the correct number of fields
    void place_mines(int first_guess_id); // Places mines on the grid
    
    // Getter methods
    int get_width() const { return width; }
    int get_height() const { return height; }
    int get_mine_count() const { return mine_count; }
    int get_openfields() const { return openfields; }
    bool get_game_state() const { return game_state; }
    std::string get_difficulty() const { return difficulty; }
    const std::vector<feld>& get_grid() const { return grid; }
    feld& get_grid(int id) { return grid[id]; }  // Non-const version for modification
    
    // Setter methods
    void set_openfields(int value) { openfields = value; }
    void set_game_state(bool value) { game_state = value; }
    void decrement_openfields() { openfields--; }
};

#endif // GAME_H

