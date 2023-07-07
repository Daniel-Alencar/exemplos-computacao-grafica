//*****************************************************
// Detectar colisões por meio de algoritmo de detecção 
// de intersecção entre segmentos de retas do desenho.
//*****************************************************

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "Structs.h"
#include "Menu.h"
#include "Desenho.h"
#include "Collision.h"
#include "Util.h"
#include "Keyboard.h"

// Função responsável por inicializar par�metros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Pontos de desenho
	Point p1_nave = {+0.0, +1.5};
	Point p2_nave = {+1.0, -1.0};
	Point p3_nave = {-1.0, -1.0};
	pointsNave[0] = p1_nave;
	pointsNave[1] = p2_nave;
	pointsNave[2] = p3_nave;

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
	asteroid.angle = generateRandomFloat() * 360;

	asteroid.xStep = cos(convertDegreesToRadians(asteroid.angle)) * ASTEROID_VELOCITY;
	asteroid.yStep = sin(convertDegreesToRadians(asteroid.angle)) * ASTEROID_VELOCITY;
	asteroid.Tx = -range + generateRandomFloat() * (range * 2);
	asteroid.Ty = -range + generateRandomFloat() * (range * 2);

	asteroid.minX = -7.0f;
	asteroid.maxX = +7.0f;
	asteroid.minY = -7.0f;
	asteroid.maxY = +7.0f;

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
	// Translação da NAVE
	// Muda a posição quando chega na borda esquerda e direita
	if((spaceship.Tx+spaceship.maxX) > windowXmax) {
		spaceship.Tx = -range;
	} else if((spaceship.Tx+spaceship.minX) < windowXmin) {
		spaceship.Tx = +range;
	}
	// Muda a posição quando chega na borda superior e inferior
	if((spaceship.Ty+spaceship.maxY) > windowYmax) {
		spaceship.Ty = -range;
	} else if((spaceship.Ty+spaceship.minY) < windowYmin) {
		spaceship.Ty = +range;
	}

	// Translação do ASTERÓIDE
	// Muda a posição quando chega na borda esquerda e direita
	if((asteroid.Tx+asteroid.maxX) > windowXmax) {
		printf("Lado direito\n");
		asteroid.Tx = -range + asteroid.minX;
	} else if((asteroid.Tx+asteroid.minX) < windowXmin) {
		printf("Lado esquerdo\n");
		asteroid.Tx = +range + asteroid.maxX;
	}
	// Muda a posição quando chega na borda superior e inferior
	if((asteroid.Ty+asteroid.maxY) > windowYmax) {
		printf("Lado de cima\n");
		asteroid.Ty = -range + asteroid.minY;
	} else if((asteroid.Ty+asteroid.minY) < windowYmin) {
		printf("Lado de baixo\n");
		asteroid.Ty = +range + asteroid.maxY;
	}

	if(scene != SCENE_START) {
		spaceshipCollision = verifyIntersects();
		bulletColision = verifyBullet();
		
		if(bulletColision) {
			printf("Bala colidiu!\n");
		}
		if(spaceshipCollision) {
			printf("Game Over!\n");
			// Zera variáveis de translação da nave
			spaceship.Tx = 0;
			spaceship.Ty = 0;
			spaceship.xStep = 0;
			spaceship.yStep = 0;

			scene = SCENE_GAMEOVER;
		}
	}

	if(scene == SCENE_GAME || scene == SCENE_START) {
		if(bulletExists) {
			// Move a bala
			bullet.Tx += bullet.xStep;
			bullet.Ty += bullet.yStep;
		}
		if(!spaceshipCollision) {
			// Move a Nave
			spaceship.Tx += spaceship.xStep;
			spaceship.Ty += spaceship.yStep;

			// Move o Asteroid
			asteroid.Tx += asteroid.xStep;
			asteroid.Ty += asteroid.yStep;
		}
	}


	// Redesenha a Nave em outra posição
	glutPostRedisplay();

	// Parâmetros:
	// - Milliseconds: especifica o tempo em milissegundos que 
  // deve decorrer antes que a função de retorno de chamada seja chamada.
	// - Callback: é um ponteiro para a função que será chamada 
  // após o tempo especificado.
	// - Value: é um valor inteiro que é passado como argumento 
  // para a função de retorno de chamada.
	glutTimerFunc(1, Anima, 1);
}

// Programa Principal 
int main(int argc, char** argv)
{
  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowPosition(5,5);     
	glutInitWindowSize(450,450);  
	glutCreateWindow("Asteroides"); 
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);  
	
	// Registra a função callback de redimensionamento da janela de visualização 

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc(Teclado);

  // Registra a função callback que será chamada a cada intervalo de tempo
	glutTimerFunc(1, Anima, 1);

	// Chama a função responsável por fazer as inicializações 
	Inicializa(); 
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
