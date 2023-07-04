#include <GL/glut.h>

typedef struct {
	float x;
	float y;
} Point;

int scene = 0;

GLfloat tx = 0;
GLfloat win = 25;

// Declaração de variáveis globais
GLfloat angle = 0;

// Variáveis que guardam a translação que será aplicada sobre a nave
GLfloat Tx;
GLfloat Ty;
// Variáveis que guardam a translação que será aplicada sobre o asteróide
GLfloat Tx_Asteroid;
GLfloat Ty_Asteroid;
// Variáveis que guardam a translação do tiro
bool bullet = false;
GLfloat Tx_bullet;
GLfloat Ty_bullet;

// Variáveis que guardam os valores mínimos de x e y da nave
GLfloat minX, maxX;
GLfloat minY, maxY;
// Variáveis que guardam os valores mínimos de x e y do asteróide
GLfloat minX_Asteroid, maxX_Asteroid;
GLfloat minY_Asteroid, maxY_Asteroid;

// Variáveis que guardam o tamanho do incremento nas 
// direções x e y (número de pixels para se mover a cada intervalo de tempo)
GLfloat xStep;
GLfloat yStep;

GLfloat xStep_Asteroid;
GLfloat yStep_Asteroid;

GLfloat xStep_bullet;
GLfloat yStep_bullet;

// Variáveis que guardam a largura e altura da janela
GLfloat windowXmin, windowXmax;
GLfloat windowYmin, windowYmax;

// Variáveis de referência do plano cartesiano
int range = 25;
bool colision = false;

Point pointsNave[3];
Point pointsAsteroid[10];
