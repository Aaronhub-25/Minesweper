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
    int first_guess_id; // Id of first guess
    bool game_state; // game state 1 = running, 0 = game over
    bool first_guess_done; // tracks wheter first guess was done is zero zu beginn
    std::vector<int> mines_ids; // ids of the mines werden auf der gerade f(x,y)=y*width+x gespeichert
    std::vector<int> available_ids; // alle verfügbaren IDs für Minen-Platzierung
    
public:
    // Konstruktor - erstellt Grid basierend auf width und height
    game();
    
    void build_game(const std::string& difficulty);  // Sets difficulty and builds game field based on difficulty
    void generate_plane();// Generates the plane with the correct number of fields
    void place_mines(int first_guess_id); // Places mines on the grid
    void reveal_open_adjacent_fields(int id); // Reveal all adjacent fields if current field has 0 mines around
    void decrement_openfields() { openfields--; } // decreses number of open fields
    
    // Getter methods
    int get_width() const { return width; } // get width of the game
    int get_height() const { return height; } // get height of the game
    int get_mine_count() const { return mine_count; } // get number of mines
    int get_openfields() const { return openfields; } // get number of open fields
    int get_first_guess_id() const { return first_guess_id;} // get id of first guess
    bool get_game_state() const { return game_state; } // get game state
    bool get_first_guess_done() const {return first_guess_done;} // get first guess done
    int get_number_of_fields() const { return number_of_fields; } // get number of fields

    std::string get_difficulty() const { return difficulty; } // get difficulty
    const std::vector<feld>& get_grid() const { return grid; } // get grid
    feld& get_grid(int id) { return grid[id]; }  // Non-const version for modification

    
    // Setter methods
    void set_width(int value) { width = value; }
    void set_height(int value) { height = value; }
    void set_difficulty(std::string value) { difficulty = value; }
    void set_mine_count(int value) { mine_count = value; }
    void set_number_of_fields(int value) { number_of_fields = value; }
    void set_openfields(int value) { openfields = value; }
    void set_game_state(bool value) { game_state = value; }
    void set_first_guess_done(bool value) { first_guess_done = value; }
    void set_first_guess_id(int value) { first_guess_id = value; }
    //
   
};

#endif // GAME_H

