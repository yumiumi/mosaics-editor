#include <vector>
#include "raylib.h"
#include "parser.h"

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

void parser(const char* file, std::vector<Tileset>& tilesets) {
    char *text = LoadFileText(file);

    if(text == NULL) {
        printf("Failed to load file: %s\n", file);
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
            int len = 0;
            int max_len = (int)sizeof(ts.file_name) - 1;
            while(*p != '"' && *p != '\n' && *p != '\0') {
                if(len < max_len) {
                    ts.file_name[len] = *p;
                    len++;
                }
                p++;
            }
            ts.file_name[len] = '\0';
            if(*p != '"') {
                printf("unterminated string in %s\n", file);
                break;
            }
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
