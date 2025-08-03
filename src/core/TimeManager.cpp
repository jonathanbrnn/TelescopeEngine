#include "TimeManager.h"

using namespace std; 

void TimeManager::UpdateTime() {
    auto current_time = chrono::high_resolution_clock::now();
    chrono::duration<float> elapsed_time = current_time - original_time;
    //cout << elapsed_time.count() << endl; check for 60fps cause 1 / 60 = 0.0167f
    delta_time = elapsed_time.count();
    original_time = current_time;
}

float TimeManager::GetDeltaTime() {
    return delta_time;
}