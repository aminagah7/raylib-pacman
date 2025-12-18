#include "enemy.h"
#include "raymath.h"
#include "map.h"
#include <stdlib.h>
#include <time.h>

// ثابت‌ها
#define CELL_SIZE 40


// تابع تنظیم اولیه دشمن‌ها با ورودی‌های تکسچر
void InitEnemies(Enemy enemies[], int count, Texture2D textures[],float SPEED) {
    for (int i = 0; i < count; i++) {
        enemies[i].radius = 17.0f;
        enemies[i].invincibleTimer = 0;
    }

    // تنظیم موقعیت و سرعت اولیه
    if (count > 0) {
        enemies[0].position = (Vector2){3 * CELL_SIZE + CELL_SIZE / 2, 3 * CELL_SIZE + CELL_SIZE / 2};
        enemies[0].speed = (Vector2){0, SPEED};
        enemies[0].texture = textures[0];
    }
    if (count > 1) {
        enemies[1].position = (Vector2){10 * CELL_SIZE + CELL_SIZE / 2, 5 * CELL_SIZE + CELL_SIZE / 2};
        enemies[1].speed = (Vector2){SPEED, 0};
        enemies[1].texture = textures[1];
    }
    if (count > 2) {
        enemies[2].position = (Vector2){15 * CELL_SIZE + CELL_SIZE / 2, 8 * CELL_SIZE + CELL_SIZE / 2};
        enemies[2].speed = (Vector2){0, SPEED};
        enemies[2].texture = textures[2];
    }
    if (count > 3) {
        enemies[3].position = (Vector2){9 * CELL_SIZE + CELL_SIZE / 2, 11 * CELL_SIZE + CELL_SIZE / 2};
        enemies[3].speed = (Vector2){0, -SPEED};
        enemies[3].texture = textures[3];
    }
    if (count > 4) {
        enemies[4].position = (Vector2){8 * CELL_SIZE + CELL_SIZE / 2, 1 * CELL_SIZE + CELL_SIZE / 2};
        enemies[4].speed = (Vector2){SPEED, 0};
        enemies[4].texture = textures[4];
    }
    if (count > 5) {
        enemies[5].position = (Vector2){8 * CELL_SIZE + CELL_SIZE / 2, 1 * CELL_SIZE + CELL_SIZE / 2};
        enemies[5].speed = (Vector2){SPEED, 0};
        enemies[5].texture = textures[5];
    }
    if (count > 6) {
        enemies[6].position = (Vector2){8 * CELL_SIZE + CELL_SIZE / 2, 1 * CELL_SIZE + CELL_SIZE / 2};
        enemies[6].speed = (Vector2){SPEED, 0};
        enemies[6].texture = textures[6];
    }
}
// تابع تنظیم اولیه دشمن‌ها متناسب با مپ جدید
void InitEnemiesForNewMap(Enemy enemies[], int count, Texture2D textures[], float SPEED) {
    for (int i = 0; i < count; i++) {
        enemies[i].radius = 17.0f;
        enemies[i].invincibleTimer = 0;
    }

    // تنظیم موقعیت و سرعت اولیه برای مپ جدید
    if (count > 0) {
        enemies[0].position = (Vector2){740, 540};
        enemies[0].speed = (Vector2){0, SPEED};
        enemies[0].texture = textures[0];
    }
    if (count > 1) {
        enemies[1].position = (Vector2){60, 540};
        enemies[1].speed = (Vector2){-SPEED, 0};
        enemies[1].texture = textures[1];
    }
    if (count > 2) {
        enemies[2].position = (Vector2){740, 60};
        enemies[2].speed = (Vector2){0, SPEED};
        enemies[2].texture = textures[2];
    }
    if (count > 3) {
        enemies[3].position = (Vector2){220, 140};
        enemies[3].speed = (Vector2){0, -SPEED};
        enemies[3].texture = textures[3];
    }
    if (count > 4) {
        enemies[4].position = (Vector2){500, 220};
        enemies[4].speed = (Vector2){SPEED, 0};
        enemies[4].texture = textures[4];
    }
    if (count > 5) {
        enemies[5].position = (Vector2){220, 300};
        enemies[5].speed = (Vector2){-SPEED, 0};
        enemies[5].texture = textures[5];
    }
    if (count > 6) {
        enemies[6].position = (Vector2){220, 300};
        enemies[6].speed = (Vector2){-SPEED, 0};
        enemies[6].texture = textures[6];
    }
}
// چک کردن برخورد دشمن با دیوار یا مرز نقشه
bool CheckEnemyCollision(const Map *map, Vector2 position, float radius) {
    int leftCell = (position.x - radius) / map->cellSize;
    int rightCell = (position.x + radius) / map->cellSize;
    int topCell = (position.y - radius) / map->cellSize;
    int bottomCell = (position.y + radius) / map->cellSize;

    // بررسی اینکه خارج از نقشه است یا نه
    if (leftCell < 0 || rightCell >= MAP_COLS || topCell < 0 || bottomCell >= MAP_ROWS) {
        return true;
    }

    // برخورد با دیوارها
    for (int y = topCell; y <= bottomCell; y++) {
        for (int x = leftCell; x <= rightCell; x++) {
            if (map->grid[y][x] == WALL) {
                return true;
            }
        }
    }

    return false;
}

