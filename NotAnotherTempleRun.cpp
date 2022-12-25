#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"

#include "Vector.h"
#include "GroundBuilder.h"
#include "Player.h"
#include "ObstacleGenerator.h"
#include "CoinsGenerator.h"
#include "ShieldGenerator.h"




#include <iostream>
#include <conio.h>
#include <glut.h>
#include <FreeCamera.h>
#include <PlayerCamera.h>
#include <ThirdPersonCamera.h>

using namespace std;

int WIDTH = 1280;
int HEIGHT = 720;

GLuint tex;
char title[] = "Not Another Temple Run";
Gamemode gameMode;

std::string basePath;
int gameTime = 0;

// 3D Projection Optionsk
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.01;
GLdouble zFar = 1000;

// Cameras
Camera *camera;

// Objects
GroundBuilder* groundBuilder;
Player* player;
ObstacleGenerator* obstacleGen;
CoinsGenerator* coinsGen;
ShieldGenerator* shieldGen;



//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	InitLightSource();
	InitMaterial();

	groundBuilder = new GroundBuilder();
	player = new Player(&groundBuilder->grounds);
  
	obstacleGen = new ObstacleGenerator(&groundBuilder->grounds, gameMode, player);
	coinsGen = new CoinsGenerator(&groundBuilder->grounds, gameMode, player);
	shieldGen = new ShieldGenerator(&groundBuilder->grounds, gameMode, player);

	camera = new ThirdPersonCamera(player);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

void drawString(string str, float x, float z) {
	glPushMatrix();
	glRasterPos3f(x, 0.14, z);
	for (size_t i = 0; i < str.size(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)str[i]);
	}
	glPopMatrix();
}

//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera->draw();

	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	groundBuilder->reset();
	groundBuilder->drawForward();
	groundBuilder->drawForward();
	groundBuilder->drawRight();
	groundBuilder->drawForward();
	groundBuilder->drawRight();
	groundBuilder->drawForward();
	groundBuilder->drawLeft();
	groundBuilder->drawForward();
	groundBuilder->drawRight();
	groundBuilder->drawForward();
	groundBuilder->drawRight();
	groundBuilder->drawForward();
	groundBuilder->drawForward();
	groundBuilder->drawForward();
	groundBuilder->drawRight();
	groundBuilder->drawForward();
	groundBuilder->isFillGrounds = false;

	if (gameMode == ROCK) {
		coinsGen->drawCoins();
	}
	else if (gameMode == FIRE) {
		shieldGen->drawShield();
	}
	obstacleGen->drawObstacles();

	//sky box
	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 200, 100, 100);
	gluDeleteQuadric(qobj);
	glPopMatrix();

	// Draw player
	player->draw();

	glPushMatrix();
	if (gameMode == ROCK) {
		drawString("Coins Collected " + to_string(player->coins), player->playerModel.pos.x - 0.02, player->playerModel.pos.z);
	}
	else if (gameMode == FIRE) {
		drawString("Score " + to_string(gameTime), player->playerModel.pos.x - 0.02, player->playerModel.pos.z);
	}
	glPopMatrix();

	glutSwapBuffers();
}

void initMainMenu() {
	int set[] = { 7, 7};
	int counter = 2;
	char key;
	while (true) {
		util::changeCursor(60, 5);
		util::color(32);
		cout << "Welcome to Not Another Temple Run" << endl;

		util::changeCursor(70, 15);
		util::color(set[0]);
		cout << "Arcade Mode" << endl;

		util::changeCursor(70, 25);
		util::color(set[1]);
		cout << "Survival Mode" << endl;

		key = _getch();

		if (key == 72 && counter == 2) {
			counter--;
		}
		if (key == 80 && counter == 1) {
			counter++;
		}
		if (key == '\r') {
			if (counter == 1) {
				gameMode = ROCK;
				break;
			}
			else if (counter == 2) {
				gameMode = FIRE;
				break;
			}
		}
		set[0] = 7;
		set[1] = 7;
		if (counter == 1) {
			set[0] = 12;
		}
		if (counter == 2) {
			set[1] = 12;
		}
	}
}

//=======================================================================
// Keyboard Function
//=======================================================================
void keyDown(unsigned char button, int x, int y) {
	if (button == '1') {
		camera = new ThirdPersonCamera(player);
	}
	else if (button == '2') {
		camera = new PlayerCamera(player);
	}
	else if (button == '3') {
		camera = new FreeCamera();
	}

	camera->keyDown(button);
	player->keyDown(button);
}
void keyUp(unsigned char button, int x, int y) {
	camera->keyUp(button);
	player->keyUp(button);
}
void specialKeyDown(int button, int x, int y) {
	camera->specialKeyDown(button);
	player->specialKeyDown(button);
}
void specialKeyUp(int button, int x, int y) {
	camera->specialKeyUp(button);
	player->specialKeyUp(button);
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}
	
	WIDTH = w;
	HEIGHT = h;
	
	// set the drawable region of the window
	glViewport(0, 0, w, h);
	
	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);
	
	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	
	// Loading texture files
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
}

//=======================================================================
// Timer Function
//=======================================================================
void timerFunc(int _) {
	camera->tick();
	if (groundBuilder->grounds.size() > 0) {
		player->tick();
		if (obstacleGen->obstacles.size() == 0) obstacleGen->generateObstacles();
		if (coinsGen->coins.size() == 0 && gameMode == ROCK) coinsGen->generateCoins();
		if (shieldGen->shields.size() == 0 && gameMode == FIRE) shieldGen->generateShield();
	}
	obstacleGen->tick();
	if (gameMode == ROCK) {
		coinsGen->tick();
	}
	else if (gameMode == FIRE) {
		shieldGen->tick();
	}
	gameTime++;
	glutTimerFunc(10, timerFunc, 0);
	glutPostRedisplay();
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);
	glutTimerFunc(0, timerFunc, 0);

	glutReshapeFunc(myReshape);

	initMainMenu();

	LoadAssets();
	myInit();
	
	string tmp = argv[0];
	tmp = tmp.substr(0, tmp.find_last_of("\\/"));
	basePath = tmp.substr(0, tmp.find_last_of("\\/"));
	util::playSound("sounds/music.wav", 2, true);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}