#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat tx = 0;
GLfloat ang1 = 0, ang2 = 0;
GLfloat win = 25;

void DesenhaCabeca(){
	glRectf(-1.5f, 5.0f, 1.5f, 8.0f);
	glColor3f(0.0f,0.0f,0.0f);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
		glVertex3f(-0.8f, 7.0f, 0.0f);
		glVertex3f(0.8f, 7.0f, 0.0f);
	glEnd();
	
	glBegin( GL_LINES);
	    glVertex3f(-1.0f, 6.0f, 0.0f);
	    glVertex3f(1.0f, 6.0f, 0.0f);
    glEnd();
}

void DesenhaCorpo(){
	glRectf(-3.0f, -5.0f, 3.0f, 5.0f);
	glRectf(3.0f, 5.0f, 5.0f, 3.5f);
	glRectf(-3.0f, 5.0f, -5.0f, 3.5f);
}

void DesenhaBraco(int esquerda){
	if(esquerda == 1){
		glRectf(-3.0f, 4.0f, -5.0f, -0.25f);
	}else{
		glRectf(3.0f, 4.0f, 5.0f, -0.25f);
	}
}

void DesenhaAntebraco(int esquerda){
	if(esquerda == 1){
		glRectf(-3.0f, -0.25f, -5.0f, -4.25f);
	}else{
		glRectf(3.0f, -0.25f, 5.0f, -4.25f);
	}
}

void Desenha(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-20.0f, 20.0f, -20.0f, 20.0f);
	glLineWidth(2);
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	glPushMatrix();
	glTranslatef(tx,0.0f,0.0f);
	
	glPushMatrix();
	glColor3f(1.0f,0.6f,0.0f);
	DesenhaCorpo();
	
	glColor3f(0.0f,0.0f,1.0f);
	DesenhaBraco(1);
	
	glColor3f(0.0f,1.0f,0.0f);
	DesenhaAntebraco(1);
	
	glColor3f(1.0f,1.0f,0.0f);
	DesenhaCabeca();
	
	glTranslatef(4.0f,4.0f,0.0f);
	glRotatef(ang1,0.0f,0.0f,1.0f);
	glTranslatef(-4.0f,-4.0f,0.0f);
	
	glColor3f(0.0f,0.0f,1.0f);
	DesenhaBraco(0);
	
	glTranslatef(4.0f,-0.25f,0.0f);
	glRotatef(ang2,0.0f,0.0f,1.0f);
	glTranslatef(-4.0f,0.25f,0.0f);
	
	glColor3f(0.0f,1.0f,0.0f);
	DesenhaAntebraco(0);
	
	glPopMatrix();
	
	glFlush();
}

void Inicializa(){
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
	printf("Seta para esuqeda/direita para se movimentar \n");
	printf("Seta para cima/baixo para girar o braco (azul) esquerdo\n");
	printf("PageUP/PageDown para girar o antebraco (verde) esquerdo\n");
}

void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

void Movimento(int key, int x, int y){
	// Move a base
	if(key == GLUT_KEY_LEFT)
	{
		tx-=1.0f;
		if ( tx < -win )
			tx = -win; 
	}
	if(key == GLUT_KEY_RIGHT)
	{
		tx+=1.0f;
		if ( tx > win )
			tx = win; 
	}     

	// Rotaciona braço
	if(key == GLUT_KEY_DOWN)
		ang1-=15;
	if(key == GLUT_KEY_UP)
		ang1+=15;
              
	// Rotaciona antebraço
	if(key == GLUT_KEY_PAGE_UP)
		ang2+=15;
	if(key == GLUT_KEY_PAGE_DOWN)
		ang2-=15;
				                                                           
	glutPostRedisplay();
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowPosition(5,5);     
	glutInitWindowSize(500,500);  
	glutCreateWindow("Boneco"); 
	
	glutDisplayFunc(Desenha);     
	glutSpecialFunc(Movimento);
	glutKeyboardFunc (Teclado);
	Inicializa(); 
	glutMainLoop();

	return 0;
}