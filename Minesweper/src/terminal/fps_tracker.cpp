#include "fps_tracker.h"
#include <unistd.h>
#include <chrono>

FPSTracker::FPSTracker(int target_fps) 
    : target_fps(target_fps), frame_count(0), current_fps(0.0) {
    start_time = std::chrono::high_resolution_clock::now();
    last_fps_update = start_time;
}

void FPSTracker::start_frame() {
    start_time = std::chrono::high_resolution_clock::now();
}

void FPSTracker::wait_for_next_frame() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    // Berechne wie lange wir warten müssen für die Ziel-FPS
    int frame_time_ms = 1000 / target_fps;
    
    if (duration.count() < frame_time_ms) {
        // Warte die verbleibende Zeit
        usleep((frame_time_ms - duration.count()) * 1000);
    }
    
    // Update FPS-Statistik alle Sekunde
    frame_count++;
    auto now = std::chrono::high_resolution_clock::now();
    auto time_since_update = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - last_fps_update).count();
    
    if (time_since_update >= 1000) {
        current_fps = (frame_count * 1000.0) / time_since_update;
        frame_count = 0;
        last_fps_update = now;
    }
}
