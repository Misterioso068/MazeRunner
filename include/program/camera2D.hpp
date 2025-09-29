#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include <GL/glew.h>

struct Camera2D {
    GLfloat x, y;
    GLfloat zoom;
    Camera2D(GLfloat startX = 0, GLfloat startY = 0, GLfloat startZoom = 1.0f);
    void move(GLfloat dx, GLfloat dy);
    void setZoom(GLfloat z);
    void applyProjection(size_t mazeRows, size_t mazeCols);

    void zoomIn(GLfloat factor = 1.1f) {zoom *= factor;};
    void zoomOut(GLfloat factor = 1.1f) {zoom /= factor;};
};

#endif