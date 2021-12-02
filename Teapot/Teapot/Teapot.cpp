//
//  Bounce.cpp
//  Bounce
//
//  Created by anker on 2021/7/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLUT/glut.h>

GLuint v,f,p;
float lpos[4] = {1, 0.5, 1.0};
float a = 0;
GLint time_id;

void ChangeSize(int w, int h) {
    printf("chage size: %d, %d\n", w, h);
    float ratio = 1.0 * w / h;
    // 再更改之前重设坐标系
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    // 设置正确的透视投影方法
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, -1.0,
              0.0, 1.0, 0.0f);
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glRotatef(a, 0, 1, 1);
    glutSolidTeapot(1);
    a += 0.1;
    glUniform1f(time_id, a);
    glutSwapBuffers();
}

const GLchar *vv = (const GLchar*)
"void main() {\n"
"    vec4 a;\n"
"    a = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
"    gl_Position.x = a.x;\n"
"    gl_Position.y = a.y;\n"
"}\n";

const GLchar *ff = (const GLchar*)
"uniform float v_time;\n"
"void main() {\n"
"   float fR = 0.9 * sin(0.0 + v_time*0.05) + 1.0;\n"
"   float fG = 0.9 * sin(0.33 + v_time*0.05) + 1.0;\n"
"   float fB = 0.9 * sin(0.67 + v_time*0.05) + 1.0;\n"
"   gl_FragColor = vec4(fR/2.0, fG/2.0, fB/2.0, 1.0);\n"
"}\n";

void setShaders() {
    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(v, 1, &vv, NULL);
    glShaderSource(f, 1, &ff, NULL);
    glCompileShader(v);
    glCompileShader(f);

    p = glCreateProgram();
    glAttachShader(p, v);
    glAttachShader(p, f);
    glLinkProgram(p);
    glUseProgram(p);

    time_id = glGetUniformLocation(p, "v_time");
}

int main(int argc, char *argv[]) {
    printf("hello opengl\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("GPGPU Tutorial");
    glutDisplayFunc(RenderScene);
    glutIdleFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_CULL_FACE);
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "glew error: %s\n", glewGetErrorString(err));
        return 1;
    }

    setShaders();

    glutMainLoop();
    return 0;
}
