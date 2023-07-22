#include <GL/glut.h>

// Variáveis para controlar a posição do personagem
float characterX = 0.0f;
float characterY = 0.0f;

// Variáveis para controlar o estado das teclas
bool keyUpPressed = false;
bool keyDownPressed = false;
bool keyLeftPressed = false;
bool keyRightPressed = false;

// Função de temporizador que atualiza a posição do personagem
void updateCharacterPosition(int value) {
    if (keyUpPressed) {
        // Tecla para cima pressionada, move o personagem para cima
        characterY += 0.01f;
    }

    if (keyDownPressed) {
        // Tecla para baixo pressionada, move o personagem para baixo
        characterY -= 0.01f;
    }

    if (keyLeftPressed) {
        // Tecla para esquerda pressionada, move o personagem para a esquerda
        characterX -= 0.01f;
    }

    if (keyRightPressed) {
        // Tecla para direita pressionada, move o personagem para a direita
        characterX += 0.01f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateCharacterPosition, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Renderiza o personagem na posição atual
    glPushMatrix();
    glTranslatef(characterX, characterY, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCube(0.2);
    glPopMatrix();

    glutSwapBuffers();
}

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

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Controle de Personagem");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeyDownCallback);
    glutSpecialUpFunc(specialKeyUpCallback);
    glutTimerFunc(0, updateCharacterPosition, 0);

    glutMainLoop();
    return 0;
}