// انتخاب جهت تصادفی جدید برای دشمن
// انتخاب جهت تصادفی جدید برای دشمن (بدون 180 درجه)
// انتخاب جهت تصادفی جدید برای دشمن (بدون 180 درجه)
Vector2 GetRandomDirectionNoReverse(Vector2 currentDirection,float SPEED) {
    Vector2 newDirection;
    do {
        switch (rand() % 4) {
            case 0: newDirection = (Vector2){SPEED, 0};   break; // راست
            case 1: newDirection = (Vector2){-SPEED, 0};  break; // چپ
            case 2: newDirection = (Vector2){0, SPEED};   break; // پایین
            case 3: newDirection = (Vector2){0, -SPEED};  break; // بالا
        }
    } while (Vector2Equals(newDirection, Vector2Negate(currentDirection))); // اطمینان از نبودن 180 درجه
    return newDirection;
}

// بروزرسانی حرکت دشمن‌ها
void UpdateEnemies(Enemy enemies[], int count, const Map *map ,Vector2 playerPosition,float SPEED) {
    for (int i = 0; i < count; i++) {
        Vector2 nextPosition = Vector2Add(enemies[i].position, Vector2Scale(enemies[i].speed, GetFrameTime() * 100));

        // بررسی برخورد
        if (!CheckEnemyCollision(map, nextPosition, enemies[i].radius)&&enemies[i].invincibleTimer == 0) {
            enemies[i].position = nextPosition; // حرکت دشمن
        } else if(enemies[i].invincibleTimer>1){
            enemies[i].position= (Vector2){20,50 *(i+1)};
            enemies[i].invincibleTimer--;

        }else if(enemies[i].invincibleTimer==1){
            if (i== 0) {
                enemies[0].position = (Vector2){3 * CELL_SIZE + CELL_SIZE / 2, 3 * CELL_SIZE + CELL_SIZE / 2};
                enemies[0].speed = (Vector2){0, 2.0f};
            }
            if (i== 1) {
                enemies[1].position = (Vector2){10 * CELL_SIZE + CELL_SIZE / 2, 5 * CELL_SIZE + CELL_SIZE / 2};
                enemies[1].speed = (Vector2){1.8f,0 };

            }
            if (i== 2) {
                enemies[2].position = (Vector2){15 * CELL_SIZE + CELL_SIZE / 2, 8 * CELL_SIZE + CELL_SIZE / 2};
                enemies[2].speed = (Vector2){0, 1.2f};

            }
            if (i== 3) {
                enemies[3].position = (Vector2){9 * CELL_SIZE + CELL_SIZE / 2, 11 * CELL_SIZE + CELL_SIZE / 2};
                enemies[3].speed = (Vector2){0, -1.9f};

            }
            if (i== 4) {
                enemies[4].position = (Vector2){8 * CELL_SIZE + CELL_SIZE / 2, 1 * CELL_SIZE + CELL_SIZE / 2};
                enemies[4].speed = (Vector2){1, 0};

            }
            if (i== 5) {
                enemies[5].position = (Vector2){8 * CELL_SIZE + CELL_SIZE / 2, 1 * CELL_SIZE + CELL_SIZE / 2};
                enemies[5].speed = (Vector2){1, 0};

            }
            if (i== 6) {
                enemies[6].position = (Vector2){8 * CELL_SIZE + CELL_SIZE / 2, 1 * CELL_SIZE + CELL_SIZE / 2};
                enemies[6].speed = (Vector2){1, 0};

            }
            enemies[i].invincibleTimer--;
        }
        else {
            // تغییر جهت تصادفی در صورت برخورد
            Vector2 previousSpeed = enemies[i].speed; // ذخیره جهت فعلی
            enemies[i].speed = GetRandomDirectionNoReverse(previousSpeed,SPEED);

            // اطمینان از حرکت به مسیر معتبر
            nextPosition = Vector2Add(enemies[i].position, Vector2Scale(enemies[i].speed, GetFrameTime() * 100));
            while (CheckEnemyCollision(map, nextPosition, enemies[i].radius)) {
                enemies[i].speed = GetRandomDirectionNoReverse(previousSpeed,SPEED);
                nextPosition = Vector2Add(enemies[i].position, Vector2Scale(enemies[i].speed, GetFrameTime() * 100));
            }
        }
    }
}
// بروزرسانی حرکت دشمن‌ها
void UpdateEnemies2(Enemy enemies[], int count, const Map *map ,Vector2 playerPosition,float SPEED) {
    for (int i = 0; i < count; i++) {
        Vector2 nextPosition = Vector2Add(enemies[i].position, Vector2Scale(enemies[i].speed, GetFrameTime() * 100));

        // بررسی برخورد
        if (!CheckEnemyCollision(map, nextPosition, enemies[i].radius)&&enemies[i].invincibleTimer == 0) {
            enemies[i].position = nextPosition; // حرکت دشمن
        } else if(enemies[i].invincibleTimer>1){
            enemies[i].position= (Vector2){20,50 *(i+1)};
            enemies[i].invincibleTimer--;

        }else if(enemies[i].invincibleTimer==1){
            // تنظیم موقعیت و سرعت اولیه برای مپ جدید
            if (i == 0) {
                enemies[0].position = (Vector2){740, 540};
                enemies[0].speed = (Vector2){0, SPEED};
            }
            if (i == 1) {
                enemies[1].position = (Vector2) {60, 540};
                enemies[1].speed = (Vector2) {-SPEED, 0};
            }
            if (i == 2) {
                enemies[2].position = (Vector2){740, 60};
                enemies[2].speed = (Vector2){0, SPEED};
            }
            if (i == 3) {
                enemies[3].position = (Vector2){220, 140};
                enemies[3].speed = (Vector2){0, -SPEED};
            }
            if (i == 4) {
                enemies[4].position = (Vector2){500, 220};
                enemies[4].speed = (Vector2){SPEED, 0};
            }
            if (i == 5) {
                enemies[5].position = (Vector2){220, 300};
                enemies[5].speed = (Vector2){-SPEED, 0};
            }
            if (i == 6) {
                enemies[6].position = (Vector2){220, 300};
                enemies[6].speed = (Vector2){-SPEED, 0};
            }
            enemies[i].invincibleTimer--;
        }
        else {
            // تغییر جهت تصادفی در صورت برخورد
            Vector2 previousSpeed = enemies[i].speed; // ذخیره جهت فعلی
            enemies[i].speed = GetRandomDirectionNoReverse(previousSpeed,SPEED);

            // اطمینان از حرکت به مسیر معتبر
            nextPosition = Vector2Add(enemies[i].position, Vector2Scale(enemies[i].speed, GetFrameTime() * 100));
            while (CheckEnemyCollision(map, nextPosition, enemies[i].radius)) {
                enemies[i].speed = GetRandomDirectionNoReverse(previousSpeed,SPEED);
                nextPosition = Vector2Add(enemies[i].position, Vector2Scale(enemies[i].speed, GetFrameTime() * 100));
            }
        }
    }
}

