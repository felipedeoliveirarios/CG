// GRUPO 3

// JOÃO PEDRO SILVA SOUSA
// CÁSSIO HENRIQUE PEREIRA COELHO
// ANTÔNIO SIDNEI MOREIRA CIRQUEIRA
// THIAGO DA SILVA FAGUNDES
// FELIPE DEO OLIVEIRA RIOS


/*
################################################################################
#   Seção de inclusão e opções do OpenGL
################################################################################
*/

#ifdef _WIN32
    #include "libs/glut.h"
    #include <windows.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#elif __unix__      
    #include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>

/*
################################################################################
#   Seção de constantes definidas pelo programador
################################################################################
*/

#define GL_SILENCE_DEPRECATION
#define WINDOW_WIDTH 640 // Largura da janela
#define WINDOW_HEIGHT 480 // Altura da janela
#define DEBUG 1 // Ativa/Desativa os prints de debug

/*
################################################################################
#   Seção de estruturas de dados
################################################################################
*/
typedef struct vertex2D{
    GLint x;
    GLint y;
} vertex2D;

typedef struct color3i{
    GLint r;
    GLint g;
    GLint b;
} color3i;

// Funcao personalizada para desenhar um pixel com uma cor
void putPixel(int x, int y, color3i color){
    glBegin(GL_POINTS);
    glColor3ub(color.r, color.g, color.b);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}


// Desenha os 8 pontos simetricos de uma circunferencia
void circlePoints (GLint x, GLint y, color3i c3i) {
    putPixel ( x,  y, c3i);
    putPixel ( x, -y, c3i);
    putPixel (-x,  y, c3i);
    putPixel (-x, -y, c3i);

    putPixel ( y,  x, c3i);
    putPixel ( y, -x, c3i);
    putPixel (-y,  x, c3i);
    putPixel (-y, -x, c3i);
}


void drawCircle (GLint r, color3i c3i) {
    GLint x;
    GLint y;
    GLfloat d;

    x = 0;
    y = r;
    d = (5.0/4.0) - r;

    circlePoints (x, y, c3i);

    while (y > x) {
        if (d < 0) {
            d += (2 * x) + 3;
            x++;
        }
        else {
            d += (2 * (x - y)) + 5;
            x++;
            y--;
        }
        circlePoints (x, y, c3i);
    }
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    color3i white = {255,255,255};
    color3i red = {255,0,0};

    drawCircle (200, white);

    glFlush();


}


/*
Função de inicialização.
*/
void init() {
    int width = glutGet(GLUT_SCREEN_WIDTH); // Pega a largura da tela
    int height = glutGet(GLUT_SCREEN_HEIGHT); // Pega a altura da tela
    int xpos = 100; // Posição inicial x da janela.
    int ypos = 100; // Posição inicial y da janela.
    if (width != 0 && height != 0){ // As funções retornam 0 caso desconhecido
        // centraliza a janela na tela.
        xpos = (width - WINDOW_WIDTH)/2;
        ypos = (height - WINDOW_HEIGHT)/2;
    }
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition (xpos, ypos);
    glutCreateWindow("Desenho de circunferencia");
    glutDisplayFunc(display);
    glClearColor(0,0,0,0); // Define a cor de limpeza da tela.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WINDOW_WIDTH/2, WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, WINDOW_HEIGHT/2); // Estabelece a área de visualização.
    printf("Projection Bounds:  (%d, %d, %d, %d).\n", -WINDOW_WIDTH/2, WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, WINDOW_HEIGHT/2);
}


int main(int argc, char** argv){
    glutInit(&argc, argv);
    init();
    glutMainLoop();
}
