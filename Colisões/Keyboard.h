
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
			// Lógica para mover para "cima"
			spaceship.xStep += 
				+cos(convertDegreesToRadians(spaceship.angle + SPACESHIP_OFFSET_ANGLE))
				*SPACESHIP_ACCELERATION;
			spaceship.yStep += 
				+sin(convertDegreesToRadians(spaceship.angle + SPACESHIP_OFFSET_ANGLE)) 
				*SPACESHIP_ACCELERATION;
			spaceshipWithAcceleration = true;
		}
		if(key == 'a' || key == 'A') {
			// Lógica para mover para a esquerda
			spaceship.angle+=SPACESHIP_ANGLE_STEP;
		}
		if(key == 's' || key == 'S') {
			// Lógica para mover para "baixo"
			spaceship.xStep += 
				-cos(convertDegreesToRadians(spaceship.angle + SPACESHIP_OFFSET_ANGLE)) 
				*SPACESHIP_ACCELERATION;
			spaceship.yStep += 
				-sin(convertDegreesToRadians(spaceship.angle + SPACESHIP_OFFSET_ANGLE)) 
				*SPACESHIP_ACCELERATION;
		}
		if(key == 'd' || key == 'D') {
			// Lógica para mover para a direita
			spaceship.angle-=SPACESHIP_ANGLE_STEP;
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
void TeclasEspeciais(int key, int x, int y) {
	glutPostRedisplay();
}
