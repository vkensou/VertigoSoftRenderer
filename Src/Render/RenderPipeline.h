#pragma once

struct Vertex;
class Matrix;

void setModelMatrix(const Matrix& m);
void setModelIMatrix(const Matrix& m);
void setViewMatrix(const Matrix& m);
void setProjectionMatrix(const Matrix& m);

void setTarget(unsigned int* target, int width, int height);
void drawTriangle(Vertex *v, int count);