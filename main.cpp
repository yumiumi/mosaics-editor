#include <vector>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "types.h"
#include "parser.h"

void generate_tiles(std::vector<Tileset>& ts) {
    for(int i = 0; i < ts.size(); i++) {
        const char* path = TextFormat("assets/%s", ts[i].file_name);
        ts[i].texture = LoadTexture(path);
        if (ts[i].texture.id == 0) {
            TraceLog(LOG_ERROR, "Failed to load texture: %s", ts[i].file_name);
            continue;
        }
        int row = ts[i].texture.height / ts[i].tile_h;
        int col = ts[i].texture.width / ts[i].tile_w;
        for(int y = 0; y < row; y++) {
            for(int x = 0; x < col; x++) {
                Tile t = {};
                t.id = y * col + x + 1;
                t.x = x * ts[i].tile_w;
                t.y = y * ts[i].tile_h;
                t.w = ts[i].tile_w;
                t.h = ts[i].tile_h;
                ts[i].tiles.push_back(t);
            }
        }
        SetTextureFilter(ts[i].texture, TEXTURE_FILTER_POINT);
    }
}

int main() {
    const int scr_w = 1600;
    const int scr_h = 720;
    InitWindow(scr_w, scr_h, "mosaics-editor");

    rlImGuiSetup(true);

    std::vector <Tileset> tilesets;
    parser("tilesets.txt", tilesets);
    generate_tiles(tilesets);

    int selected_t = 0;

    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        BeginDrawing();
            rlImGuiBegin();
            ClearBackground(BLACK);

            static int selected_ts = 0;

            if (ImGui::BeginListBox("Tilesets")) {
                for (int i = 0; i < tilesets.size(); i++) {
                    const bool is_selected = (selected_ts == i);
                    if (ImGui::Selectable(tilesets[i].file_name, is_selected)) {
                        selected_ts = i;
                    }
                    if (is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndListBox();
            }

            if(tilesets.size() > 0) {
                Tileset& ts = tilesets[selected_ts];
                float scale = 2.f;
                int col = ts.texture.width / ts.tile_w;

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

                for (int i = 0; i < (int)ts.tiles.size(); i++) {
                    const Tile& t = ts.tiles[i];
                    ImGui::PushID(i);

                    Rectangle src = {(float)t.x, (float)t.y, (float)t.w, (float)t.h};
                    rlImGuiImageRect(&ts.texture, (int)(t.w * scale), (int)(t.h * scale), src);

                    ImGui::SetCursorScreenPos(ImGui::GetItemRectMin());
                    if (ImGui::InvisibleButton("tile", ImVec2(t.w * scale, t.h * scale))) {
                        selected_t = t.id;
                    }

                    ImDrawList* dl = ImGui::GetWindowDrawList();
                    if(selected_t == t.id) {
                        dl->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 255, 255), 0, 0, 1.f);
                    }
                    else if(ImGui::IsItemHovered()) {
                        dl->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 255, 100), 0, 0, 1.f);
                    }

                    ImGui::PopID();

                    if ((i + 1) % col != 0) {
                        ImGui::SameLine();
                    }
                }
                ImGui::PopStyleVar();
            }
            rlImGuiEnd();
        EndDrawing();
    }
    // release GPU resources
    for (int i = 0; i < tilesets.size(); i++) {
        UnloadTexture(tilesets[i].texture);
    }
    rlImGuiShutdown();
    CloseWindow();
    return 0;
}
