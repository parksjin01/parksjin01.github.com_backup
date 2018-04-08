//
//  HW1.c
//  OpenGL_Tutorial
//
//  Created by 박성진 on 2018. 4. 2..
//  Copyright © 2018년 ZG. All rights reserved.
//

/**
 @file Graphics.c
 @breif Drawing Sun, Earth and Moon, animate their rotation and revolution
 @author Seong Jin Park
 @return None
 @remark None
 @version 1.0
 */

#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>

/**
 @details hour represents cumulative time from 0, no upper limitation.
 @details hour increase 1 per each 0.1 second
 */
GLfloat hour = 0;

/**
 @brief Initialize
 @details Initialize configuration and call setting functions for openGL
 @author Seong Jin Park
 @version 1.0
 @date 2018.04.07
 @pre Called by main function
 @param None
 */
void init()
{
    glMatrixMode(GL_PROJECTION);                                // Setting projection matrix as identity matrix
    glLoadIdentity();
    
    glClearColor(1, 1, 1, 1);                                   // Setting background color as white
    glOrtho(-1, 1, -1, 1, -5, 5);                               // Setting Ortho coordinate system
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_MODELVIEW);                                 // Setting ModelView matrix will be changed
}

/**
 @brief Display
 @details Display Sun, Earth and Moon and animate their rotation and revolution
 @author Seong Jin Park
 @version 1.0
 @date 2018.04.07
 @pre Called by OS. kind of callback function
 @param None
 */
void display()
{
    GLfloat axis = -23.5;                                       // Represents inclination of Earth rotation axis
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);           // Clear existing model in window
    
    glLoadIdentity();                                           // Load identity matrix
    glColor3f(1, 0, 0);                                         // Choose color of Sun as red
    glPushMatrix();                                             // Push current ModelView Matrix
    glRotatef(90, 1, 0, 0);                                 // Rotate 90 degree with x axis as center axis. (Sun polar area will be go up)
    glutWireSphere(0.2, 20, 16);                            // Draw Sun
    glPopMatrix();                                              // Pop matrix and ModelView matrix will be changed as pushed matrix
    glPushMatrix();                                             // Push current ModelView matrix
    glRotatef(1.0/365*hour/24*360, 0, 1, 0);                // Rotate earth as !!!!!
    glTranslatef(0.7, 0, 0);                                // Move frame !!!!!!!!!!
    glRotatef(-1.0/365*hour/24*360, 0, 1, 0);               // Rotate again !!!!!!!!
    glColor3f(0, 0, 1);                                     // Choose color of Earch as blue
    glPushMatrix();                                         // Push current ModelView Matrix
    glRotatef(90, 1, 0, 0);                             // Rotate 90 degree with x axis as center axis. (Earth polar area will be go up)
    glRotatef(axis, 0, 1, 0);                           // Rotate -23.5 degree with y axis as center axis (Represent Earth rotate axis)
    glRotatef(hour/24*360, 0, 0, 1);                        // Rotate Earth to represent Earth rotation
    glutWireSphere(0.1, 10, 8);                            // Draw Earth
    glPopMatrix();                                          // Pop matrix and ModelView matrix will be changed as pushed matrix
    glPushMatrix();                                             // Push current ModelView Matrix
    glRotatef(hour/24/30*360, 0, 1, 0);                     // Rotate Moon to represent Moon revolution
    glTranslatef(0.2, 0, 0);                                // Move frame !!!!!
    glColor3f(0, 1, 1);                                     // Choose color of Moon as skyblue
    glRotatef(90, 1, 0, 0);
    glutWireSphere(0.04, 10, 8);                             // Draw Moon
    glPopMatrix();                                              // Pop matrix and ModelView matrix will be changed as pushed matrix
    glPopMatrix();                                              // Pop matrix and ModelView matrix will be changed as pushed matrix
    glutSwapBuffers();                                          // Flush
}


/**
 @brief Timer
 @details Increase 1 hour per 0.1 second, call display function and set timer again
 @author Seong Jin Park
 @version 1.0
 @date 2018.04.07
 @pre Callback function for timer event
 @param t timer value
 */
void timer(int t)
{
    hour += 1;                                                  // Increase hour per every 0.1 second
    glutPostRedisplay();                                        // Redisplay the model
    glutTimerFunc(100, timer, t);                                 // Setting timer function again
}

/**
 @brief Main function
 @details Initializing glut function
 @author Seong Jin Park
 @version 1.0
 @date 2018.04.07
 @pre First initialize the system
 @param argc number of parameters
 @param argv string of parameter
 */
int main(int argc, char *argv[])
{
    glutInit(&argc, (char**) argv);                             // Initialize state variable in glut and handle window session
    glutInitWindowSize(500, 500);                               // Initialize window size, height as 500 and width as 500
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);       // Setting display mode
    glutCreateWindow("Homework #1");                            // Create window with title name as "Homework #1"
    glutDisplayFunc(display);                                   // Setting display callback function
    //    glutKeyboardFunc(keyboard_handler);
    glutTimerFunc(100, timer, 0);                               // Setting timer callback function with interval 0.1 second
    //    glutIdleFunc(timer);
    init();                                                     // Call init function
    glutMainLoop();                                             // Start glut loop
}

