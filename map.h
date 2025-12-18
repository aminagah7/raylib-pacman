#ifndef MAP_H
#define MAP_H
#define APPLE 3  // مقدار میوه
#define MUSHROOM 4
#define PEPPER 5
#define CHERRY 6
#include "game.h"

// مقادیر ثابت برای نقشه
#define WALL 1  // مقدار دیوار
#define EMPTY 0 // مقدار فضای خالی
#define POINT 2 // مقدار نقطه امتیاز

// توابع مربوط به نقشه
void InitMap(Map *map);
void InitMap2(Map *map);
void InitPoints(Map *map);
void DrawMap(Map *map,Texture2D wall,Texture2D apple,Texture2D poisonousmushroom,Texture2D pepper,Texture2D cherry,Texture2D point,Texture2D point2, int frameCounter);
bool CheckCollisionWithMap(const Map *map, Vector2 position, float radius);

#endif

