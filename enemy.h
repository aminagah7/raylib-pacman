#ifndef ENEMY_H
#define ENEMY_H

#include "game.h"

// مقداردهی اولیه دشمنان
void InitEnemies(Enemy enemies[MAX_ENEMIES], int count,Texture2D textures[],float SPEED);
void InitEnemiesForNewMap(Enemy enemies[], int count, Texture2D textures[], float SPEED);
// به‌روزرسانی حرکت دشمنان
void UpdateEnemies(Enemy enemies[MAX_ENEMIES], int count, const Map *map, Vector2 playerPosition,float SPEED);
void UpdateEnemies2(Enemy enemies[], int count, const Map *map ,Vector2 playerPosition,float SPEED);
// رسم دشمنان
void DrawEnemies(Enemy enemies[MAX_ENEMIES], int count);

#endif
