

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

	glColor3f(redValue, greenValue, blueValue);

	switch (scene){
		case SCENE_MENU:
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);
			DrawInitialScreen("Click 'E' to change color", 0);
			DrawInitialScreen("Pedro Amaro", -7);
			DrawInitialScreen("Daniel Alencar", -9);
			break;

		case SCENE_START:
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);
			DrawInitialScreen("Click 'SPACE' to start", -5);

		case SCENE_GAME:
			// Inicializa a matriz de transformação corrente
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);
			
			if(scene == SCENE_GAME)
				drawText("Click 'ESC' to pause", -25, 23);	

			// Aplica uma translação sobre a Nave
			glTranslatef(spaceship.Tx, spaceship.Ty, 0.0f);

			// Desenha uma rotação sobre a Nave
			glTranslatef(0.0f,0.0f,0.0f);
			glRotatef(spaceship.angle,0.0f,0.0f,1.0f);
			glTranslatef(0.0f,0.0f,0.0f);

			DesenhaNave();

			// Inicializa a matriz de transformação corrente
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);

			// Aplica uma translação sobre a Nave
			glTranslatef(bullet.Tx, bullet.Ty, 0.0f);
			if(bulletExists) {
			  DesenhaBala();
			}
			
			// Inicializa a matriz de transformação corrente
			glLoadIdentity();
			if(levelDestructionAsteroid == 0) {
				gluOrtho2D(-range, range, -range, range);
			} else if(levelDestructionAsteroid == 1) {
				gluOrtho2D(-range * 1.5, range * 1.5, -range * 1.5, range * 1.5);
			}

			// Aplica uma translação sobre o asteroide
			if(levelDestructionAsteroid == 0) {
				glTranslatef(asteroid.Tx, asteroid.Ty, 0.0f);
				DesenhaAsteroide();

			} else if(levelDestructionAsteroid == 1) {
				glTranslatef(asteroid1.Tx, asteroid1.Ty, 0.0f);
				DesenhaAsteroide();
				glLoadIdentity();
				gluOrtho2D(-range * 1.5, range * 1.5, -range * 1.5, range * 1.5);
				glTranslatef(asteroid2.Tx, asteroid2.Ty, 0.0f);
				DesenhaAsteroide();
			}

			break;
		case SCENE_GAMEOVER:
			
			// Inicializa a matriz de transformação corrente
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);

			DrawInitialScreen("GAME OVER", 0);
			break;
		default:
			break;
	}

	// Executa os comandos OpenGL 
	glutSwapBuffers();
}