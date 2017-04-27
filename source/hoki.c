#include "opengl.h"

void game_init(void)
{
    gl_load();
}

void game_render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    
    // Top
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2i(1, 1);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2i(-1, 1);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2i(0, 0);
    
    // Right
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(1, 1);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(0, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(1, -1);
    
    // Bottom
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2i(1, -1);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2i(0, 0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2i(-1, -1);
    
    // Left
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2i(-1, -1);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2i(0, 0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2i(-1, 1);
    
    glEnd();
    glFlush();
}