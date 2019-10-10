// GRUPO 3

// JOÃO PEDRO SILVA SOUSA
// CÁSSIO HENRIQUE PEREIRA COELHO
// ANTÔNIO SIDNEI MOREIRA CIRQUEIRA
// THIAGO DA SILVA FAGUNDES
// FELIPE DEO OLIVEIRA RIOS


#define GL_SILENCE_DEPRECATION


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <string.h>
#include <stdlib.h>


typedef struct d2Vertex {
    GLfloat x;
    GLfloat y;
} d2Vertex;


typedef struct color3f {
    GLfloat r;
    GLfloat g;
    GLfloat b;
} color3f;


void cgTranslate (d2Vertex *polygon, GLint nVerts, GLfloat tx, GLfloat ty) {
    GLint i;

    glBegin (GL_POLYGON);
    for (i = 0; i < nVerts; i++) {
        glVertex2d (polygon[i].x + tx, polygon[i].y + ty);
    }
    glEnd ();
}


void cgScale (d2Vertex *polygon, GLint nVerts, GLfloat sx, GLfloat sy) {
    GLint i;

    glBegin (GL_POLYGON);
    for (i = 0; i < nVerts; i++) {
        glVertex2d (polygon[i].x * sx, polygon[i].y * sy);
    }
    glEnd ();
}


void cgRotate (d2Vertex *polygon, GLint nVerts, d2Vertex pivPt, GLfloat theta){
    GLint i;

    glBegin (GL_POLYGON);
    for (i = 0; i < nVerts; i++) {
        glVertex2f (pivPt.x + ((polygon[i].x - pivPt.x) * cos (theta)) - ((polygon[i].y - pivPt.y) * sin (theta)),
                    pivPt.y + ((polygon[i].x - pivPt.x) * sin (theta)) + ((polygon[i].y - pivPt.y) * cos (theta)));
    }
    glEnd ();
}

void cgDraw (d2Vertex *polygon, GLint nVerts, color3f color) {
    GLint i;

    glColor3f (color.r, color.g, color.b);
    glBegin (GL_POLYGON);

    for (i = 0; i < nVerts; i++) {
        glVertex2f (polygon[i].x, polygon[i].y);
    }

    glEnd ();
}


d2Vertex square[] = {{50,50},{100,50},{100,100},{50,100}};

d2Vertex sq_triangle[] = {{50,50},{100,50},{75,93.3}};

d2Vertex rectangle[] = {{50,50},{125,50},{125,100},{50,100}};

d2Vertex is_triangle[] = {{50,50},{100,50},{125,75}};

color3f red = {1,0,0};
color3f green = {0,1,0};
color3f blue = {0,0,1};
color3f black = {0,0,0};
color3f white = {1,1,1};
color3f custom = {0.5,1,0.1};


void display () {
    d2Vertex v = {50,50};
    glClear (GL_COLOR_BUFFER_BIT);

    cgDraw (square, 4, red);

    glColor3f (0,0,1);
    cgTranslate (square, 4, 50, 50);

    glColor3f (0,1,0);
    cgScale (square, 4, 0.5, 0.5);

    glColor3f (1,1,1);
    cgRotate (square, 4, v, (45 * M_PI)/180);


    glFlush();
}

void init() {
    glClearColor(0,0,0,0);
    gluOrtho2D(-240,240,-160,160);//estabeleca a area de visualizacao
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (480, 320);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    // glOrtho (0, 1, 0, 1, -1 ,1);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}