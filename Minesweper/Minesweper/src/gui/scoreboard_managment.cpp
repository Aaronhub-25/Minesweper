#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "scoreboard_managment.h"



void save_high_score(const std::string& user_name, double finish_time) {
    const std::string filename = "scores.bin";
    std::vector<Score> scores = load_high_score();

    // 2. Neuen Score hinzufügen
    Score newScore;
    std::strncpy(newScore.name, user_name.c_str(), 19);
    newScore.name[19] = '\0'; // Sicherstellen, dass der String terminiert ist
    newScore.time = finish_time;
    scores.push_back(newScore);

    // 3. Sortieren (kleinste Zeit zuerst) und auf Top 5 kürzen
    std::sort(scores.begin(), scores.end(), [](const Score& a, const Score& b) {
        return a.time < b.time;
    });
    if (scores.size() > 5) scores.resize(5);

    // 4. Zurück in die Binärdatei schreiben
    std::ofstream outFile(filename, std::ios::binary | std::ios::trunc);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(scores.data()), scores.size() * sizeof(Score));
        outFile.close();
    }
}

std::vector<Score> load_high_score(){
    //Scores einladen
    const std::string filename = "scores.bin";
    std::vector<Score> scores;
    std::ifstream inFile(filename, std::ios::binary);

    if (!inFile) {
        // Falls die Datei noch nicht existiert, geben wir einen leeren Vektor zurück
        return scores; 
    }
    
    Score temp;
    while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(Score))) {
        scores.push_back(temp);
    }
    inFile.close();

    return scores;
}