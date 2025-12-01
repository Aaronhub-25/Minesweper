#ifndef FELD_H
#define FELD_H

#include <string>
#include <vector>

// Forward declaration
class game;

// Jedes Feld erhält eine public id mit 3 private Zuständen
class feld
{
private:
    bool ismine;
public:
    std::vector<int> id;  // gibt die Position des Feldes an [x, y]
    bool marked;    // feld is either marked(1) or unmarked(0)
    bool reveald; //  feld is either reveald(1) or unreveald(0)
    int mines_arround; // gibt Anzal an anliegenden Mineien an
    
    // Konstruktor
    feld(std::vector<int> position = {0, 0}) : id(position), ismine(false), marked(false), reveald(false) {}
    
    // Mark this field or unmark it
    void mark();
    // Reveal this tile
    void reveal(game& g);
    // Set mine status (used during grid generation)
    void set_mine(bool mine) { ismine = mine; }
    // Get mine status
    bool is_mine() const { return ismine; }
    // Count Mines arround
    void count_mines_arround(game& g);
};

#endif // FELD_H

