
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
	if(key == ' ') {
		if (scene == 0){
			scene = 2;
		}

    Tx_bullet = Tx;
    Ty_bullet = Ty;
		// Tiro
		bullet = true;
		xStep_bullet = cos(convertDegreesToRadians(angle + 90)) * 0.030f;
		yStep_bullet = sin(convertDegreesToRadians(angle + 90)) * 0.030f;
		printf("Atirou!\n");
	}
}

// Função callback chamada para gerenciar eventos de teclas especiais
void TeclasEspeciais(int key, int x, int y) {
	glutPostRedisplay();
}
