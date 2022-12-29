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


GameStatus gameStatus = MAINMENU;
float skyColor = 0.0;
bool isSunSetting = true;

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

	gameTime = 0;
	skyColor = 0;
	groundBuilder = new GroundBuilder();
	player = new Player(&groundBuilder->grounds);
  
	obstacleGen = new ObstacleGenerator(&groundBuilder->grounds, gameMode, player);
	coinsGen = new CoinsGenerator(&groundBuilder->grounds, gameMode, player);
	shieldGen = new ShieldGenerator(&groundBuilder->grounds, gameMode, player);

	camera = new ThirdPersonCamera(player);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	gameStatus = PLAYING;
}

void drawString(string str, int x, int y) {
	auto uchrs = reinterpret_cast<unsigned char*>(const_cast<char*>(str.c_str()));
	
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	
	glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslated(x, y, 0);
		glScaled(0.5, 0.5, 1);
		glLineWidth(1);
		for (size_t i = 0; i < str.size(); ++i) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, (int)str[i]);
		}
	glPopMatrix();

	glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(x, y, 0);
		glScaled(0.5, 0.5, 1);
		glLineWidth(5);
		for (size_t i = 0; i < str.size(); ++i) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, (int)str[i]);
		}
	glPopMatrix();
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPopMatrix();
}


//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(fovy, ratio, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	WIDTH = w;
	HEIGHT = h;
}

//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void) {
	
	myReshape(WIDTH, HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	// Camera
	camera->draw();

	// Skycolor
	if (isSunSetting) {
		skyColor += 0.001;
		if(skyColor >= 1)
			isSunSetting = false;
	}
	else {
		skyColor -= 0.001;
		if (skyColor <= 0)
			isSunSetting = true;
	}
	GLfloat lightIntensity[] = { skyColor, skyColor, skyColor, 1.0f };
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

	glPushMatrix();
	if (gameMode == ROCK) {
		coinsGen->drawCoins();
	}
	else if (gameMode == FIRE) {
		shieldGen->drawShield();
	}
	glPopMatrix();
	
	glPushMatrix();
	obstacleGen->drawObstacles();
	glPopMatrix();

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
	glPushMatrix();
	player->draw();
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	if (gameMode == ROCK) {
		drawString("COINS", WIDTH/2 - 130, HEIGHT - 70);
		int offset = to_string(player->coins).size() * 15;
		drawString(to_string(player->coins), WIDTH/2 - 50 - offset, HEIGHT - 150);
	}
	else if (gameMode == FIRE) {
		drawString("SCORE", WIDTH / 2 - 130, HEIGHT - 70);
		int offset = to_string(gameTime).size() * 15;
		drawString(to_string(gameTime), WIDTH / 2 - 50 - offset, HEIGHT - 150);
	}
	glPopMatrix();

	glutSwapBuffers();
}

//=======================================================================
// Init Menus
//=======================================================================
void initMainMenu() {
	int color[] = { 7, 7};
	int counter = 2;
	char key;
	while (true) {
		util::changeCursor(60, 5);
		util::color(32);
		cout << "Welcome to Not Another Temple Run" << endl;

		util::changeCursor(70, 15);
		util::color(color[0]);
		cout << "Arcade Mode" << endl;

		util::changeCursor(70, 25);
		util::color(color[1]);
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
		color[0] = 7;
		color[1] = 7;
		if (counter == 1) {
			color[0] = 12;
		}
		if (counter == 2) {
			color[1] = 12;
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
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading texture files
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
}

//=======================================================================
// Timer Function
//=======================================================================
int color[] = { 7, 7, 7 };
int counter = 2;
char key;
void timerFunc(int _) {
	if (gameStatus != PLAYING) {

		util::changeCursor(60, 3);
		if (gameStatus == WON) {
			util::color(32);
			cout << "You won :)" << endl;
		}
		else {
			util::color(12);
			cout << "You lost :'(" << endl;
		}

		util::changeCursor(50, 12);
		util::color(color[0]);
		cout << "Restart in arcade" << endl;

		util::changeCursor(50, 16);
		util::color(color[1]);
		cout << "Restart in survival" << endl;

		util::changeCursor(50, 21);
		util::color(color[2]);
		cout << "Exit" << endl;

		key = _getch();

		if (key == 72 && counter > 1) {
			counter--;
		}
		if (key == 80 && counter < 3) {
			counter++;
		}
		if (key == '\r') {
			if (counter == 1) {
				gameMode = ROCK;
			}
			else if (counter == 2) {
				gameMode = FIRE;
			}
			else if(counter == 3) {
				exit(0);
			}
			myInit();
			glutShowWindow();
		}
		
		color[0] = 7;
		color[1] = 7;
		color[2] = 7;
		
		if (counter == 1)
			color[0] = 12;
		
		if (counter == 2)
			color[1] = 12;
		
		if (counter == 3)
			color[2] = 12;


		glutTimerFunc(10, timerFunc, 0);
		return;
	}
	
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

	if (player->coins >= 50) {
		glutHideWindow();
		std::cout << "\x1B[2J\x1B[H";
		gameStatus = WON;
	}
	
	glutTimerFunc(10, timerFunc, 0);
	glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y) {
	player->mouseFunc(button, state, x, y);
}

void motionFunc(int x, int y) {
	player->motionFunc(x, y);
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
	glutMouseFunc(mouseFunc);
	glutPassiveMotionFunc(motionFunc);
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