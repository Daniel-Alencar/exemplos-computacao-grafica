

// Função para desenhar a bala
void DesenhaBala() {
	glPointSize(5.0f);
	glBegin(GL_POINTS);
		glVertex2f(0,0); 
	glEnd();
}

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

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Limpa a janela de visualização com a cor de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	switch (scene){
		case 0:
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);

			DesenhaTelaInicial();


		case 1:
			
			break;
		case 2:
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

			// Aplica uma translação sobre a Nave
			glTranslatef(Tx_bullet, Ty_bullet, 0.0f);
			glColor3f(1.0f,1.0f,1.0f);
			DesenhaBala();

			// Inicializa a matriz de transformação corrente
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);

			// Aplica uma translação sobre o asteroide
			glTranslatef(Tx_Asteroid, Ty_Asteroid, 0.0f);

			glColor3f(1.0f,1.0f,1.0f);
			DesenhaAsteroide();
			break;
		default:
			break;
	}

	// Executa os comandos OpenGL 
	glutSwapBuffers();
}