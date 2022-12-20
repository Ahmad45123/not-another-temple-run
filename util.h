#pragma once

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

namespace util
{
    void drawCube(double size, int repeatTextures = 1);
    int randomNumber(int l, int r);
};

