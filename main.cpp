#include <iostream>
#include <vector>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

int main() {
    const int scr_w = 1200;
    const int scr_h = 720;
    InitWindow(scr_w, scr_h, "mosaics-editor");

    rlImGuiSetup(true);

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
            rlImGuiBegin();
            ClearBackground(BLACK);
            ImGui::ShowDemoWindow();
            rlImGuiEnd();
        EndDrawing();
    }
    rlImGuiShutdown();
    CloseWindow();
    return 0;
}
