#ifndef BANNER_H
#define BANNER_H

#include <string>

// Gibt das Banner in ncurses aus (start_y = Startzeile für das Banner)
int PrintBanner(const std::string& filepath, int start_y = 0);

#endif // BANNER_H

