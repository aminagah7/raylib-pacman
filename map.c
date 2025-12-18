#include "map.h"
#define pacpos 8
bool CheckCollisionWithMap(const Map *map, Vector2 position, float radius) {
    // محاسبه محدوده سلول‌هایی که باید بررسی شوند
    int leftCell = (position.x - (radius-1.5f)) / map->cellSize;
    int rightCell = (position.x + (radius-1.5f)) / map->cellSize;
    int topCell = (position.y - (radius-1.5f)) / map->cellSize;
    int bottomCell = (position.y + (radius-1.5f)) / map->cellSize;

    // بررسی اینکه آیا محدوده درون مرزهای نقشه است
    if (leftCell < 0 || rightCell >= MAP_COLS || topCell < 0 || bottomCell >= MAP_ROWS) {
        return true; // برخورد با مرزهای نقشه
    }

    // بررسی سلول‌های اطراف شعاع
    for (int y = topCell; y <= bottomCell; y++) {
        for (int x = leftCell; x <= rightCell; x++) {
            if (map->grid[y][x] == WALL) {
                return true; // برخورد با دیوار
            }
        }
    }

    return false; // بدون برخورد
}


void InitPoints(Map *map) {
    for (int i = 0; i < MAX_POINTS; i++) {
        int x = GetRandomValue(1, MAP_COLS - 2);
        int y = GetRandomValue(1, MAP_ROWS - 2);
        if (map->grid[y][x] == EMPTY) {
            map->grid[y][x] = POINT;  // نقطه
        } else {
            i--;  // اگر سلول پر بود، دوباره تلاش کن
        }
    }

    // اضافه کردن میوه
    for (int i = 0; i < 1; i++) {
        int x = GetRandomValue(1, MAP_COLS - 2);
        int y = GetRandomValue(1, MAP_ROWS - 2);
        if (map->grid[y][x] == EMPTY) {
            map->grid[y][x] = APPLE;
        } else {
            i--;
        }
    }
    // اضافه کردن قارچ
    for (int i = 0; i < 2; i++) {
        int x = GetRandomValue(1, MAP_COLS - 2);
        int y = GetRandomValue(1, MAP_ROWS - 2);
        if (map->grid[y][x] == EMPTY) {
            map->grid[y][x] = MUSHROOM;
        } else {
            i--;
        }
    }
    // اضافه کردن pepper
    for (int i = 0; i < 1; i++) {
        int x = GetRandomValue(1, MAP_COLS - 2);
        int y = GetRandomValue(1, MAP_ROWS - 2);
        if (map->grid[y][x] == EMPTY) {
            map->grid[y][x] = PEPPER;
        } else {
            i--;
        }
    }
    // اضافه کردن cherry
    for (int i = 0; i < 1; i++) {
        int x = GetRandomValue(1, MAP_COLS - 2);
        int y = GetRandomValue(1, MAP_ROWS - 2);
        if (map->grid[y][x] == EMPTY) {
            map->grid[y][x] = CHERRY;
        } else {
            i--;
        }
    }
}


void InitMap(Map *map) {
        // مقداردهی اولیه سایز هر سلول
        map->cellSize = SCREEN_WIDTH / MAP_COLS;

    // مپ بازی
    int tempMap[MAP_ROWS][MAP_COLS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},  // ردیف اضافی اول
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}   // ردیف اضافی دوم
    };

    for (int i = 0; i < MAP_ROWS; i++) {
            for (int j = 0; j < MAP_COLS; j++) {
                map->grid[i][j] = tempMap[i][j];
            }
        }


    InitPoints(map);  // اضافه کردن نقاط اولیه
}
void InitMap2(Map *map) {
    // مقداردهی اولیه سایز هر سلول
    map->cellSize = SCREEN_WIDTH / MAP_COLS;

    int tempMap[MAP_ROWS][MAP_COLS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            map->grid[i][j] = tempMap[i][j];
        }
    }


    InitPoints(map);  // اضافه کردن نقاط اولیه
}


void DrawMap(Map *map,Texture2D wall,Texture2D apple,Texture2D poisonousmushroom,Texture2D pepper,Texture2D cherry,Texture2D point,Texture2D point2, int frameCounter) {

    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            int x = j * map->cellSize;
            int y = i * map->cellSize;

            if (map->grid[i][j] == WALL) {
                //DrawRectangle(x, y, map->cellSize, map->cellSize, BLUE);
                DrawTexture(wall, x, y, WHITE);
            } else if (map->grid[i][j] == POINT) {
                // انتخاب تصویر برای چشمک زدن
                if ((frameCounter / 50) % 2 == 0) { // تغییر هر 30 فریم
                    DrawTexture(point, x + map->cellSize / 2 - 15, y + map->cellSize / 2 - 15, WHITE);
                } else {
                    DrawTexture(point2, x + map->cellSize / 2 - 15, y + map->cellSize / 2 - 15, WHITE);
                }

            } else if (map->grid[i][j] == APPLE) {
                DrawTexture(apple, x + map->cellSize / 2-15, y + map->cellSize / 2-15, WHITE);
            }else if (map->grid[i][j] == MUSHROOM) {
                DrawTexture(poisonousmushroom, x + map->cellSize / 2-15, y + map->cellSize / 2-15, WHITE);
            }
            else if (map->grid[i][j] == PEPPER) {
                DrawTexture(pepper, x + map->cellSize / 2-15, y + map->cellSize / 2-15, WHITE);
            }
            else if (map->grid[i][j] == CHERRY) {
                DrawTexture(cherry, x + map->cellSize / 2-15, y + map->cellSize / 2-15, WHITE);
            }
        }
    }
}


