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

int gene;
float s = 1.0; //length of the toothpick
float length = 1.0;
float depth=1.0;

void adjustDepth(){
    
        if ( s == 1 ) { //check if the size is smaller than 1
    
            depth = -gene/5;
            length = 1;
    
        }else if( s < 1 && gene <= 10 ){
    
            depth = -(gene+2/s);
            length = 10;
    
        }else if( s< 1 && gene > 10){
    
            depth = -12;
            length = 10;
        //    std::cout << depth<<"\n" ;
    
        }else if( s > 1 && gene <=10){
    
            length = (gene/pow(s,gene));
            if(length <= 0) length++;
            depth = -(gene*s)/1.8;
    
        }else{
            depth = -14;
            length = gene/pow(s,gene);
        }
    
/**
 *  This is recusively drawing the toothpick
 *  @param x - x and y coodinates of the current origin
 *  @param y - x and y coodinates of the current origin
 *  @param g - how many left to draw
 *  @param s - size
 */
void toothpick(float x, float y, int g, float len)
{
    if(g == 0){
        
        return;
        
    } else if (gene % 2 == 0) {
        
        if (g%2 == 0) {
            
            
            glBegin(GL_LINES);
            
            glVertex3f( x+len/2, y+len*s/2, depth );
            glVertex3f( x+len/2, y-len*s/2, depth );
            
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x-len/2, y+len*s/2, depth );
            glVertex3f( x-len/2, y-len*s/2, depth);
            glEnd();
            
            toothpick( x+len/2, y, g-1, len*s);
            toothpick( x-len/2, y, g-1, len*s);
            
            
            
        }else{
            
            glBegin(GL_LINES);
            glVertex3f( x+len*s/2, y+len/2, depth );
            glVertex3f( x-len*s/2, y+len/2, depth );
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x+len*s/2, y-len/2, depth );
            glVertex3f( x-len*s/2, y-len/2, depth );
            glEnd();
            
            toothpick(x, y+len/2, g-1, len*s);
            toothpick(x, y-len/2, g-1, len*s);
        }
        
        
    } else{
        
        if (g%2 == 1) {
            glBegin(GL_LINES);
            glVertex3f( x+len/2, y+len*s/2, depth );
            glVertex3f( x+len/2, y-len*s/2, depth );
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x-len/2, y+len*s/2, depth );
            glVertex3f( x-len/2, y-len*s/2, depth );
            glEnd();
            
            toothpick( x+len/2, y, g-1, len*s);
            toothpick( x-len/2, y, g-1, len*s);
            
        }else{
            glBegin(GL_LINES);
            glVertex3f( x+len*s/2, y+len/2, depth );
            glVertex3f( x-len*s/2, y+len/2, depth );
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x+len*s/2, y-len/2, depth );
            glVertex3f( x-len*s/2, y-len/2, depth );
            glEnd();
            
            toothpick(x, y+len/2, g-1, len*s);
            toothpick(x, y-len/2, g-1, len*s);
        }
        
    }
    
}


void drawToothpick(float x, float y, int g, float s){
    
    glBegin(GL_LINES);
    glVertex3f( x-length/2 , y, depth );
    glVertex3f( x+length/2 , y, depth );
    glEnd();
    
    toothpick(x, y, g, s);
}




void display(void)
{
    /* clear the matrix */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // set camera view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set the camera
    gluLookAt(	x, 0.0f, z,        //specify the eye
              x+lx, 0.0+ly,  z+lz,   //
              0.0f, 1.0f,  0.0f);
    
    /* modeling transformation */
    glPushMatrix();
    
    adjustDepth();
    
    drawToothpick(0, 0, gene, length);
    
    
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
    
    std::cout << "Please enter the generation: ";
    std::cin >> gene;
    std::cout << "Please enter the size: ";
    std::cin >> s;
    
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
