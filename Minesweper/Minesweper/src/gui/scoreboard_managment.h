#ifndef SCOREBOARD_MANAGMENT_H
#define SCOREBOARD_MANAGMENT_H

#include <string>
#include <vector>

struct Score {
    char name[20]; 
    double time;
};

void save_high_score(const std::string& user_name, double finish_time);
std::vector<Score> load_high_score();



#endif // SCOREBOARD_MANAGMENT_H