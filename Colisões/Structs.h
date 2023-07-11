#include <GL/glut.h>

// Pontos de desenho
#define POINTS_SPACESHIP 3
#define POINTS_ASTEROID 10

// Cenas
#define SCENE_MENU 0
#define SCENE_START 1
#define SCENE_GAME 2
#define SCENE_GAMEOVER 3
#define SCENE_WIN 4

// Valores de controle
#define ASTEROID_VELOCITY 0.010f
#define ASTEROID_RANGE_ANGLES 360

#define SPACESHIP_ACCELERATION 0.005f
#define SPACESHIP_OFFSET_ANGLE 90
#define SPACESHIP_ANGLE_STEP 8

#define BULLET_SPEED 0.030f

typedef struct {
	float x;
	float y;
} Point;

typedef struct {
	bool enable;
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


Point pointsNave[POINTS_SPACESHIP];
Point pointsAsteroid[POINTS_ASTEROID];

// Variáveis de controle
bool spaceshipCollision = false;
bool bulletColision = false;
int scene = SCENE_START;
int lives = 3;
bool winCondition = false;

int currentColor = 0;
float redValue = 1.0f;
float greenValue = 1.0f;
float blueValue = 1.0f;

// Asteroids TAD
#define ASTEROIDS_LENGTH_ARRAY 7
Object_transformation asteroidsArray[ASTEROIDS_LENGTH_ARRAY];

void clearAsteroidsEnables() {
	for(int i = 0; i < ASTEROIDS_LENGTH_ARRAY; i++) {
		asteroidsArray[i].enable = false;
	}
}

int getLeftChildrenIndex(int asteroidIndex) {
	asteroidIndex += 1;
	return asteroidIndex * 2 - 1;
}

int getRightChildrenIndex(int asteroidIndex) {
	asteroidIndex += 1;
	return asteroidIndex * 2;
}

void divideAsteroid(int asteroidIndex) {

	int left = getLeftChildrenIndex(asteroidIndex);
	int right = getRightChildrenIndex(asteroidIndex);
	printf("Left: %d e Right: %d\n", left, right);

	// Habilitando/Desabilitando asteroides
	asteroidsArray[asteroidIndex].enable = false;

	if(left < ASTEROIDS_LENGTH_ARRAY) {
		asteroidsArray[left].enable = true;
		// Setando posições para o filho esquerdo
		asteroidsArray[left].angle = asteroidsArray[asteroidIndex].angle + 30;
		asteroidsArray[left].Tx = asteroidsArray[asteroidIndex].Tx;
		asteroidsArray[left].Ty = asteroidsArray[asteroidIndex].Ty;
		asteroidsArray[left].xStep = cos(
			convertDegreesToRadians(asteroidsArray[left].angle)
		) * ASTEROID_VELOCITY;
		asteroidsArray[left].yStep = sin(
			convertDegreesToRadians(asteroidsArray[left].angle)
		) * ASTEROID_VELOCITY;
	}

	if(right < ASTEROIDS_LENGTH_ARRAY) {
		asteroidsArray[right].enable = true;
		// Setando posições para o filho direito
		asteroidsArray[right].angle = asteroidsArray[asteroidIndex].angle - 30;
		asteroidsArray[right].Tx = asteroidsArray[asteroidIndex].Tx;
		asteroidsArray[right].Ty = asteroidsArray[asteroidIndex].Ty;
		asteroidsArray[right].xStep = cos(
			convertDegreesToRadians(asteroidsArray[right].angle)
		) * ASTEROID_VELOCITY;
		asteroidsArray[right].yStep = sin(
			convertDegreesToRadians(asteroidsArray[right].angle)
		) * ASTEROID_VELOCITY;
	}

}