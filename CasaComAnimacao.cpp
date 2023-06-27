//*****************************************************
//
// CasaComAnimacao.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e desenha uma casa que se move até "bater" em uma
// das extremidades da janela, voltando a se mover em
// outra direção.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

// Variáveis que guardam a translação que será aplicada sobre a casinha
GLfloat Tx;
GLfloat Ty;

// Variáveis que guardam os valores mínimos de x e y da casinha
GLfloat minX, maxX;
GLfloat minY, maxY;

// Variáveis que guardam o tamanho do incremento nas 
// direções x e y (número de pixels para se mover a cada intervalo de tempo)
GLfloat xStep;
GLfloat yStep;

// Variáveis que guardam a largura e altura da janela
GLfloat windowXmin, windowXmax;
GLfloat windowYmin, windowYmax;

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transformação corrente
	glLoadIdentity();

	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Aplica uma translação sobre a casinha
	glTranslatef(Tx, Ty, 0.0f);

	// Desenha uma casinha composta de um quadrado e um triângulo

	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);	
	// Desenha a casa
	glBegin(GL_QUADS);
		glVertex2f(-15.0f,-15.0f);
		glVertex2f(-15.0f,  5.0f);
		glVertex2f( 15.0f,  5.0f);
		glVertex2f( 15.0f,-15.0f);
	glEnd();

	// Altera a cor do desenho para branco
	glColor3f(1.0f, 1.0f, 1.0f);  
	// Desenha a porta e a janela  
	glBegin(GL_QUADS);
		glVertex2f(-4.0f,-14.5f);
		glVertex2f(-4.0f,  0.0f);
		glVertex2f( 4.0f,  0.0f);
		glVertex2f( 4.0f,-14.5f);
		glVertex2f( 7.0f,-5.0f);
		glVertex2f( 7.0f,-1.0f);
		glVertex2f(13.0f,-1.0f);
		glVertex2f(13.0f,-5.0f);
	glEnd();

	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);	
	// Desenha as "linhas" da janela 
	glBegin(GL_LINES);
		glVertex2f( 7.0f,-3.0f);
		glVertex2f(13.0f,-3.0f);
		glVertex2f(10.0f,-1.0f);
		glVertex2f(10.0f,-5.0f);
	glEnd();

	// Altera a cor do desenho para vermelho
	glColor3f(1.0f, 0.0f, 0.0f); 
	// Desenha o telhado
	glBegin(GL_TRIANGLES);
		glVertex2f(-15.0f, 5.0f);
		glVertex2f(  0.0f,17.0f);
		glVertex2f( 15.0f, 5.0f);
	glEnd();

	// Executa os comandos OpenGL 
	glutSwapBuffers();
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

	// Inicializa o sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, superior)
	// mantendo a proporção com a janela de visualização
	if (largura <= altura) 
	{
		gluOrtho2D (-40.0f, 40.0f, -40.0f*altura/largura, 40.0f*altura/largura);
		windowXmin = -40.0f;
		windowXmax =  40.0f;
		windowYmin = -40.0f*altura/largura;
		windowYmax = 40.0f*altura/largura;
	}
	else
	{ 
		gluOrtho2D (-40.0f*largura/altura, 40.0f*largura/altura, -40.0f, 40.0f);
		windowXmin = -40.0f*largura/altura;
		windowXmax =  40.0f*largura/altura;
		windowYmin = -40.0f;
		windowYmax =  40.0f;
	}
}

// Função callback chamada pela GLUT a cada intervalo de tempo
void Anima(int value)
{
	// Muda a direção quando chega na borda esquerda ou direita
	if( (Tx+maxX) > windowXmax || (Tx+minX) < windowXmin )
		xStep = -xStep;

	// Muda a direção quando chega na borda superior ou inferior
	if( (Ty+maxY) > windowYmax || (Ty+minY) < windowYmin )
		yStep = -yStep;

	// Move a casinha
	Tx += xStep;
	Ty += yStep;

	// Redesenha a casinha em outra posição
	glutPostRedisplay();

	// Parâmetros:
	// - milliseconds: especifica o tempo em milissegundos que 
  // deve decorrer antes que a função de retorno de chamada seja chamada.
	// - callback: é um ponteiro para a função que será chamada 
  // após o tempo especificado.
	// - value: é um valor inteiro que é passado como argumento 
  // para a função de retorno de chamada.
	glutTimerFunc(1, Anima, 1);
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Inicialização das variáveis globais
	xStep = yStep = 0.5f;
	Tx = Ty = 0.0f;
	minX = -15.0f;
	maxX =  15.0f;
	minY = -15.0f;
	maxY =  17.0f;
	windowXmin = windowYmin = -40.0f;
	windowXmax = windowYmax = 40.0f;
}

// Programa Principal 
int main(int argc, char** argv)
{
  glutInit(&argc, argv);

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Animacao de uma casa");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Registra a função callback que será chamada a cada intervalo de tempo
	glutTimerFunc(150, Anima, 1);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
