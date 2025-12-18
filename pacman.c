#include "pacman.h"
#include "raylib.h"
#include "raymath.h"
#define EMPTY 0 // مقدار فضای خالی
#define WALL 1  // مقدار دیوار
#define POINT 2 // مقدار نقطه امتیاز
#define APPLE 3  // مقدار apple
#define MUSHROOM 4
#define PEPPER 5
#define CHERRY 6
void InitPacman(Pacman *pacman) {
    pacman->position = (Vector2){ 60, 100 };
    pacman->speed = 150.0f;
    pacman->radius = 12.9f;
    pacman->direction = (Vector2){ 0, 0 };
    pacman->invincibleTimer = 0;
    pacman->soulٍEater=0;
    pacman->score = 0;
    pacman->HP = 1;
    pacman->collectedPoints = 0;
    pacman->collectedHP = 0;
    pacman->mouthAngle = 45.0f;
    pacman->mouthClosing = true;
    pacman->lastRotationAngle = 0.0f; // مقدار اولیه زاویه
}



void UpdatePacman(Pacman *pacman, Map *map,Sound munch,Sound credit,int random) {

    pacman->direction = (Vector2){ 0, 0 };

    // به‌روزرسانی جهت حرکت بر اساس کلیدهای ورودی
    if (IsKeyDown(KEY_UP)) pacman->direction.y = -1;
    if (IsKeyDown(KEY_DOWN)) pacman->direction.y = 1;
    if (IsKeyDown(KEY_LEFT)) pacman->direction.x = -1;
    if (IsKeyDown(KEY_RIGHT)) pacman->direction.x = 1;

    // تنظیم جهت نرمال شده
    if (pacman->direction.x != 0 || pacman->direction.y != 0) {
        pacman->direction = Vector2Normalize(pacman->direction);

        // تنظیم زاویه چرخش بر اساس جهت حرکت
        if (pacman->direction.x > 0) pacman->lastRotationAngle = 0.0f;       // راست
        else if (pacman->direction.x < 0) pacman->lastRotationAngle = 180.0f; // چپ
        else if (pacman->direction.y > 0) pacman->lastRotationAngle = 90.0f;  // پایین
        else if (pacman->direction.y < 0) pacman->lastRotationAngle = 270.0f; // بالا
    }

    // محاسبه موقعیت جدید
    Vector2 newPosition = Vector2Add(pacman->position, Vector2Scale(pacman->direction, pacman->speed * GetFrameTime()));

    // بررسی برخورد با نقشه
    if (!CheckCollisionWithMap(map, newPosition, pacman->radius)) {
        pacman->position = newPosition;

        // بررسی جمع‌آوری نقاط
        int cellX = newPosition.x / map->cellSize;
        int cellY = newPosition.y / map->cellSize;
        if (pacman->invincibleTimer > 0) {
            pacman->invincibleTimer--;
        }
        if (pacman->soulٍEater > 0) {
            pacman->soulٍEater--;
        }
        if (map->grid[cellY][cellX] == 2) {  // اگر نقطه باشد
            PlaySound(munch);
            pacman->score++;
            pacman->collectedPoints++;
            map->grid[cellY][cellX] = 0;  // نقطه جمع‌آوری شد

            // بازنشانی نقاط اگر همه جمع شدند
            if (pacman->collectedPoints == MAX_POINTS) {
                pacman->collectedPoints = 0;  // بازنشانی تعداد نقاط جمع‌شده
                if(random==0) {
                    InitMap(map);             // ایجاد دوباره نقاط
                } else if(random==1){
                    InitMap2(map);
                }
            }
        }
        // بررسی جمع‌آوری سیب

        if (map->grid[cellY][cellX] == 3) {  // اگر سیب باشد
            PlaySound(credit);
            pacman->HP++;
            pacman->collectedHP++;
            map->grid[cellY][cellX] = 0;  // سیب جمع‌آوری شد

            // بازنشانی نقاط اگر همه جمع شدند
            /*if (pacman->collectedHP == MAX_HP) {
                pacman->collectedHP = 0;  // بازنشانی تعداد سیب جمع‌شده
                InitPoints(map);             // ایجاد دوباره سیب
            }*/
        }
        if (map->grid[cellY][cellX] == MUSHROOM) {
            PlaySound(credit);
            pacman->HP--;
            map->grid[cellY][cellX] = 0;
        }
        if (map->grid[cellY][cellX] == PEPPER) {
            PlaySound(credit);
            pacman->speed +=9;
            map->grid[cellY][cellX] = 0;
        }
        if (map->grid[cellY][cellX] == CHERRY) {
            PlaySound(credit);
            pacman->soulٍEater +=1200;
            map->grid[cellY][cellX] = 0;
        }
    }
}




void DrawPacman(Pacman *pacman, Font customFontRecords, Texture2D live) {
    // تغییر زاویه دهان (باز و بسته شدن)
    if (pacman->mouthClosing) {
        pacman->mouthAngle -= 90 * GetFrameTime();
        if (pacman->mouthAngle <= 10) pacman->mouthClosing = false;
    } else {
        pacman->mouthAngle += 90 * GetFrameTime();
        if (pacman->mouthAngle >= 45) pacman->mouthClosing = true;
    }

    // چرخاندن دهان
    float startAngle = pacman->lastRotationAngle + pacman->mouthAngle;
    float endAngle = pacman->lastRotationAngle + (360.0f - pacman->mouthAngle);

    // رنگ پکمن بر اساس وضعیت
    Color pacmanColor = YELLOW;
    if (pacman->invincibleTimer > 0 && (pacman->invincibleTimer / 30) % 2 == 0) {
        pacmanColor = GRAY;
    } else if (pacman->soulٍEater > 0 && (pacman->soulٍEater / 30) % 2 == 0) {
        pacmanColor = RED;
    }

    // رسم پکمن با دهان متحرک و جهت چرخش
    DrawCircleSector(
            pacman->position,
            pacman->radius,
            startAngle,
            endAngle,
            36,
            pacmanColor
    );

    // نمایش امتیاز و HP
    DrawTextEx(customFontRecords, TextFormat("Score: %d", pacman->score), (Vector2){10, 6}, 33, 2, WHITE);
    DrawTextEx(customFontRecords, TextFormat("Press BACKSPACE To Show Menu"), (Vector2){400, 570}, 25, 2, WHITE);
    for (int co = 0; co < pacman->HP; co++) {
        DrawTexture(live, 155 + 36 * co, 4, WHITE);
    }
}