#pragma once

#include <random>
#include <Windows.h>
#include <Vector.h>
#include <string>
#include <glut.h>

enum Direction {
    POSITIVE_X,
    NEGATIVE_X,
    POSITIVE_Z,
    NEGATIVE_Z,
    UNKNOWN
};

struct GroundInfo {
    Direction dir;
    double endPos;
    double centerPos;
};

enum Gamemode {
    FIRE,
    ROCK
};

enum GameStatus {
    MAINMENU,
    WON,
    LOST,
    PLAYING,
};

namespace util
{
    void drawCube(double size, int repeatTextures = 1);
    int randomNumber(int l, int r);
    double getDist(Vector pos1, Vector pos2);
    void playSound(std::string path, float vol = 1, bool loop = false);
    void color(int color);
    void changeCursor(int x, int y);
};

