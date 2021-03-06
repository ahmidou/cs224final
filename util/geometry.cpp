#include "geometry.h"
#include "vector.h"
#include <qgl.h>

GLUquadric *quadric = NULL;
const float cubeVertices[8 * 3] =
{
    -1, -1, -1,
    +1, -1, -1,
    -1, +1, -1,
    +1, +1, -1,
    -1, -1, +1,
    +1, -1, +1,
    -1, +1, +1,
    +1, +1, +1,
};
const int cubeFaces[] =
{
    0, 2, 3, 1,
    4, 5, 7, 6,
    0, 1, 5, 4,
    2, 6, 7, 3,
    0, 4, 6, 2,
    1, 3, 7, 5,
};
const int cubeLines[] =
{
    0, 1, 2, 3, 4, 5, 6, 7,
    0, 2, 1, 3, 4, 6, 5, 7,
    0, 4, 1, 5, 2, 6, 3, 7,
};

static void initQuadric()
{
    if (!quadric)
        quadric = gluNewQuadric();
}

void drawCube()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, cubeVertices);
    glDrawElements(GL_QUADS, sizeof(cubeFaces) / sizeof(*cubeFaces), GL_UNSIGNED_INT, cubeFaces);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawSphere(int detail)
{
    initQuadric();
    gluSphere(quadric, 1, detail, detail / 2);
}

void drawCylinder(int detail)
{
    initQuadric();
    gluCylinder(quadric, 1, 1, 1, detail, 1);
}

void drawWireCube()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, cubeVertices);
    glDrawElements(GL_LINES, sizeof(cubeLines) / sizeof(*cubeLines), GL_UNSIGNED_INT, cubeLines);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawWireCube(const Vector3 &minCorner, const Vector3 &maxCorner)
{
    Vector3 center = (minCorner + maxCorner) / 2;
    Vector3 scale = (maxCorner - minCorner) / 2;
    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);
    glScalef(scale.x, scale.y, scale.z);
    drawWireCube();
    glPopMatrix();
}

void drawWireDisk()
{
    const int count = 64;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < count; i++)
    {
        float angle = (float)i / (float)count * M_2PI;
        glVertex2f(cosf(angle), sinf(angle));
    }
    glEnd();
}

void drawMoveCursor()
{
    glBegin(GL_LINE_LOOP);

    // +y
    glVertex2f(-0.2, 0.2);
    glVertex2f(-0.2, 0.6);
    glVertex2f(-0.4, 0.6);
    glVertex2f(0, 1);
    glVertex2f(0.4, 0.6);
    glVertex2f(0.2, 0.6);
    glVertex2f(0.2, 0.2);

    // +x
    glVertex2f(0.2, 0.2);
    glVertex2f(0.6, 0.2);
    glVertex2f(0.6, 0.4);
    glVertex2f(1, 0);
    glVertex2f(0.6, -0.4);
    glVertex2f(0.6, -0.2);
    glVertex2f(0.2, -0.2);

    // -y
    glVertex2f(0.2, -0.2);
    glVertex2f(0.2, -0.6);
    glVertex2f(0.4, -0.6);
    glVertex2f(0, -1);
    glVertex2f(-0.4, -0.6);
    glVertex2f(-0.2, -0.6);
    glVertex2f(-0.2, -0.2);

    // -x
    glVertex2f(-0.2, -0.2);
    glVertex2f(-0.6, -0.2);
    glVertex2f(-0.6, -0.4);
    glVertex2f(-1, 0);
    glVertex2f(-0.6, 0.4);
    glVertex2f(-0.6, 0.2);
    glVertex2f(-0.2, 0.2);

    glEnd();
}

void drawScaleCursor()
{
    glBegin(GL_LINE_LOOP);

    // +y
    glVertex2f(-0.2, 0.6);
    glVertex2f(-0.4, 0.6);
    glVertex2f(0, 1);
    glVertex2f(0.4, 0.6);
    glVertex2f(0.2, 0.6);

    // -y
    glVertex2f(0.2, -0.6);
    glVertex2f(0.4, -0.6);
    glVertex2f(0, -1);
    glVertex2f(-0.4, -0.6);
    glVertex2f(-0.2, -0.6);

    glEnd();
}
