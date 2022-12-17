#pragma once

enum Direction {
    POSITIVE_X,
    NEGATIVE_X,
    POSITIVE_Z,
    NEGATIVE_Z,
};

struct GroundInfo {
    Direction dir;
    double endPos;
    double centerPos;
};

namespace util
{
    void drawCube(double size, int repeatTextures = 1);
};

