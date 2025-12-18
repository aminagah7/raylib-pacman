#include "raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "map.h"
#include "menu.h"
#include "game.h"

#define MENU_OPTIONS 3
#define MAP_OPTIONS 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "raylib.h"


// ذخیره رکورد همراه با تاریخ
void SaveRecord(const char *filename, const Record *record) {
    // بررسی اینکه نام خالی نباشد
    if (strlen(record->name) == 0) {
        printf("Record not saved. Name is empty.\n");
        return;
    }

    // گرفتن تاریخ و زمان فعلی
    time_t currentTime = time(NULL);
    char formattedTime[50];
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", localtime(&currentTime));

    FILE *file = fopen(filename, "a");
    if (file) {
        fprintf(file, "%s %d %s\n", record->name, record->score, formattedTime); // ذخیره فقط در صورت داشتن نام
        fclose(file);
    }
}

// بارگذاری رکوردها از فایل
int LoadRecords(const char *filename, Record records[], int maxRecords) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    int count = 0;
    while (count < maxRecords && fscanf(file, "%s %d %[^\n]", records[count].name, &records[count].score, records[count].date) == 3) {
        count++;
    }
    fclose(file);
    return count;
}

// نمایش رکوردها همراه با تاریخ
void DisplayRecords(const Record records[], int count, Font customFont) {
    DrawTextEx(customFont, "High Scores", (Vector2) {20, 5}, 70, 2, WHITE);
    DrawTextEx(customFont, "Press BACKSPACE To Back", (Vector2) {380, 550}, 35, 1, WHITE);

    for (int i = 0; i < count; i++) {
        char recordText[150];
        sprintf(recordText, "%d. %s: %d | Date: %s", i + 1, records[i].name, records[i].score, records[i].date); // اضافه کردن تاریخ به متن نمایش
        DrawTextEx(customFont, recordText, (Vector2) {20, 70 + i * 50}, 46, 1, YELLOW);
    }
}

// مرتب‌سازی رکوردها بر اساس امتیاز
int CompareScores(const void *a, const void *b) {
    Record *recordA = (Record *)a;
    Record *recordB = (Record *)b;
    return recordB->score - recordA->score; // مرتب‌سازی نزولی
}

void SortRecords(const char *filePath) {
    Record records[100];
    int count = LoadRecords(filePath, records, 100);

    qsort(records, count, sizeof(Record), CompareScores);

    FILE *file = fopen(filePath, "w");
    if (!file) return;

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %s\n", records[i].name, records[i].score, records[i].date); // تاریخ را نیز ذخیره کنید
    }
    fclose(file);
}

int InputPlayerName(char *name, int maxLen, Font customFont, Texture2D background, Music menuMusic) {
    PlayMusicStream(menuMusic); // شروع پخش موسیقی
    menuMusic.looping = true;  // حلقه‌ای شدن موسیقی
    int index = 0;
    while (!IsKeyPressed(KEY_UP) && index < maxLen - 1 && !WindowShouldClose()) {
        UpdateMusicStream(menuMusic);
        int key = GetCharPressed();
        if (key >= 32 && key <= 126) name[index++] = (char) key;
        if (IsKeyPressed(KEY_BACKSPACE) && index > 0) index--;
        if (IsKeyPressed(KEY_DOWN)) {
            StopMusicStream(menuMusic); // توقف موسیقی هنگام خروج از منو
            return 0;
        }
        name[index] = '\0';

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);
        DrawTextEx(customFont, "Enter Your Name:", (Vector2) {SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 170}, 55, 2,
                   WHITE);
        DrawTextEx(customFont, name, (Vector2) {SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 - 90}, 55, 2, YELLOW);
        DrawTextEx(customFont, "Press UP To Play", (Vector2) {20, 10}, 40, 2, WHITE);
        DrawTextEx(customFont, "Press DOWN To Back", (Vector2) {20, 60}, 40, 2, WHITE);
        EndDrawing();
    }
    StopMusicStream(menuMusic); // توقف موسیقی هنگام خروج از منو
    return 1;
}

