
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
		glVertex2f(pointsNave[3].x, pointsNave[3].y);
		glVertex2f(pointsNave[4].x, pointsNave[4].y);
		glVertex2f(pointsNave[5].x, pointsNave[5].y);
		glVertex2f(pointsNave[6].x, pointsNave[6].y);
	glEnd();
	glPointSize(1);
	glBegin(GL_POINTS);
		glVertex2i(0,0);      
	glEnd();
	glLineWidth(2);
}

void DesenhaFogo() {
	Point p1_fogo = {+0.0, -2.0};
	Point p2_fogo = {+0.4, -1.0};
	Point p3_fogo = {-0.4, -1.0};

	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(p1_fogo.x, p1_fogo.y);
		glVertex2f(p2_fogo.x, p2_fogo.y);
		glVertex2f(p3_fogo.x, p3_fogo.y);
	glEnd();
	glPointSize(1);
	glBegin(GL_POINTS);
		glVertex2i(0,0);      
	glEnd();
}

int handleSize(int i){
	i++;

	int level = (int)log2(i);
	printf("Level: %d\n", level);

	return level + 1;
}

// Função para desenhar um asteróide
void DesenhaAsteroide(int size) {
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(pointsAsteroid[0].x / size, pointsAsteroid[0].y / size);
		glVertex2f(pointsAsteroid[1].x / size, pointsAsteroid[1].y / size);
		glVertex2f(pointsAsteroid[2].x / size, pointsAsteroid[2].y / size);
		glVertex2f(pointsAsteroid[3].x / size, pointsAsteroid[3].y / size);
		glVertex2f(pointsAsteroid[4].x / size, pointsAsteroid[4].y / size);
		glVertex2f(pointsAsteroid[5].x / size, pointsAsteroid[5].y / size);
		glVertex2f(pointsAsteroid[6].x / size, pointsAsteroid[6].y / size);
		glVertex2f(pointsAsteroid[7].x / size, pointsAsteroid[7].y / size);
		glVertex2f(pointsAsteroid[8].x / size, pointsAsteroid[8].y / size);
		glVertex2f(pointsAsteroid[9].x / size, pointsAsteroid[9].y / size);
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
			DrawInitialScreen("Press 'E' to change color", 0);
			DrawInitialScreen("Pedro Amaro", -7);
			DrawInitialScreen("Daniel Alencar", -9);
			break;

		case SCENE_START:
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);
			DrawInitialScreen("Press 'SPACE' to start", -5);

		case SCENE_GAME:
			// Inicializa a matriz de transformação corrente
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);
			
			if(scene == SCENE_GAME){
				drawText("Press 'ESC' to pause", -25, 23);

				for( int i = 0; i < lives; i++){
					glLoadIdentity();
					gluOrtho2D(-range, range, -range, range);
					glTranslatef(23 -3*i, 23, 0.0f);
					DesenhaNave();
				}
			}
					
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);
			// Aplica uma translação sobre a Nave
			glTranslatef(spaceship.Tx, spaceship.Ty, 0.0f);

			// Desenha uma rotação sobre a Nave
			glRotatef(spaceship.angle,0.0f,0.0f,1.0f);

			DesenhaNave();
			if(spaceshipWithAcceleration) {
				glLoadIdentity();
				gluOrtho2D(-range, range, -range, range);

				glTranslatef(spaceship.Tx, spaceship.Ty, 0.0f);
				glRotatef(spaceship.angle,0.0f,0.0f,1.0f);
				DesenhaFogo();
			}

			// Inicializa a matriz de transformação corrente
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);

			// Aplica uma translação sobre a bala
			glTranslatef(bullet.Tx, bullet.Ty, 0.0f);
			if(bulletExists) {
			  DesenhaBala();
			}
			
			// Desenha os asteroides
			winCondition = true;
			
			for(int j = 0; j < ASTEROIDS_ARRAY_QUANTITY; j++) {
				Object_transformation *asteroidsArray = asteroidsArraysArray[j];

				for(int i = 0; i < ASTEROIDS_LENGTH_ARRAY; i++) { 
					if(asteroidsArray[i].enable) {
						winCondition = false;
						glLoadIdentity();
						gluOrtho2D(-range, range, -range, range);

						glTranslatef(asteroidsArray[i].Tx, asteroidsArray[i].Ty, 0.0f);
						DesenhaAsteroide(asteroidsArray[i].size);
					}
				}
			}
			if(winCondition){
				scene = SCENE_WIN;
			}

			break;
		case SCENE_GAMEOVER:
			
			// Inicializa a matriz de transformação corrente
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);

			DrawInitialScreen("GAME OVER", 0);
			break;
			
		case SCENE_WIN:
			// Inicializa a matriz de transformação corrente
			glLoadIdentity();
			gluOrtho2D(-range, range, -range, range);

			DrawInitialScreen("YOU WON!", 0);
			break;
			
		default:
			break;
	}

	// Executa os comandos OpenGL 
	glutSwapBuffers();
}