#include <GL/glut.h>

// Pontos de desenho
#define POINTS_SPACESHIP 3
#define POINTS_ASTEROID 10

// Cenas
#define SCENE_MENU 0
#define SCENE_START 1
#define SCENE_GAME 2
#define SCENE_GAMEOVER 3

// Valores de controle
#define ASTEROID_VELOCITY 0.010f
#define ASTEROID_RANGE_ANGLES 360

#define SPACESHIP_ACCELERATION 0.001f
#define SPACESHIP_OFFSET_ANGLE 90
#define SPACESHIP_ANGLE_STEP 8

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

typedef struct node {
	Object_transformation asteroid;
	struct node *left;
	struct node *right;
} ASTEROIDS_TREE;

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

ASTEROIDS_TREE asteroids;

Object_transformation asteroid;
Object_transformation asteroid1;
Object_transformation asteroid2;
int levelDestructionAsteroid = 0;
bool notDivided = true;


Point pointsNave[POINTS_SPACESHIP];
Point pointsAsteroid[POINTS_ASTEROID];

// Variáveis de controle
bool spaceshipCollision = false;
bool bulletColision = false;
int scene = SCENE_START;

int currentColor = 0;
float redValue = 1.0f;
float greenValue = 1.0f;
float blueValue = 1.0f;