int ShowMenu(Texture2D background, Font customFont, Music menuMusic) {
    PlayMusicStream(menuMusic); // شروع پخش موسیقی
    menuMusic.looping = true;  // حلقه‌ای شدن موسیقی
    const char *menuItems[MENU_OPTIONS] = {"Play", "Records", "Exit"};
    int selectedOption = 0;

    while (!WindowShouldClose()) {
        UpdateMusicStream(menuMusic);
        if (IsKeyPressed(KEY_DOWN)) selectedOption = (selectedOption + 1) % MENU_OPTIONS;
        if (IsKeyPressed(KEY_UP)) selectedOption = (selectedOption - 1 + MENU_OPTIONS) % MENU_OPTIONS;

        if (IsKeyPressed(KEY_ENTER)) {
            StopMusicStream(menuMusic); // توقف موسیقی هنگام خروج از منو
            return selectedOption;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);
        for (int i = 0; i < MENU_OPTIONS; i++) {
            Vector2 pos = {200, 150 + i * 50};
            if (i == selectedOption)
                DrawTextEx(customFont, TextFormat(">%s<", menuItems[i]), (Vector2) {290, 200 + i * 60}, 60, 2, YELLOW);
            else
                DrawTextEx(customFont, menuItems[i], (Vector2) {330, 200 + i * 60}, 55, 2, WHITE);
        }
        EndDrawing();
    }
    StopMusicStream(menuMusic); // توقف موسیقی هنگام خروج از منو
    return MENU_EXIT;
}
int ShowDifficulty(Texture2D background, Font customFont, Music menuMusic) {
    PlayMusicStream(menuMusic); // شروع پخش موسیقی
    menuMusic.looping = true;  // حلقه‌ای شدن موسیقی
    const char *menuItems[MENU_OPTIONS] = {"Easy", "Normal", "Hard"};
    int selectedOption = 1;

    while (!WindowShouldClose()) {
        UpdateMusicStream(menuMusic);
        if (IsKeyPressed(KEY_DOWN)) selectedOption = (selectedOption + 1) % MENU_OPTIONS;
        if (IsKeyPressed(KEY_UP)) selectedOption = (selectedOption - 1 + MENU_OPTIONS) % MENU_OPTIONS;

        if (IsKeyPressed(KEY_ENTER)) {
            StopMusicStream(menuMusic); // توقف موسیقی هنگام خروج از منو
            return selectedOption;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);
        for (int i = 0; i < MENU_OPTIONS; i++) {
            Vector2 pos = {200, 150 + i * 50};
            if (i == selectedOption)
                DrawTextEx(customFont, TextFormat(">%s<", menuItems[i]), (Vector2) {290, 200 + i * 60}, 60, 2, YELLOW);
            else
                DrawTextEx(customFont, menuItems[i], (Vector2) {330, 200 + i * 60}, 55, 2, WHITE);
        }
        EndDrawing();
    }
    StopMusicStream(menuMusic); // توقف موسیقی هنگام خروج از منو
    return MENU_EXIT;
}
int Showmap(Texture2D background, Font customFont, Music menuMusic) {
    PlayMusicStream(menuMusic); // شروع پخش موسیقی
    menuMusic.looping = true;  // حلقه‌ای شدن موسیقی
    const char *menuItems[MAP_OPTIONS] = {"MapOne", "MapTwo"};
    int selectedOption = 0;

    while (!WindowShouldClose()) {
        UpdateMusicStream(menuMusic);
        if (IsKeyPressed(KEY_DOWN)) selectedOption = (selectedOption + 1) % MAP_OPTIONS;
        if (IsKeyPressed(KEY_UP)) selectedOption = (selectedOption - 1 + MAP_OPTIONS) % MAP_OPTIONS;

        if (IsKeyPressed(KEY_RIGHT_SHIFT)) {
            StopMusicStream(menuMusic); // توقف موسیقی هنگام خروج از منو
            return selectedOption;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);
        DrawTextEx(customFont,"Press RSHIFT To Play" , (Vector2) {170,50}, 48, 2, WHITE);
        for (int i = 0; i < MAP_OPTIONS; i++) {
            Vector2 pos = {200, 150 + i * 50};
            if (i == selectedOption)
                DrawTextEx(customFont, TextFormat(">%s<", menuItems[i]), (Vector2) {250, 200 + i * 60}, 60, 2, YELLOW);
            else
                DrawTextEx(customFont, menuItems[i], (Vector2) {290, 200 + i * 60}, 55, 2, WHITE);
        }
        EndDrawing();
    }
    StopMusicStream(menuMusic); // توقف موسیقی هنگام خروج از منو
    return MENU_EXIT;
}


