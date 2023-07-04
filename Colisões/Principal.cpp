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
	if((Tx+maxX) > windowXmax) {
		Tx = -range;
	} else if((Tx+minX) < windowXmin) {
		Tx = +range;
	}
	// Muda a posição quando chega na borda superior e inferior
	if((Ty+maxY) > windowYmax) {
		Ty = -range;
	} else if((Ty+minY) < windowYmin) {
		Ty = +range;
	}

	// Translação do ASTERÓIDE
	// Muda a posição quando chega na borda esquerda e direita
	if((Tx_Asteroid+maxX_Asteroid) > windowXmax) {
		printf("Lado direito\n");
		Tx_Asteroid = -range + minX_Asteroid;
	} else if((Tx_Asteroid+minX_Asteroid) < windowXmin) {
		printf("Lado esquerdo\n");
		Tx_Asteroid = +range + maxX_Asteroid;
	}
	// Muda a posição quando chega na borda superior e inferior
	if((Ty_Asteroid+maxY_Asteroid) > windowYmax) {
		printf("Lado de cima\n");
		Ty_Asteroid = -range + minY_Asteroid;
	} else if((Ty_Asteroid+minY_Asteroid) < windowYmin) {
		printf("Lado de baixo\n");
		Ty_Asteroid = +range + maxY_Asteroid;
	}

	colision = verifyIntersects();
	if(!colision) {
		// Move a Nave
		Tx += xStep;
		Ty += yStep;

		// Move o Asteroid
		Tx_Asteroid += xStep_Asteroid;
		Ty_Asteroid += yStep_Asteroid;

	} else {
		printf("Com interseção!\n");
		// Zera variáveis de translação da nave
		Tx = 0;
		Ty = 0;
		xStep = 0;
		yStep = 0;
	}

	if(bullet) {
		// Move a bala
		Tx_bullet += xStep_bullet;
		Ty_bullet += yStep_bullet;
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
















// Função responsável por inicializar par�metros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);



  // Inicialização das variáveis globais
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



	xStep = yStep = 0.00f;
	Tx = Ty = 0.0f;

	xStep_Asteroid = -0.000f;
	yStep_Asteroid = +0.010f;
	Tx_Asteroid = Ty_Asteroid = 10.0f;

	xStep_bullet = yStep_bullet = 0.00f;
	Tx_bullet = Ty_bullet = 0.0f;

	minX = -7.0f;
	maxX = +7.0f;
	minY = -7.0f;
	maxY = +7.0f;

	minX_Asteroid = -7.0f;
	maxX_Asteroid = +7.0f;
	minY_Asteroid = -7.0f;
	maxY_Asteroid = +7.0f;

	windowXmin = windowYmin = -40.0f;
	windowXmax = windowYmax = +40.0f;
    
	// Exibe mensagem inicial
	printf("windowXmin: %.2f e windowXmax: %.2f\n", windowXmin, windowXmax);
	printf("windowYmin: %.2f e windowYmax: %.2f\n", windowYmin, windowYmax);
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
