#ifndef TOOLS_H
#define TOOLS_H

#include "camera.h"

class QMouseEvent;

class Tool
{
public:
    virtual bool mousePressed(QMouseEvent *) = 0;
    virtual void mouseDragged(QMouseEvent *) {}
    virtual void mouseReleased(QMouseEvent *) {}
};

class OrbitCameraTool : public Tool
{
private:
    OrbitCamera &camera;
    int oldX, oldY;

public:
    OrbitCameraTool(OrbitCamera &camera) : camera(camera) {}

    bool mousePressed(QMouseEvent *event);
    void mouseDragged(QMouseEvent *event);
};

#endif // TOOLS_H
