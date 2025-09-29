#include "program/camera2D.hpp"

Camera2D::Camera2D(GLfloat startX, GLfloat startY, GLfloat startZoom) 
                   : x(startX), y(startY), zoom(startZoom) {}

void Camera2D::move(GLfloat dx, GLfloat dy) {
    x += dx;
    y += dy;
}

void Camera2D::setZoom(GLfloat z) {
    zoom = z;
}

void Camera2D::applyProjection(size_t mazeRows, size_t mazeCols) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(x, x + mazeCols * zoom, y + mazeRows * zoom, y, -1, 1); 
    glMatrixMode(GL_MODELVIEW);
}