#ifndef PACMAN_H
#define PACMAN_H

#include "raylib.h"
#include "map.h"

// توابع مربوط به پکمن
void InitPacman(Pacman *pacman);
void UpdatePacman(Pacman *pacman, Map *map,Sound munch,Sound credit,int random);  // نوع ورودی Map هماهنگ شود
void DrawPacman( Pacman *pacman,Font customFontRecords,Texture2D live);

#endif



