#ifndef __OPENGL_H__
#define __OPENGL_H__

// TODO: Currently Win32 only

#include <windows.h>

typedef unsigned int GLbitfield;
typedef unsigned int GLenum;
typedef float GLfloat;
typedef int GLint;

#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_TRIANGLES 0x0004

typedef void __stdcall gl_clear(GLbitfield mask);
typedef void __stdcall gl_begin(GLenum mode);
typedef void __stdcall gl_end(void);
typedef void __stdcall gl_color_3f(GLfloat red, GLfloat green, GLfloat blue);
typedef void __stdcall gl_vertex_2i(GLint x, GLint y);
typedef void __stdcall gl_flush(void);
typedef void __stdcall gl_rotate_f(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

gl_clear* glClear;
gl_begin* glBegin;
gl_end* glEnd;
gl_color_3f* glColor3f;
gl_vertex_2i* glVertex2i;
gl_flush* glFlush;
gl_rotate_f* glRotatef;

void gl_load()
{
    HMODULE lib = LoadLibraryW(L"OpenGL32.dll");

    glClear = (gl_clear*)GetProcAddress(lib, "glClear");
    glBegin = (gl_begin*)GetProcAddress(lib, "glBegin");
    glEnd = (gl_end*)GetProcAddress(lib, "glEnd");
    glColor3f = (gl_color_3f*)GetProcAddress(lib, "glColor3f");
    glVertex2i = (gl_vertex_2i*)GetProcAddress(lib, "glVertex2i");
    glFlush = (gl_flush*)GetProcAddress(lib, "glFlush");
    glRotatef = (gl_rotate_f*)GetProcAddress(lib, "glRotatef");
}

#endif