
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

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
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

		bulletExists = true;

		bullet.Tx = spaceship.Tx;
		bullet.Ty = spaceship.Ty;

		// Tiro
		bullet.xStep = cos(convertDegreesToRadians(
			spaceship.angle + SPACESHIP_OFFSET_ANGLE
		)) * BULLET_SPEED;
		bullet.yStep = sin(convertDegreesToRadians(
			spaceship.angle + SPACESHIP_OFFSET_ANGLE
		)) * BULLET_SPEED;

		printf("Atirou!\n");
	}

	if(scene != SCENE_START) {
		if(key == 'w' || key == 'W') {
			pressUpArrow();
		}
		if(key == 'a' || key == 'A') {
			pressLeftArrow();
		}
		if(key == 's' || key == 'S') {
			pressDownArrow();
		}
		if(key == 'd' || key == 'D') {
			pressRightArrow();
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

// Função callback chamada para gerenciar eventos de teclas especiais
void specialKeyDownCallback(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_UP:
			pressUpArrow();
			break;

		case GLUT_KEY_DOWN:
			pressDownArrow();
			break;
		
		case GLUT_KEY_LEFT:
			pressLeftArrow();
			break;

		case GLUT_KEY_RIGHT:
			pressRightArrow();
			break;
	}
	glutPostRedisplay();
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