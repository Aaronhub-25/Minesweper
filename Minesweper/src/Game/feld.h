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
    bool mine;
    int id;  // gibt die Position des Feldes an id = y * width +x
    bool marked;    // feld is either marked(1) or unmarked(0)
    bool reveald; //  feld is either reveald(1) or unreveald(0)
    int mines_arround; // gibt Anzal an anliegenden Mineien an
public:
    // Konstruktor
    feld(int id = 0) : mine(false), id(id), marked(false), reveald(false), mines_arround(0) {}

    
    void mark();// Mark this field or unmark it
    void reveal(game& g);// Reveal this tile
    
    // Getter methods
    bool is_mine() const { return mine; }
    bool is_marked() const { return marked; }
    bool is_reveald() const { return reveald; }
    int get_mines_arround() const { return mines_arround; }
    int get_id() const { return id; }
    int get_id_x(const game& g) const;
    int get_id_y(const game& g) const;
    
    // Setter methods
    void set_mine(bool mine) { this->mine = mine; }
    void set_marked(bool value) { marked = value; }
    void set_reveald(bool value) { reveald = value; }
    void set_mines_arround(int value) { mines_arround = value; }
    void set_id(int value) { id = value; }
    
    // Count Mines arround
    void count_mines_arround(game& g);
};

#endif // FELD_H

