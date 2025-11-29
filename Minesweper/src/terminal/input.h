#ifndef INPUT_H
#define INPUT_H

// Initialize ncurses
void init_input();

// Cleanup ncurses
void cleanup_input();

// Get a key press, returns key code
// Returns special codes for arrow keys:
// KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT (from ncurses)
// Or regular character codes
int get_key();

#endif // INPUT_H

