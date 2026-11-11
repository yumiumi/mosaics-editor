#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "types.h"

static void skip_spaces(char **p) {
    while(**p == ' ' || **p == '\t') (*p)++;
}
static void skip_comment(char **p) {
    if(**p == '#') {
        while(**p != '\n' && **p != '\0') (*p)++;
    }
}

int parse_int(char **p) {
    skip_spaces(p);
    int out = 0;
    while(**p >= '0' && **p <= '9') {
        int cur = **p - '0';
        out = out * 10 + cur;
        (*p)++;
    }
    return out;
}

void parser(const char* file_name, std::vector<Tileset>& tilesets) {
    char *text = LoadFileText(file_name);

    if(text == NULL) {
        printf("Failed to load file: %s\n", file_name);
        return;
    }

    char *p = text;
    while(*p != '\0') {
        skip_spaces(&p);
        skip_comment(&p);
        if(*p == '\0') break;
        if(*p == '\n') { p++; continue;}
        char *start = p;

        Tileset ts = {};

        ts.id = parse_int(&p);

        skip_spaces(&p);
        if(*p == '"') {
            p++;
            while(*p != '"' && *p != '\n' && *p != '\0') {
                ts.image_path += *p;
                p++;
            }
            assert (*p == '"' && "unterminated string in tileset file");
            p++;
        }

        ts.tile_w = parse_int(&p);
        ts.tile_h = parse_int(&p);
        ts.margin = parse_int(&p);
        ts.spacing = parse_int(&p);

        if(p == start) break;
        tilesets.push_back(ts);
    }
    UnloadFileText(text);
}

int main() {
    const int scr_w = 1200;
    const int scr_h = 720;
    InitWindow(scr_w, scr_h, "mosaics-editor");

    rlImGuiSetup(true);

    std::vector <Tileset> tilesets;

    parser("tilesets.txt", tilesets);
    printf("Loaded %zu tilesets\n", tilesets.size());

    SetTargetFPS(60);
    while(!WindowShouldClose()) {
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
