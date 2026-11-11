#pragma once

#include <string>
#include <vector>
#include "raylib.h"

struct Tile {
    int id;
    int x, y, w, h;
};

struct Tileset {
    int id;
    std::string image_path;
    Texture2D texture;
    int tile_w, tile_h;
    int margin = 0, spacing = 0;
    std::vector<Tile> tiles;
};

struct TileRef {
    int tileset_id;
    int tile_id;
};
