#ifndef COUSTUM_DIFFICULTY_H
#define COUSTUM_DIFFICULTY_H

#include <string>

struct CustomSettings {
    int width;
    int height;
    int mines;
};

CustomSettings ask_coustum_settings();

#endif // COUSTUM_DIFFICULTY_H