//*****************************************************
//
// ObjetoComTransformacoesHierarquicas.cpp
// Um programa OpenGL simples que abre uma janela GLUT, 
// desenha e permite interagir com um objeto que é 
// modelado através da utilização de transformações
// hierárquicas.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Declaração de variáveis globais
GLfloat tx = 0;
GLfloat ang1 = 0, ang2 = -90;
GLfloat win = 25;

// Função para desenhar um "braço" do objeto
void DesenhaBraco()
{
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(1.0,4.6);
		glVertex2f(1.0,-0.8);
		glVertex2f(-1.0,-0.8);
		glVertex2f(-1.0,4.6);
	glEnd();
	glPointSize(2);
	glBegin(GL_POINTS);
		glVertex2i(0,0);              
	glEnd();
}

// Função para desenhar a base do objeto           
void DesenhaBase()
{
	glLineWidth(2);
	glRectf(-0.75f,0.75f, 0.75f, -0.75f);
	glEnd();
}
           
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

	// Desenha o "chão"
	glColor3f(0.0f,0.0f,0.0f);
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-win,-3.9);
		glVertex2f(win,-3.9);
	glEnd();
                               
	// Desenha um objeto modelado com transformações hierárquicas
    
	glPushMatrix();                   
                    
	glTranslatef(tx,0.0f,0.0f);
    
	glPushMatrix();
    
	glScalef(2.5f,2.5f,1.0f);
	glColor3f(1.0f,0.0f,0.0f);
	DesenhaBase();
    
	glPopMatrix();
                    
	glTranslatef(0.0f,1.5f,0.0f);
	glRotatef(ang1,0.0f,0.0f,1.0f);    
	glScalef(1.4f,1.4f,1.0f);
	glColor3f(0.0f,1.0f,0.0f);
	DesenhaBraco();
                                    
	glTranslatef(0.4f,2.6f,0.0f);
	glRotatef(ang2,0.0f,0.0f,1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	DesenhaBraco();
                    
	glPopMatrix();    
      
	// Executa os comandos OpenGL 
	glFlush();
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
	if (largura <= altura) 
	{ 
		gluOrtho2D (-25.0f, 25.0f, -25.0f*altura/largura, 25.0f*altura/largura);
		win = 25.0f;
	}              
	else 
	{ 
		gluOrtho2D (-25.0f*largura/altura, 25.0f*largura/altura, -25.0f, 25.0f);
		win = 25.0f*largura/altura;           
	}             
}

// Função callback chamada para gerenciar eventos de teclas especiais
void TeclasEspeciais(int key, int x, int y)
{
	// Move a base
	if(key == GLUT_KEY_LEFT)
	{
		tx-=2;
		if ( tx < -win )
			tx = -win; 
	}
	if(key == GLUT_KEY_RIGHT)
	{
		tx+=2;
		if ( tx > win )
			tx = win; 
	}     

	// Rotaciona braço1
	if(key == GLUT_KEY_HOME)
		ang1-=5;
	if(key == GLUT_KEY_END)
		ang1+=5;
              
	// Rotaciona braço2
	if(key == GLUT_KEY_PAGE_UP)
		ang2-=5;
	if(key == GLUT_KEY_PAGE_DOWN)
		ang2+=5;              
                                                
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}
           
// Função responsável por inicializar par�metros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
	// Exibe mensagem que avisa como interagir
	printf(" Setas para esquerda e para direita movimentam a base (vermelha)");
	printf("\n Home e End rotacionam o braco 1 (verde)");
	printf("\n PageUP e PageDn rotacionam o braco 2 (azul)");    
}

// Programa Principal 
int main(int argc, char** argv)
{
  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowPosition(5,5);     
	glutInitWindowSize(450,300);  
	glutCreateWindow("Desenho de objeto modelado com transformacoes"); 
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);  
	
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);    

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações 
	Inicializa(); 
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
