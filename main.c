#include "raylib.h"
#include "map.h"
#include "pacman.h"
#include "enemy.h"
#include "menu.h"
#include "string.h"
#include "game.h"
#include "stdlib.h"
#define RECORDS_FILE "resources/records.txt"
#define MAX_RECORDS 10
#define MAX_PLAYER_NAME_LENGTH 50
#define EASYSpeed 1.3f
#define NormalSpeed 1.5f
#define HARDSpeed 1.7f
#define MAX_HARDENEMIES 7
int main() {
    int temp = 0;
    int random;
    int frameCounter=0;
    // --- لود منابع ---
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pacman Game");
    InitAudioDevice();
    SetTargetFPS(120);

    // منابع گرافیکی
    Texture2D backgroundMenu = LoadTexture("resources/background.png");
    Texture2D backgroundRecord = LoadTexture("resources/tokyorecord3.png");
    Texture2D backgroundGameOver = LoadTexture("resources/tokyocyber5.png");
    //enemy
    Texture2D ghostTexture = LoadTexture("resources/colored_ghosts.png");  // تصویر روح
    Texture2D ghostTexture1 = LoadTexture("resources/colored_ghosts2.png");
    Texture2D ghostTexture2 = LoadTexture("resources/colored_ghosts3.png");
    Texture2D ghostTexture3 = LoadTexture("resources/colored_ghosts4.png");
    Texture2D ghostTexture4 = LoadTexture("resources/colored_ghosts5.png");
    Texture2D ghostTexture5 = LoadTexture("resources/colored_ghosts6.png");
    Texture2D ghostTexture6 = LoadTexture("resources/colored_ghosts7.png");
    //pacman
    Texture2D live = LoadTexture("resources/live.png");
    //map
    Texture2D wall = LoadTexture("resources/wall.png");
    Texture2D apple = LoadTexture("resources/apple.png");
    Texture2D poisonousmushroom = LoadTexture("resources/poisonous mushroom.png");
    Texture2D pepper = LoadTexture("resources/pepper.png");
    Texture2D cherry = LoadTexture("resources/cherry.png");
    Texture2D point = LoadTexture("resources/british.png");
    Texture2D point2 = LoadTexture("resources/british2.png");
    // فونت‌ها
    Font customFontMenu = LoadFont("resources/LoveGlitch.ttf");
    Font customFontRecords = LoadFont("resources/RussoOne-Regular.ttf");
    Font customFontNAME = LoadFont("resources/Montserrat/Russo_One/RussoOne-Regular.ttf");
    //sound
    Sound credit = LoadSound("resources/resources_Audio_credit.wav");
    Sound munch = LoadSound("resources/resources_Audio_munch_2.wav");
    Sound collisionSound = LoadSound("resources/collisionSound.mp3");
    Sound death = LoadSound("resources/resources_Audio_death (2).mp3");
    // --- بارگذاری آهنگ ---
    //Music menuMusic = LoadMusicStream("C:/Users/ASUS/CLionProjects/resources of pacman/resources_Audio_take_on_me_small (mp3cut.net).mp3");
    Music menuMusic = LoadMusicStream("resources/resources_Audio_take_on_me_small (mp3cut.net) (1).mp3");
    Texture2D enemyTextures[5] = {ghostTexture, ghostTexture1, ghostTexture2, ghostTexture3, ghostTexture4};
    Texture2D enemyTexturesHard[7] = {ghostTexture, ghostTexture1, ghostTexture2, ghostTexture3, ghostTexture4,ghostTexture5,ghostTexture6};
    while (!WindowShouldClose()) {

        int menuChoice = ShowMenu(backgroundMenu, customFontRecords, menuMusic);
        if (menuChoice == MENU_RECORDS) {
            Record records[MAX_RECORDS];
            int recordCount = LoadRecords(RECORDS_FILE, records, MAX_RECORDS);
            PlayMusicStream(menuMusic);// شروع پخش موسیقی
            menuMusic.looping = true;  // حلقه‌ای شدن موسیقی
            while (!IsKeyPressed(KEY_BACKSPACE) && !WindowShouldClose()) { // بازگشت به منو با BACKSPACE
                UpdateMusicStream(menuMusic);
                BeginDrawing();
                ClearBackground(BLACK);
                DrawTexture(backgroundRecord, 0, 0, WHITE);
                DisplayRecords(records, recordCount, customFontRecords);
                EndDrawing();
            }
            StopMusicStream(menuMusic); // توقف موسیقی هنگام خروج از منو
        } else if (menuChoice == MENU_PLAY) {
            char playerName[MAX_PLAYER_NAME_LENGTH];
            int back = InputPlayerName(playerName, MAX_PLAYER_NAME_LENGTH, customFontNAME, backgroundMenu,menuMusic);

            if (back == 0) {
                continue;
            }
            // --- تنظیمات اولیه بازی ---
            int Difficulty = ShowDifficulty(backgroundMenu, customFontRecords, menuMusic);
            random = Showmap(backgroundMenu, customFontRecords, menuMusic);
            Pacman pacman;
            Enemy enemies[MAX_ENEMIES];
            Enemy enemiesHard[MAX_HARDENEMIES];
            Map map;
            if (random == 0) {
                InitMap(&map);
                if (Difficulty == Easy) {
                    InitPacman(&pacman);
                    InitEnemies(enemies, MAX_ENEMIES, enemyTextures, EASYSpeed);
                    pacman.HP = 4;
                } else if (Difficulty == Normal) {
                    InitPacman(&pacman);
                    InitEnemies(enemies, MAX_ENEMIES, enemyTextures, NormalSpeed);
                    pacman.HP = 3;
                } else if (Difficulty == Hard) {
                    InitPacman(&pacman);
                    InitEnemies(enemiesHard, MAX_HARDENEMIES, enemyTexturesHard, HARDSpeed);
                    pacman.HP = 2;
                }
            } else if (random == 1) {
                InitMap2(&map);
                if (Difficulty == Easy) {
                    InitPacman(&pacman);
                    InitEnemiesForNewMap(enemies, MAX_ENEMIES, enemyTextures, EASYSpeed);
                    pacman.HP = 4;
                } else if (Difficulty == Normal) {
                    InitPacman(&pacman);
                    InitEnemiesForNewMap(enemies, MAX_ENEMIES, enemyTextures, NormalSpeed);
                    pacman.HP = 3;
                } else if (Difficulty == Hard) {
                    InitPacman(&pacman);
                    InitEnemiesForNewMap(enemiesHard, MAX_HARDENEMIES, enemyTexturesHard, HARDSpeed);
                    pacman.HP = 2;
                }
            }

            bool gameOver = false;
            PlayMusicStream(menuMusic); // شروع پخش موسیقی
            menuMusic.looping = true;  // حلقه‌ای شدن موسیقی
            while (!IsKeyPressed(KEY_BACKSPACE) && !WindowShouldClose()) {

                if (!gameOver) {
                    UpdateMusicStream(menuMusic);
                    // بروزرسانی بازی
                    UpdatePacman(&pacman, &map, munch, credit,random);
                    if (random == 0) {
                        if (Difficulty == Easy)
                            UpdateEnemies(enemies, MAX_ENEMIES, &map, pacman.position, EASYSpeed);
                        else if (Difficulty == Normal)
                            UpdateEnemies(enemies, MAX_ENEMIES, &map, pacman.position, NormalSpeed);
                        else if (Difficulty == Hard)
                            UpdateEnemies(enemiesHard, MAX_HARDENEMIES, &map, pacman.position, HARDSpeed);
                    } else if (random == 1) {
                        if (Difficulty == Easy)
                            UpdateEnemies2(enemies, MAX_ENEMIES, &map, pacman.position, EASYSpeed);
                        else if (Difficulty == Normal)
                            UpdateEnemies2(enemies, MAX_ENEMIES, &map, pacman.position, NormalSpeed);
                        else if (Difficulty == Hard)
                            UpdateEnemies2(enemiesHard, MAX_HARDENEMIES, &map, pacman.position, HARDSpeed);
                    }
                    temp = 0;
                    if (Difficulty == Hard) {
                        // بررسی برخوردها
                        for (int i = 0; i < MAX_HARDENEMIES; i++) {
                            if (CheckCollisionCircles(pacman.position, pacman.radius, enemiesHard[i].position,
                                                      enemiesHard[i].radius)) {
                                if (pacman.invincibleTimer == 0 && pacman.soulٍEater == 0) {
                                    if (pacman.HP > 1) {
                                        PlaySound(collisionSound);
                                    }
                                    pacman.HP--;
                                    pacman.invincibleTimer = 160; // بازه زمانی برای حالت بی‌اثر
                                    if (pacman.HP == 0) gameOver = true;
                                } else if (pacman.soulٍEater > 0) {
                                    enemiesHard[i].invincibleTimer = 600; // دشمن بی‌اثر می‌شود
                                }
                            }
                            if (pacman.invincibleTimer == 0) {
                                if (pacman.HP == 0) {
                                    gameOver = true;  // پایان بازی
                                }
                            }

                        }
                    } else {
                        // بررسی برخوردها
                        for (int i = 0; i < MAX_ENEMIES; i++) {
                            if (CheckCollisionCircles(pacman.position, pacman.radius, enemies[i].position,
                                                      enemies[i].radius)) {
                                if (pacman.invincibleTimer == 0 && pacman.soulٍEater == 0) {
                                    if (pacman.HP > 1) {
                                        PlaySound(collisionSound);
                                    }
                                    pacman.HP--;
                                    pacman.invincibleTimer = 160; // بازه زمانی برای حالت بی‌اثر
                                    if (pacman.HP == 0) gameOver = true;
                                } else if (pacman.soulٍEater > 0) {
                                    enemies[i].invincibleTimer = 600; // دشمن بی‌اثر می‌شود
                                }
                            }
                            if (pacman.invincibleTimer == 0) {
                                if (pacman.HP == 0) {
                                    gameOver = true;  // پایان بازی
                                }
                            }

                        }
                    }
                }

                // --- رسم ---
                BeginDrawing();
                ClearBackground(BLACK);

                if (!gameOver) {
                    frameCounter++;
                    DrawMap(&map, wall, apple, poisonousmushroom, pepper, cherry, point,point2,frameCounter);
                    DrawPacman(&pacman, customFontRecords, live);
                    if (Difficulty == Hard)
                        DrawEnemies(enemiesHard, MAX_HARDENEMIES);
                    else
                        DrawEnemies(enemies, MAX_ENEMIES);
                } else {
                    // ذخیره رکورد پس از باخت
                    if (temp == 0) {
                        StopMusicStream(menuMusic); // توقف موسیقی هنگام خروج از منو
                        PlaySound(death);
                        Record record;
                        record.score = pacman.score;
                        strcpy(record.name, playerName);
                        SaveRecord(RECORDS_FILE, &record);
                        SortRecords(RECORDS_FILE);
                        temp = 1;
                    }
                    // نمایش صفحه گیم‌اور
                    DrawTexture(backgroundGameOver, 0, 0, WHITE);
                    DrawTextEx(customFontRecords, "Game Over!", (Vector2) {285, 40}, 35, 2, WHITE);
                    DrawTextEx(customFontRecords, "Press UP To Restart", (Vector2) {220, 370}, 30, 2, WHITE);
                    DrawTextEx(customFontRecords, "Press DOWN To Show Menu", (Vector2) {220, 420}, 30, 2, WHITE);
                    //DrawText(TextFormat("Score: %d", pacman.score),SCREEN_WIDTH / 2 - 25,SCREEN_HEIGHT / 20,35, WHITE);
                    DrawTextEx(customFontRecords, TextFormat("Score: %d", pacman.score), (Vector2) {310, 120}, 35, 2,
                               WHITE);
                    DrawTextEx(customFontRecords, TextFormat("%s", playerName), (Vector2) {310, 80}, 35, 2, WHITE);
                    // مدیریت کلیدهای گیم‌اور
                    if (IsKeyPressed(KEY_UP)) {
                        PlayMusicStream(menuMusic); // شروع پخش موسیقی
                        menuMusic.looping = true;  // حلقه‌ای شدن موسیقی
                        if (random == 0) {
                            InitMap(&map);
                            if (Difficulty == Easy) {
                                InitPacman(&pacman);
                                InitEnemies(enemies, MAX_ENEMIES, enemyTextures, EASYSpeed);
                                pacman.HP = 4;
                            } else if (Difficulty == Normal) {
                                InitPacman(&pacman);
                                InitEnemies(enemies, MAX_ENEMIES, enemyTextures, NormalSpeed);
                                pacman.HP = 3;
                            } else if (Difficulty == Hard) {
                                InitPacman(&pacman);
                                InitEnemies(enemiesHard, MAX_HARDENEMIES, enemyTexturesHard, HARDSpeed);
                                pacman.HP = 2;
                            }
                        } else if (random == 1) {
                            InitMap2(&map);
                            if (Difficulty == Easy) {
                                InitPacman(&pacman);
                                InitEnemiesForNewMap(enemies, MAX_ENEMIES, enemyTextures, EASYSpeed);
                                pacman.HP = 4;
                            } else if (Difficulty == Normal) {
                                InitPacman(&pacman);
                                InitEnemiesForNewMap(enemies, MAX_ENEMIES, enemyTextures, NormalSpeed);
                                pacman.HP = 3;
                            } else if (Difficulty == Hard) {
                                InitPacman(&pacman);
                                InitEnemiesForNewMap(enemiesHard, MAX_HARDENEMIES, enemyTexturesHard, HARDSpeed);
                                pacman.HP = 2;
                            }
                        }

                        gameOver = false;
                    } else if (IsKeyPressed(KEY_DOWN)) {
                        break; // بازگشت به منو
                    }
                }

                EndDrawing();
            }
        } else if (menuChoice == MENU_EXIT) {
            break; // خروج از حلقه اصلی
        }
    }

    // --- آزادسازی منابع ---
    UnloadTexture(backgroundMenu);
    UnloadTexture(backgroundRecord);
    UnloadTexture(backgroundGameOver);
    UnloadFont(customFontMenu);
    UnloadFont(customFontRecords);
    UnloadFont(customFontNAME);
    //enemy
    UnloadTexture(ghostTexture);
    UnloadTexture(ghostTexture1);
    UnloadTexture(ghostTexture2);
    UnloadTexture(ghostTexture3);
    UnloadTexture(ghostTexture4);
    //pacman
    UnloadTexture(live);
    //map wall, apple,poisonousmushroom,pepper,cherry, point
    UnloadTexture(wall);
    UnloadTexture(apple);
    UnloadTexture(poisonousmushroom);
    UnloadTexture(pepper);
    UnloadTexture(cherry);
    UnloadTexture(point);
    //UnloadSound(play);
    UnloadSound(credit);
    UnloadSound(munch);
    UnloadSound(collisionSound); // آزادسازی صدای برخورد
    UnloadSound(death);
    //music

    UnloadMusicStream(menuMusic);
    CloseAudioDevice();          // بستن دستگاه صوتی

    CloseWindow();
    SortRecords(RECORDS_FILE);
    return 0;
}




