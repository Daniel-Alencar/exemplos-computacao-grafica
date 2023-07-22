#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

float win, aspecto;
int largura, altura;

// Variáveis de referência do plano cartesiano
int range = 10;

void PontosDeReferencia() {
	glClear(GL_COLOR_BUFFER_BIT);
    
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(10.0f);
  glBegin(GL_POINTS);
    
    // Desenha pontos de referência
		// Meio
    glVertex2f(0.0f, 0.0f);

		// Right and Left
    glVertex2f(+range, 0.0f);
    glVertex2f(-range, 0.0f);

		// Top and Down
    glVertex2f(0.0f, +range);
    glVertex2f(0.0f, -range);
    
  glEnd();
}

void DesenhaAsteroide() {
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (-7, 7, -7, 7);

	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(+3.5,+7);
		glVertex2f(+7,+3.5);

		glVertex2f(+7,-3.5);
		glVertex2f(+3.5,-7);

		glVertex2f(+0,-5);

		glVertex2f(-3.5,-7);
		glVertex2f(-7,-3.5);
		
		glVertex2f(-3.5,+0);
		
		glVertex2f(-7,+3.5);
		glVertex2f(-3.5,+7);
	glEnd();
	glPointSize(1);
	glBegin(GL_POINTS);
		glVertex2i(0,0);      
	glEnd();

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (-range, range, -range, range);
}

// Fun��o que coloca uma linha ao redor da �rea da window
void FazMoldura()
{
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-win*aspecto,-win);   
		glVertex2f(-win*aspecto, win);    
		glVertex2f( win*aspecto, win); 
		glVertex2f( win*aspecto,-win);                    
	glEnd();
	glLineWidth(1);                           
}

void Desenha(void) {
	printf("Largura da tela: %d\n", largura);
	printf("Altura da tela: %d\n", altura);

	printf("Valores limites do desenho: %f e %f\n", win*aspecto, win);

	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
  glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0, 0, largura, altura);
	PontosDeReferencia();
	DesenhaAsteroide();

	// Executa os comandos OpenGL
  glFlush();
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;
	
	// Atualiza as vari�veis
	largura = w;
	altura = h;

	aspecto = (float) largura/altura;	
	
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Estabelece a janela de sele��o:
	// (esquerda, direita, inferior, superior)
	// mantendo a propor��o com a janela de visualiza��o
	gluOrtho2D (-range, range, -range, range);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if(key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	win = 50.0f;
}


// Programa Principal 
int main(int argc, char** argv)
{
  glutInit(&argc, argv);

	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 
	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5); 
    
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Desenho do asteroide");
 
	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);
  
	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc(Teclado);
    
	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();
 
	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();
 
	return 0;
}
