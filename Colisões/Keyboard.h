
// Variáveis para controlar o estado das teclas
bool keyUpPressed = false;
bool keyDownPressed = false;
bool keyLeftPressed = false;
bool keyRightPressed = false;

void pressUpArrow() {
	// Lógica para mover para "cima"
	spaceship.xStep += 
		+cos(convertDegreesToRadians(spaceship.angle + SPACESHIP_OFFSET_ANGLE))
		*SPACESHIP_ACCELERATION;
	spaceship.yStep += 
		+sin(convertDegreesToRadians(spaceship.angle + SPACESHIP_OFFSET_ANGLE)) 
		*SPACESHIP_ACCELERATION;
	spaceshipWithAcceleration = true;
}

void pressDownArrow() {
	// Lógica para mover para "baixo"
	spaceship.xStep += 
		-cos(convertDegreesToRadians(spaceship.angle + SPACESHIP_OFFSET_ANGLE)) 
		*SPACESHIP_ACCELERATION;
	spaceship.yStep += 
		-sin(convertDegreesToRadians(spaceship.angle + SPACESHIP_OFFSET_ANGLE)) 
		*SPACESHIP_ACCELERATION;
}

void pressLeftArrow() {
	// Lógica para mover para a esquerda
	spaceship.angle+=SPACESHIP_ANGLE_STEP;
}

void pressRightArrow() {
	// Lógica para mover para a direita
	spaceship.angle-=SPACESHIP_ANGLE_STEP;
}

void updateMovesWithPressedKeys() {
	if(keyUpPressed) {
		pressUpArrow();
	}
	if(keyDownPressed) {
		pressDownArrow();
	}
	if(keyLeftPressed) {
		pressLeftArrow();
	}
	if(keyRightPressed) {
		pressRightArrow();
	}
}

// Função callback chamada para gerenciar eventos de teclas
void keyboardPressed(unsigned char key, int x, int y)
{
	if (key == 27) {
		if (scene == SCENE_MENU){
			scene = SCENE_GAME;
		}else if ( scene == SCENE_GAME){
			scene = SCENE_MENU;
		}
	}
	if(key == ' ') {
		if (scene == SCENE_START){
			scene = SCENE_GAME;
		}

		float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
		printf("Current Time: %f\n", currentTime);
		printf("Spaceship shoot Time: %f\n", spaceshipShootTime);

		if(currentTime - spaceshipShootTime > delayTimeShoot) {

			if(bulletsLength < 20) {
				bulletsLength++;

				bullets = (Object_transformation*) realloc(
					bullets, sizeof(Object_transformation) * bulletsLength
				);

				bullets[bulletsLength - 1].enable = true;

				bullets[bulletsLength - 1].Tx = spaceship.Tx;
				bullets[bulletsLength - 1].Ty = spaceship.Ty;

				// Tiro
				bullets[bulletsLength - 1].xStep = cos(convertDegreesToRadians(
					spaceship.angle + SPACESHIP_OFFSET_ANGLE
				)) * BULLET_SPEED;
				bullets[bulletsLength - 1].yStep = sin(convertDegreesToRadians(
					spaceship.angle + SPACESHIP_OFFSET_ANGLE
				)) * BULLET_SPEED;

			} else {
				for(int k = 0; k < bulletsLength; k++) {
					if(bullets[k].enable == false) {

						bullets[k].enable = true;
						bullets[k].Tx = spaceship.Tx;
						bullets[k].Ty = spaceship.Ty;

						bullets[k].xStep = cos(convertDegreesToRadians(
							spaceship.angle + SPACESHIP_OFFSET_ANGLE
						)) * BULLET_SPEED;
						bullets[k].yStep = sin(convertDegreesToRadians(
							spaceship.angle + SPACESHIP_OFFSET_ANGLE
						)) * BULLET_SPEED;

						break;
					}
				}
			}
			spaceshipShootTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
			printf("Atirou!\n");
			
		}
	}

	if(scene != SCENE_START) {
		if(key == 'w' || key == 'W') {
			keyUpPressed = true;
		}
		if(key == 'a' || key == 'A') {
			keyLeftPressed = true;
		}
		if(key == 's' || key == 'S') {
			keyDownPressed = true;
		}
		if(key == 'd' || key == 'D') {
			keyRightPressed = true;
		}
	}

	if(scene == SCENE_MENU) {
		if(key == 'e' || key == 'E') {
			currentColor++;
			if(currentColor > 3)
				currentColor = 0;
				
			switch (currentColor){
				case 0:
					redValue = 1.0f;
					greenValue = 1.0f;
					blueValue = 1.0f;
					break;
				case 1:
					redValue = 1.0f;
					greenValue = 0.0f;
					blueValue = 0.0f;
					break;
				case 2:
					redValue = 0.0f;
					greenValue = 1.0f;
					blueValue = 0.0f;
					break;
				case 3:
					redValue = 0.0f;
					greenValue = 0.0f;
					blueValue = 1.0f;
					break;
				default:
					break;
			}
		}
	}

	glutPostRedisplay();
}

void keyboardDespressed(unsigned char key, int x, int y) {
	if(key == 'w' || key == 'W') {
		keyUpPressed = false;
	}
	if(key == 'a' || key == 'A') {
		keyLeftPressed = false;
	}
	if(key == 's' || key == 'S') {
		keyDownPressed = false;
	}
	if(key == 'd' || key == 'D') {
		keyRightPressed = false;
	}
}

// Função callback chamada para gerenciar eventos de teclas especiais
void specialKeyDownCallback(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			// Tecla para cima pressionada
			keyUpPressed = true;
			break;
		case GLUT_KEY_DOWN:
			// Tecla para baixo pressionada
			keyDownPressed = true;
			break;
		case GLUT_KEY_LEFT:
			// Tecla para esquerda pressionada
			keyLeftPressed = true;
			break;
		case GLUT_KEY_RIGHT:
			// Tecla para direita pressionada
			keyRightPressed = true;
			break;
	}
}

// Função callback chamada para gerenciar eventos de teclas especiais
void specialKeyUpCallback(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			// Tecla para cima liberada
			keyUpPressed = false;
			break;
		case GLUT_KEY_DOWN:
			// Tecla para baixo liberada
			keyDownPressed = false;
			break;
		case GLUT_KEY_LEFT:
			// Tecla para esquerda liberada
			keyLeftPressed = false;
			break;
		case GLUT_KEY_RIGHT:
			// Tecla para direita liberada
			keyRightPressed = false;
			break;
	}
}