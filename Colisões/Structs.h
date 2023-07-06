#include <GL/glut.h>

#define POINTS_SPACESHIP 3
#define POINTS_ASTEROID 10

#define SCENE_MENU 0
#define SCENE_START 1
#define SCENE_GAME 2

typedef struct {
	float x;
	float y;
} Point;

typedef struct {
	GLfloat angle;
	GLfloat Tx, Ty;
	GLfloat xStep, yStep;
	GLfloat minX, minY, maxX, maxY;

} Object_transformation;

// Variáveis de controle de tela

// Variáveis relacionadas a janela de visualização
GLfloat tx = 0;
GLfloat win = 25;
int range = 25;
// Variáveis que guardam a largura e altura da janela
GLfloat windowXmin, windowXmax;
GLfloat windowYmin, windowYmax;

// Controle de objetos na tela
bool bulletExists = false;
Object_transformation bullet;
Object_transformation spaceship;
Object_transformation asteroid;

Point pointsNave[POINTS_SPACESHIP];
Point pointsAsteroid[POINTS_ASTEROID];

// Variáveis de controle
bool colisionExists = false;
int scene = SCENE_START;

int currentColor = 0;
float redValue = 1.0f;
float greenValue = 1.0f;
float blueValue = 1.0f;
