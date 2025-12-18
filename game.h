#ifndef GAME_H
#define GAME_H

#include <raylib.h>

// اندازه صفحه
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// اندازه نقشه
#define MAP_ROWS 15   // تعداد ردیف‌های نقشه
#define MAP_COLS 20   // تعداد ستون‌های نقشه
#define MAX_ENEMIES 5
#define MAX_POINTS 10  // تعداد نقاط امتیاز
#define MAX_HP 2  // تعداد نقاط سیب
// ساختار پکمن
typedef struct Pacman {
    Vector2 position;
    float radius;
    Vector2 velocity;      // بردار سرعت
    Vector2 acceleration;  // بردار شتاب
    float speed;           // حداکثر سرعت
    Vector2 direction;
    int invincibleTimer; // حالت ایمنی
    int soulٍEater; //soul eater
    int score;
    int HP;
    int collectedPoints;
    int collectedHP;
    float mouthAngle;   // زاویه دهان
    bool mouthClosing;  // وضعیت باز و بسته شدن دهان
    float lastRotationAngle; // زاویه آخرین جهت حرکت
} Pacman;


// ساختار دشمن
typedef struct Enemy {
    int move;
    Vector2 lastDirection; // جهت حرکت قبلی
    int invincibleTimer;
    Vector2 position;
    Vector2 speed;
    float radius;
    Texture2D texture;  // تصویر روح
} Enemy;


// ساختار نقشه
typedef struct Map {
    int grid[MAP_ROWS][MAP_COLS]; // شبکه نقشه
    int cellSize;  // اندازه سلول
} Map;

#endif

