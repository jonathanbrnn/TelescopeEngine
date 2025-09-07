#include "Editor.h"

void Editor::DrawUI() {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("window_0"); 
    ImGui::Text("This is text."); 
    ImGui::End(); 
}