void DrawEnemies(Enemy enemies[], int count) {
    for (int i = 0; i < count; i++) {
        // رسم تکسچر اصلی دشمن
        DrawTexture(
                enemies[i].texture,
                enemies[i].position.x - enemies[i].radius,
                enemies[i].position.y - enemies[i].radius,
                WHITE
        );

        // محاسبه موقعیت چشم‌ها بر اساس جهت حرکت
        float eyeOffsetX = 0;
        float eyeOffsetY = 0;

        if (enemies[i].speed.x > 0) { // حرکت به راست
            eyeOffsetX = 3;
        } else if (enemies[i].speed.x < 0) { // حرکت به چپ
            eyeOffsetX = -3;
        } else if (enemies[i].speed.y > 0) { // حرکت به پایین
            eyeOffsetY = 3;
        } else if (enemies[i].speed.y < 0) { // حرکت به بالا
            eyeOffsetY = -3;
        }

        // موقعیت چشم اول
        Vector2 eye1Pos = {
                enemies[i].position.x - 7 + eyeOffsetX, // موقعیت افقی چشم اول
                enemies[i].position.y - 5 + eyeOffsetY  // موقعیت عمودی چشم اول
        };

        // موقعیت چشم دوم
        Vector2 eye2Pos = {
                enemies[i].position.x + 3 + eyeOffsetX, // موقعیت افقی چشم دوم
                enemies[i].position.y - 5 + eyeOffsetY  // موقعیت عمودی چشم دوم
        };

        // رسم دایره سفید ثابت زیر چشم‌ها
        DrawCircle(eye1Pos.x, eye1Pos.y, 4, WHITE); // دایره سفید برای چشم اول
        DrawCircle(eye2Pos.x, eye2Pos.y, 4, WHITE); // دایره سفید برای چشم دوم

        // رسم دایره سیاه برای مردمک چشم‌ها
        DrawCircle(eye1Pos.x, eye1Pos.y, 2, BLACK); // مردمک چشم اول
        DrawCircle(eye2Pos.x, eye2Pos.y, 2, BLACK); // مردمک چشم دوم
    }
}
