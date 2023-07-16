//*****************************************************
// Detectar colisões por meio de algoritmo de detecção 
// de intersecção entre segmentos de retas do desenho.
//*****************************************************

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "Util.h"
#include "AsteroidsTAD.h"
#include "Menu.h"
#include "Desenho.h"
#include "Collision.h"
#include "Keyboard.h"
#include "Moves.h"

// Função responsável por inicializar par�metros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Pontos de desenho
	Point p1_nave = {+0.0, +1.5};
	Point p2_nave = {+1.0, -1.0};
	Point p3_nave = {+1.3, -2.0};
	Point p4_nave = {+1.0, -1.0};
	Point p5_nave = {-1.0, -1.0};
	Point p6_nave = {-1.3, -2.0};
	Point p7_nave = {-1.0, -1.0};

	pointsNave[0] = p1_nave;
	pointsNave[1] = p2_nave;
	pointsNave[2] = p3_nave;
	pointsNave[3] = p4_nave;
	pointsNave[4] = p5_nave;
	pointsNave[5] = p6_nave;
	pointsNave[6] = p7_nave;



	float dimension1 = 2.1875;
	float dimension2 = 4.375;

	Point p01_asteroid = {+dimension1,+dimension2};
	Point p02_asteroid = {+dimension2,+dimension1};
	Point p03_asteroid = {+dimension2,-dimension1};
	Point p04_asteroid = {+dimension1,-dimension2};

	Point p05_asteroid = {+0,-(dimension2 - dimension1)};
	Point p06_asteroid = {-dimension1,-dimension2};
	Point p07_asteroid = {-dimension2,-dimension1};

	Point p08_asteroid = {-dimension1,+0};
	Point p09_asteroid = {-dimension2,+dimension1};
	Point p10_asteroid = {-dimension1,+dimension2};

	pointsAsteroid[0] = p01_asteroid;
	pointsAsteroid[1] = p02_asteroid;
	pointsAsteroid[2] = p03_asteroid;
	pointsAsteroid[3] = p04_asteroid;
	pointsAsteroid[4] = p05_asteroid;
	pointsAsteroid[5] = p06_asteroid;
	pointsAsteroid[6] = p07_asteroid;
	pointsAsteroid[7] = p08_asteroid;
	pointsAsteroid[8] = p09_asteroid;
	pointsAsteroid[9] = p10_asteroid;

	// Variáveis da nave
	spaceship.angle = 0;
	spaceship.xStep = spaceship.yStep = 0.00f;
	spaceship.Tx = spaceship.Ty = 0.0f;

	spaceship.minX = -7.0f;
	spaceship.maxX = +7.0f;
	spaceship.minY = -7.0f;
	spaceship.maxY = +7.0f;

	// Variáveis do asteróide
	for(int i = 0; i < ASTEROIDS_ARRAY_QUANTITY; i++) {
		asteroidsArraysArray[i] = (Object_transformation*) malloc(
			sizeof(Object_transformation) * ASTEROIDS_LENGTH_ARRAY
		);
	}
	
	for(int i = 0; i < ASTEROIDS_ARRAY_QUANTITY; i++) {
		Object_transformation *asteroidsArray = asteroidsArraysArray[i];

		asteroidsArray = clearAsteroidsEnables(asteroidsArray);

		asteroidsArray[0].enable = true;
		asteroidsArray[0].angle = generateRandomFloat() * 360;

		asteroidsArray[0].xStep = cos(
			convertDegreesToRadians(asteroidsArray[0].angle)
		) * ASTEROID_VELOCITY;
		asteroidsArray[0].yStep = sin(
			convertDegreesToRadians(asteroidsArray[0].angle)
		) * ASTEROID_VELOCITY;
		asteroidsArray[0].Tx = -range + generateRandomFloat() * (range * 2);
		asteroidsArray[0].Ty = -range + generateRandomFloat() * (range * 2);

		asteroidsArray[0].minX = -7.0f;
		asteroidsArray[0].maxX = +7.0f;
		asteroidsArray[0].minY = -7.0f;
		asteroidsArray[0].maxY = +7.0f;
	}

	for(int i = 0; i < ASTEROIDS_ARRAY_QUANTITY; i++) {
		Object_transformation *asteroidsArray = asteroidsArraysArray[i];

		for(int j = 0; j < ASTEROIDS_LENGTH_ARRAY; j++) {
			int size = handleSize(j);
			asteroidsArray[j].size = size;
		}
	}

	// Variáveis da bala
	bullet.xStep = bullet.yStep = 0.00f;
	bullet.Tx = bullet.Ty = 0.0f;

	// Variáveis da tela
	windowXmin = windowYmin = -40.0f;
	windowXmax = windowYmax = +40.0f;
    
	// Exibe mensagem inicial
	printf("windowXmin: %.2f e windowXmax: %.2f\n", windowXmin, windowXmax);
	printf("windowYmin: %.2f e windowYmax: %.2f\n", windowYmin, windowYmax);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;
                   
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;
                                              
	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção
	// (esquerda, direita, inferior, superior)
	// mantendo a proporção com a janela de visualização
	if (largura <= altura) { 
		gluOrtho2D (-25.0f, 25.0f, -25.0f*altura/largura, 25.0f*altura/largura);
		win = 25.0f;
	} else { 
		gluOrtho2D (-25.0f*largura/altura, 25.0f*largura/altura, -25.0f, 25.0f);
		win = 25.0f*largura/altura;           
	}             
}

// Função callback chamada pela GLUT a cada intervalo de tempo
void Anima(int value)
{
	draw();

	// Redesenha a Nave em outra posição
	glutPostRedisplay();

	// Parâmetros:
	// - Milliseconds: especifica o tempo em milissegundos que 
  // deve decorrer antes que a função de retorno de chamada seja chamada.
	// - Callback: é um ponteiro para a função que será chamada 
  // após o tempo especificado.
	// - Value: é um valor inteiro que é passado como argumento 
  // para a função de retorno de chamada.
	glutTimerFunc(1, Anima, 0);
}

// Programa Principal 
int main(int argc, char** argv)
{
	srand(time(NULL));
	
  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowPosition(5,5);     
	glutInitWindowSize(450,450);  
	glutCreateWindow("Asteroides"); 
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);  
	
	// Registra a função callback de redimensionamento da janela de visualização


	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc(keyboardPressed);
	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardUpFunc(keyboardDespressed);
	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(specialKeyDownCallback);
	// Registra a função callback para tratamento das teclas especiais
	glutSpecialUpFunc(specialKeyUpCallback);

  // Registra a função callback que será chamada a cada intervalo de tempo
	glutTimerFunc(1, Anima, 0);

	// Chama a função responsável por fazer as inicializações 
	Inicializa(); 
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
