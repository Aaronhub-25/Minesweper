#ifndef FPS_TRACKER_H
#define FPS_TRACKER_H

#include <chrono>

class FPSTracker {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    int target_fps;
    int frame_count;
    std::chrono::high_resolution_clock::time_point last_fps_update;
    double current_fps;
    
public:
    // Konstruktor mit optionaler Ziel-FPS (Standard: 60)
    FPSTracker(int target_fps = 60);
    
    // Startet die Zeitmessung für einen neuen Frame
    void start_frame();
    
    // Wartet bis zum nächsten Frame (begrenzt FPS)
    void wait_for_next_frame();
    
    // Gibt die aktuelle FPS zurück (wird periodisch aktualisiert)
    double get_current_fps() const { return current_fps; }
    
    // Setzt die Ziel-FPS
    void set_target_fps(int fps) { target_fps = fps; }
    
    // Gibt die Ziel-FPS zurück
    int get_target_fps() const { return target_fps; }
};

#endif // FPS_TRACKER_H
