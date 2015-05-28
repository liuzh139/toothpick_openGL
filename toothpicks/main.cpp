//
//  main.cpp
//  toothpicks
//
//  Created by daisy_island on 20/03/15.
//  Copyright (c) 2015 daisy_island. All rights reserved.
//
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>

float angle=0.0; // angle of rotation for the camera direction
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f,ly=0.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;
float pi = 3.1415926535897932384626433832795;
float toothpickSize;
float length=1.0;
int gene;


/* Hints: 
    1. matrix pop up in the order of last in first out.
    2. do them all in backwords?
 */

void toothpick(int g){
    
    if (g == 0) {
        return;
    }
    
    if (g%2 == 1) {
        
     
        glTranslatef(length, 0, 0);
        glRotatef(90, 0, 0, 1);
        glBegin(GL_LINES);
        glVertex2f(-length, 0);
        glVertex2f(length, 0);
        glEnd();
  
        glTranslatef(0, (g*2)*length, 0);

        glBegin(GL_LINES);
        glVertex2f(-length, 0);
        glVertex2f(length, 0);
        glEnd();

        toothpick(g-1);
        toothpick(g-1);
        
    }else{
    
        glTranslatef(length, length, 0);
        glRotatef(180, 0, 0, 1);
        glBegin(GL_LINES);
        glVertex2f(-length, 0);
        glVertex2f(length, 0);
        glEnd();

        glTranslatef((g*2)*length, -length, 0);
        glRotatef(180, 0, 0, 1);
        glBegin(GL_LINES);
        glVertex2f(-length, 0);
        glVertex2f(length, 0);
        glEnd();

     
        
        toothpick(g-1);
        toothpick(g-1);

    }
    
    
    
    
}



void display(void)
{
    /* clear the matrix */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // set camera view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set the camera
    gluLookAt(	x, 0.0f, z,
              x+lx, 0.0+ly,  z+lz,
              0.0f, 1.0f,  0.0f);
    
    /* modeling transformation */
    glPushMatrix();
    
    gene = 2;
    toothpickSize = 1;
    
    /* Case 0 */
    glBegin(GL_LINES);
    glVertex2f(-length, 0);
    glVertex2f(length, 0);
    glEnd();
    
    toothpick(gene);

    glPopMatrix();
    glutSwapBuffers();
}

void init(void)
{
    glEnable(GL_DEPTH_TEST); /* enables the depth test to allow different objects show up in order. */
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
    
    float fraction = 1.0f;
    switch (key) {
        case 27:
        case 'q':
            exit(0);
            break;
        case 188:
        case 'w':
            x += lx * fraction;
            z += lz * fraction;
            break;
            
        case 83:
        case 's':
            x -= lx * fraction;
            z -= lz * fraction;
            break;
    }
}

void processSpecialKeys(int key, int xx, int yy) {
    
    switch (key) {
        case GLUT_KEY_LEFT :
            angle -= 0.05f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_RIGHT :
            angle += 0.05f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_UP :
            angle += 0.05f;
            ly= tan(angle);
            break;
        case GLUT_KEY_DOWN :
            angle -= 0.05f;
            ly= tan(angle);
            break;
    }
}

int main(int argc, char ** argv) {
  
//    std::cout << "Please enter the generation: ";
//    std::cin >> gene;
//    std::cout << "Please enter the size: ";
//    std::cin >> toothpickSize;
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE| GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (250, 250);
    glutCreateWindow (argv[0]);
    init();
    
    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(processSpecialKeys);
    glutPostRedisplay(); //repaint the screen.
    
    glutMainLoop();
    return 0;
}
