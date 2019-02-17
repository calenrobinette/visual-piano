
// C code to create a "visual piano" using
// opengl and termios. The goal is to showcase
// the use of C to actively recieve input and 
// rerout to visual output. Eventually, this
// will be used in conjunction with a sound
// library to create a basic synthesizer

// Author: Calen Robinette

// Date: 2/12/2019

#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <math.h> 
#include <time.h> 
#include <GL/glew.h>
#include <GL/glut.h> 
  
// window size 
#define maxWD 1280
#define maxHT 960 

// Array for the current state of each key (pressed/not pressed)
bool keyStates[256] = { false };
// Array for the current heights of each bar
float heights[256] = { 0 };
  
// 
// this creates delay between two actions 
void delay(unsigned int mseconds) 
{ 
    clock_t goal = mseconds + clock(); 
    while (goal > clock()) 
        ; 
} 
void drawBar(float x, float y, float c1, float c2, float c3) 
{ 
    glBegin(GL_POLYGON);
	    glColor3f(c1, c2, c3);
	    glVertex2f(-1.0f+x, -1.0f);
	    glVertex2f(-0.6f+x, -1.0f);
	    glVertex2f(-0.6f+x, -1.0f+y);
	    glVertex2f(-1.0f+x, -1.0f+y);
    glEnd();
} 

// this function will translate the point 
void scaleBarUp(char key, float x, float c1, float c2, float c3) 
{ 

    // glClear(GL_COLOR_BUFFER_BIT); 

    // update height
    if (heights[key] <= 2.0f) {
    	heights[key] += 0.005f;
    }

    drawBar(x, heights[key], c1, c2, c3);
    // glFlush();
    // glutSwapBuffers(); 
} 

// this function will translate the point 
void scaleBarDown(char key, float x, float c1, float c2, float c3) 
{ 

    // glClear(GL_COLOR_BUFFER_BIT); 

    // update height
    if (heights[key] > 0.0f)
    heights[key] -= 0.005f;

    drawBar(x, heights[key], c1, c2, c3);
    // glFlush();
    // glutSwapBuffers();

}

void keyOperations (void) {
	if (keyStates['a']) {
		scaleBarUp('a', 0.0f, 0.815f, 0.647f, 0.752f);
	} else {
		scaleBarDown('a', 0.0f, 0.815f, 0.647f, 0.752f);
	}

	if (keyStates['s']) {
		scaleBarUp('s', 0.4f, 0.862f, 0.839f, 0.968f);
	} else {
		scaleBarDown('s', 0.4f, 0.862f, 0.839f, 0.968f);
	}

	if (keyStates['d']) {
		scaleBarUp('d', 0.8f, 0.419f, 0.305f, 0.443f);
	} else {
		scaleBarDown('d', 0.8f, 0.419f, 0.305f, 0.443f);
	}

	if (keyStates['f']) {
		scaleBarUp('f', 1.2f, 0.329f, 0.415f, 0.482f);
	} else {
		scaleBarDown('f', 1.2f, 0.329f, 0.415f, 0.482f);
	}

	if (keyStates['g']) {
		scaleBarUp('g', 1.6f, 0.568f, 0.717f, 0.780f);
	} else {
		scaleBarDown('g', 1.6f, 0.568f, 0.717f, 0.780f);
	}
	glFlush();
	glutSwapBuffers();
}

void keyPressed (unsigned char key, int x, int y) {
	keyStates[key] = true;
}

void keyUp (unsigned char key, int x, int y) {
	keyStates[key] = false;
}

void display(void) {
    keyOperations();
	glClearColor(0.0f, 0.1f, 0.1f, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
    // glutKeyboardFunc(keyPressed);
    // glutKeyboardUpFunc(keyUp);
	glLoadIdentity();
	
	glutPostRedisplay();
}

void idle() {
	glutPostRedisplay();
}

void main(int argc, char** argv) 
{ 
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE); 
    glutInitWindowSize(maxWD, maxHT); 
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("Visual Piano"); 

    glutDisplayFunc(display); 
    glutIdleFunc(idle);


    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);

    glutMainLoop(); 
} 
