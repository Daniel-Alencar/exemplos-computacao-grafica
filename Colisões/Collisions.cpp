//*****************************************************
// Detectar colisões por meio de algoritmo de detecção 
// de intersecção entre segmentos de retas do desenho.
//*****************************************************

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} Point;

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

// Variáveis que guardam a largura e altura da janela
GLfloat windowXmin, windowXmax;
GLfloat windowYmin, windowYmax;

// Variáveis de referência do plano cartesiano
int range = 25;
bool colision = false;

Point pointsNave[3];
Point pointsAsteroid[10];






// Função para desenhar uma nave
void DesenhaNave()
{
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(pointsNave[0].x, pointsNave[0].y);
		glVertex2f(pointsNave[1].x, pointsNave[1].y);
		glVertex2f(pointsNave[2].x, pointsNave[2].y);
	glEnd();
	glPointSize(1);
	glBegin(GL_POINTS);
		glVertex2i(0,0);      
	glEnd();
}

// Função para desenhar um asteróide
void DesenhaAsteroide() {
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(pointsAsteroid[0].x, pointsAsteroid[0].y);
		glVertex2f(pointsAsteroid[1].x, pointsAsteroid[1].y);
		glVertex2f(pointsAsteroid[2].x, pointsAsteroid[2].y);
		glVertex2f(pointsAsteroid[3].x, pointsAsteroid[3].y);
		glVertex2f(pointsAsteroid[4].x, pointsAsteroid[4].y);
		glVertex2f(pointsAsteroid[5].x, pointsAsteroid[5].y);
		glVertex2f(pointsAsteroid[6].x, pointsAsteroid[6].y);
		glVertex2f(pointsAsteroid[7].x, pointsAsteroid[7].y);
		glVertex2f(pointsAsteroid[8].x, pointsAsteroid[8].y);
		glVertex2f(pointsAsteroid[9].x, pointsAsteroid[9].y);
	glEnd();
	glPointSize(1);
	glBegin(GL_POINTS);
		glVertex2i(0,0);      
	glEnd();
}

void DesenhaPontosDeReferencia() {
	glClear(GL_COLOR_BUFFER_BIT);
    
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







int orientation(Point p, Point q, Point r) {
	float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (val == 0) {
		// Os pontos são colineares
		return 0;
	} else if (val > 0) {
		// Sentido horário
		return 1;
	} else {
		// Sentido anti-horário
		return 2;
	}
}

int onSegment(Point p, Point q, Point r) {
	if (q.x <= fmax(p.x, r.x) && q.x >= fmin(p.x, r.x) &&
			q.y <= fmax(p.y, r.y) && q.y >= fmin(p.y, r.y)) {
		// q está no segmento pr
		return 1;
	}
	return 0;
}

int doIntersect(Point p1, Point q1, Point p2, Point q2) {
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// Caso geral
	if (o1 != o2 && o3 != o4) {
		// As linhas se intersectam
		return 1;
	}

	// Casos especiais
	if (o1 == 0 && onSegment(p1, p2, q1)) {
		// p2 está em p1q1
		return 1;
	}
	if (o2 == 0 && onSegment(p1, q2, q1)) {
		// q2 está em p1q1
		return 1;
	}
	if (o3 == 0 && onSegment(p2, p1, q2)) {
		// p1 está em p2q2
		return 1;
	}
	if (o4 == 0 && onSegment(p2, q1, q2)) {
		// q1 está em p2q2
		return 1;
	}

	// As linhas não se intersectam
	return 0;
}

bool detectColision(GLfloat x1, GLfloat y1, GLfloat r1,
										 GLfloat x2,GLfloat y2,GLfloat r2) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	float distance = std::sqrt(dx*dx + dy*dy);

	if (distance > r1 + r2) {
		// Circulos são disjuntos
		return false;
	}

	if (distance < std::abs(r1 - r2)) {
		// Um círculo está contido dentro de outro
		return false;
	}

	if (distance == 0 && r1 == r2) {
		// Os círculos são idênticos
		return true;
	}

	// Os círculos se intersectam
	return true;
}

bool verifyIntersects() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 10; j++) {
			Point nave_point1 = { 
				pointsNave[i].x + Tx, pointsNave[i].y + Ty 
			};
			Point nave_point2 = { 
				pointsNave[(i+1)%3].x + Tx, pointsNave[(i+1)%3].y + Ty 
			};
			Point asteroid_point1 = { 
				pointsAsteroid[j].x + Tx_Asteroid, pointsAsteroid[j].y + Ty_Asteroid 
			};
			Point asteroid_point2 = { 
				pointsAsteroid[(j+1)%10].x + Tx_Asteroid, 
				pointsAsteroid[(j+1)%10].y + Ty_Asteroid 
			};

			if(doIntersect(
				nave_point1, nave_point2,
				asteroid_point1, asteroid_point2
			)) {
				return true;
			}
		}
	}
	return false;
}






// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Limpa a janela de visualização com a cor de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);



	// Inicializa a matriz de transformação corrente
	glLoadIdentity();
	gluOrtho2D(-range, range, -range, range);

	glColor3f(1.0f, 1.0f, 1.0f);
	DesenhaPontosDeReferencia();
     


	// Inicializa a matriz de transformação corrente
	glLoadIdentity();
	gluOrtho2D(-range, range, -range, range);

	// Aplica uma translação sobre a Nave
	glTranslatef(Tx, Ty, 0.0f);

	// Desenha uma rotação sobre a Nave
	glTranslatef(0.0f,0.0f,0.0f);
	glRotatef(angle,0.0f,0.0f,1.0f);
	glTranslatef(0.0f,0.0f,0.0f);

	glColor3f(1.0f,1.0f,1.0f);
	DesenhaNave();



	// Inicializa a matriz de transformação corrente
	glLoadIdentity();
	gluOrtho2D(-range, range, -range, range);

	// Aplica uma translação sobre o asteroide
	glTranslatef(Tx_Asteroid, Ty_Asteroid, 0.0f);

	glColor3f(1.0f,1.0f,1.0f);
	DesenhaAsteroide();



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







double convertDegreesToRadians(double degrees) {
	return ((2*M_PI * degrees) / 360);
}

// Função callback chamada para gerenciar eventos de teclas especiais
void TeclasEspeciais(int key, int x, int y) {
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	
	if(key == 'w' || key == 'W') {
		// Lógica para mover para "cima"
		xStep += +cos(convertDegreesToRadians(angle + 90)) * 0.001f;
		yStep += +sin(convertDegreesToRadians(angle + 90)) * 0.001f;
	}
	if(key == 'a' || key == 'A') {
		// Lógica para mover para a esquerda
		angle+=5;
	}
	if(key == 's' || key == 'S') {
		// Lógica para mover para "baixo"
		xStep += -cos(convertDegreesToRadians(angle + 90)) * 0.001f;
		yStep += -sin(convertDegreesToRadians(angle + 90)) * 0.001f;
	}
	if(key == 'd' || key == 'D') {
		// Lógica para mover para a direita
		angle-=5;
	}
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
