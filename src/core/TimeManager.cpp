#include "TimeManager.h"
#include <chrono>

using namespace std; 

void TimeManager::UpdateTime() {
    auto current_time = chrono::high_resolution_clock::now();
    chrono::duration<float> elapsed_time = current_time - original_time;
    delta_time = elapsed_time.count();
    original_time = current_time;
}

float TimeManager::GetDeltaTime() {
    return delta_time;
}