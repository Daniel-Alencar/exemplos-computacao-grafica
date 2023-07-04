
// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27) {
		if (scene == 1){
			scene = 2;
		}else if ( scene == 2){
			scene = 1;
		}
	}
	if(key == ' ') {
		if (scene == 0){
			scene = 2;
		}

		bullet.Tx = spaceship.Tx;
		bullet.Ty = spaceship.Ty;
		// Tiro
		bulletExists = true;
		bullet.xStep = cos(convertDegreesToRadians(spaceship.angle + 90)) * 0.030f;
		bullet.yStep = sin(convertDegreesToRadians(spaceship.angle + 90)) * 0.030f;
		printf("Atirou!\n");
	}

	if(scene != 0) {
		if(key == 'w' || key == 'W') {
			// Lógica para mover para "cima"
			spaceship.xStep += +cos(convertDegreesToRadians(spaceship.angle + 90)) * 0.001f;
			spaceship.yStep += +sin(convertDegreesToRadians(spaceship.angle + 90)) * 0.001f;
		}
		if(key == 'a' || key == 'A') {
			// Lógica para mover para a esquerda
			spaceship.angle+=5;
		}
		if(key == 's' || key == 'S') {
			// Lógica para mover para "baixo"
			spaceship.xStep += -cos(convertDegreesToRadians(spaceship.angle + 90)) * 0.001f;
			spaceship.yStep += -sin(convertDegreesToRadians(spaceship.angle + 90)) * 0.001f;
		}
		if(key == 'd' || key == 'D') {
			// Lógica para mover para a direita
			spaceship.angle-=5;
		}
	}
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas especiais
void TeclasEspeciais(int key, int x, int y) {
	glutPostRedisplay();
}
