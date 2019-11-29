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
typedef struct vertex2D {
    GLfloat x;
    GLfloat y;
} vertex2D;

typedef struct vertex3D {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vertex3D;

typedef struct scaleOffset {
    GLfloat sx; // escala eixo x
    GLfloat sy; //        eixo y
    GLfloat sz; //        eixo z
    GLfloat ox; // offset eixo x
    GLfloat oy; //        eixo y
    GLfloat oz; //        eixo z
} scset;

typedef struct color3i {
    GLint r;
    GLint g;
    GLint b;
} color3i;

typedef struct color3f {
    GLfloat r;
    GLfloat g;
    GLfloat b;
} color3f;


vertex3D vertA = { 50, 50, 50};
vertex3D vertB = {-50, 50, 50};
vertex3D vertC = {-50,-50, 50};
vertex3D vertD = { 50,-50, 50};
vertex3D vertE = { 50, 50,-50};
vertex3D vertF = {-50, 50,-50};
vertex3D vertG = {-50,-50,-50};
vertex3D vertH = { 50,-50,-50};

scset defsc = {1,1,0,0,0,0}; // mantem eixo x e y na mesma escala
                             // eixo z será eliminado

/*
bx = (sx * ax) + (0 * ay) + (0 * az) + cx
by = (0 * ax) + (sy * ay) + (0 * az) + cz
bz = 0
*/


GLfloat bx (vertex3D v, scset sc) {
    return (v.x * sc.sx) + sc.ox;
}

GLfloat by (vertex3D v, scset sc) {
    return (v.y * sc.sy) + sc.oz;
}


void drawQuads (vertex3D v[], color3f c) {
    glBegin (GL_POLYGON);
    glColor3f (c.r, c.g, c.b);

    int i;
    for (i = 0; i < 4; i++) {
        glVertex2f (bx (v[i], defsc), by (v[i], defsc));
    }

    glEnd ();
}


void putPixel(int x, int y, color3i color){
    glBegin(GL_POINTS);
    glColor3ub(color.r, color.g, color.b);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

/* front => ABCD yellow */
color3f yellow = {1.0,1.0,0.0};
/* back => FEHG red */
color3f red = {1.0,0.0,0.0};
/* right => EADH green */
color3f green = {0.0,1.0,0.0};
/* left => BFGC blue */
color3f blue = {0.0,0.0,1.0};
/* top => EFBA turquoise */
color3f turq = {0.0,1.0,1.0};
/* bottom => DCGH pink */
color3f pink = {1.0,0.0,1.0};

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);

    vertex3D v1[] = {vertA,vertB,vertC,vertD};
    drawQuads (v1, yellow);

    vertex3D v2[] = {vertF,vertE,vertH,vertG};
    drawQuads (v2, red);

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
    glutCreateWindow("Teste de Traçado de Retas");
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
