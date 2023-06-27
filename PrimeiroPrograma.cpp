//*****************************************************
//
// PrimeiroPrograma.cpp
// Um programa OpenGL simples que abre uma janela GLUT
// e desenha um tri�ngulo no centro
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor branca
	glClearColor(1,1,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Define a cor de desenho: vermelho
	glColor3f(1,0,0);
	
	// Desenha um tri�ngulo no centro da janela
	glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho (vértice inferior esquerdo)
    glVertex2f(-0.5f, -0.5f);

    glColor3f(0.0f, 1.0f, 0.0f); // Verde (vértice inferior direito)
    glVertex2f(0.5f, -0.5f);

    glColor3f(0.0f, 0.0f, 1.0f); // Azul (vértice superior)
    glVertex2f(0.0f, 0.5f);
	glEnd();
	
	//Executa os comandos OpenGL 
	glFlush();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 81 || key == 113)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
	// Define a janela de visualiza��o 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal 
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(300,200); 
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Primeiro Programa");
 
	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc(Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();
 
	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();
 
	return 0;
}
