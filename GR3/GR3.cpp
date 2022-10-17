#define _USE_MATH_DEFINES
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

void display();
void reshape(int, int);
void timer(int);
void processNormalKeys(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

float rx = 0;
float ry = 0;
float rz = -10;
float angle_x = 0;
float angle_y = 0;
float angle_z = 0;
float sc = 1;
float angle = sqrt(2) / 2;
double alpha;
int N, R;

struct vec3 {
    double x;
    double y;
    double z;
};

vector<vec3> colors;

vector<vec3> up
{
    {1, 0, 1},
    {1 * angle, 1 * angle, 1},
    {0, 1, 1},
    {-1 * angle, 1 * angle, 1},
    {-1, 0, 1},
    {-1 * angle, -1 * angle, 1},
    {0, -1, 1},
    {1 * angle, -1 * angle, 1},
};

vector<vec3> down
{
    {1, 0, -1},
    { 1 * angle, 1 * angle, -1 },
    { 0, 1, -1 },
    { -1 * angle, 1 * angle, -1 },
    { -1, 0, -1 },
    { -1 * angle, -1 * angle, -1 },
    { 0, -1, -1 },
    { 1 * angle, -1 * angle, -1 },
};

vector<vec3> points
{
    {0, 0, 0}
};


void calculator()
{
    alpha = M_PI - M_PI * (N - 2) / N;
}

void colgener()
{
    double a, b, c;
    for (int i = 0; i < N; i++) {
        a = (rand() % 255);
        a = a / 255;
        b = (rand() % 255);
        b = b / 255;
        c = (rand() % 255);
        c = c / 255;
        colors.push_back({ a, b, c });
    }
}

void filler()
{
    double ang = M_PI / (N + 1);
    double angle_c = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; i < N; j++)
        {
            angle_c += ang;
            points.push_back({});
        }
    }

}

void init()
{
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);

}

int main(int argc, char** argv)
{
    cout << "Input accuracy: ";
    cin >> N;
    //colgener();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(200, 200);
    glutInitWindowSize(900, 900);

    glutCreateWindow("win-1");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(processNormalKeys);
    glutMouseFunc(mouse);

    init();

    glutMainLoop();
    return 0;
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(rx, ry, rz);
    glRotatef(angle_x, 1, 0, 0);
    glRotatef(angle_y, 0, 1, 0);
    glRotatef(angle_z, 0, 0, 1);
    glScalef(sc, sc, sc);
    //glPointSize(6.0);
    //draw

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0, 0.9);
    for (auto& p: up )
    {
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.9, 0, 0.3);
    for (auto& p : down)
    {
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.9, 0, 0.3);
    for (auto& p : down)
    {
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    
    for (int i = 1; i < 8; i++)
    {
        glBegin(GL_POLYGON);
        glColor3f(colors[i-1].x, colors[i-1].y, colors[i-1].z);

        glVertex3f(down[i - 1].x, down[i - 1].y, down[i - 1].z);
        glVertex3f(up[i - 1].x, up[i - 1].y, up[i - 1].z);
        
        glVertex3f(up[i].x, up[i].y, up[i].z);
        glVertex3f(down[i].x, down[i].y, down[i].z);
        

        glEnd();
    }

    glBegin(GL_POLYGON);
    glColor3f(colors[8].x, colors[8].y, colors[8].z);

    glVertex3f(down[7].x, down[7].y, down[7].z);
    glVertex3f(up[7].x, up[7].y, up[7].z);

    glVertex3f(up[0].x, up[0].y, up[0].z);
    glVertex3f(down[0].x, down[0].y, down[0].z);


    glEnd();
    
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 2, 50);
    glMatrixMode(GL_MODELVIEW);

}
void timer(int k)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}
void mouse(int button, int state, int x, int y)
{
    if (button == 3)
    {
        rz += 1;
    }
    else if (button == 4)
    {
        rz -= 1;
    }

    /*else if (button == GLUT_RIGHT_BUTTON)
    {
        leftMouseButtonDown = (state == GLUT_DOWN);
        zMovement -= 0.1f;
    }*/

    // Save the mouse position
    ///mouseXPos = x;
    ///mouseYPos = y;
    glutPostRedisplay();
}
void processNormalKeys(unsigned char key, int x, int y) {
    switch (key)
    {
        case 'w': angle_x -= 1; break;
        case 's': angle_x += 1; break;
        case 'd': angle_z += 1; break;
        case 'a': angle_z -= 1; break;
        case 'q': angle_y -= 1; break;
        case 'e': angle_y += 1; break;
    }
    glutPostRedisplay();
}