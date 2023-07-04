#include <GL/glut.h>

void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Obtém as dimensões da janela
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Define o texto que será exibido
    const char* text = "Texto centralizado";

    // Define o tamanho do texto
    float textSizeX = glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)text);
    float textSizeY = glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, 'X');

    // Calcula as coordenadas para centralizar o texto
    float textPosX = (windowWidth - textSizeX) / 2;
    float textPosY = (windowHeight - textSizeY) / 2;

    // Desenha o texto centralizado
    glColor3f(1.0, 1.0, 1.0);
    drawText(text, textPosX, textPosY);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutCreateWindow("Texto Centralizado");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
