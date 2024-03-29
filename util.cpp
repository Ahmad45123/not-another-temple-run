#include "util.h"

#include <string>
#include <conio.h>
#include <Audio.h>

void util::drawCube(double size, int repeatTextures) {
    static GLfloat n[6][3] =
    {
        { -1.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0 },
        { 1.0, 0.0, 0.0 },
        { 0.0, -1.0, 0.0 },
        { 0.0, 0.0, 1.0 },
        { 0.0, 0.0, -1.0 }
    };
    static GLint faces[6][4] =
    {
        { 0, 1, 2, 3 },
        { 3, 2, 6, 7 },
        { 7, 6, 5, 4 },
        { 4, 5, 1, 0 },
        { 5, 6, 2, 1 },
        { 7, 4, 0, 3 }
    };
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--) {
        glBegin(GL_POLYGON);
        glNormal3fv(&n[i][0]);
        glTexCoord2d(0, 0);
        glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2d(0, repeatTextures);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2d(repeatTextures, repeatTextures);
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2d(repeatTextures, 0);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
int util::randomNumber(int l, int r) {
    std::uniform_int_distribution<> distr(l, r);
    return distr(gen);
}

double util::getDist(Vector pos1, Vector pos2) {
    return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) +  
        (pos1.z - pos2.z) * (pos1.z - pos2.z));
}

Audio audioManager;
extern std::string basePath;
void util::playSound(std::string path, float vol, bool loop) {
    audioManager.BasePath = basePath;
    audioManager.Play(path, vol, loop);
}

void util::color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void util::changeCursor(int x, int y) {
    COORD coordinate;

	coordinate.X = x;
	coordinate.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}
void util::showMessageBox(std::string msg) {
	MessageBox(NULL, msg.c_str(), "Message", MB_OK);
}