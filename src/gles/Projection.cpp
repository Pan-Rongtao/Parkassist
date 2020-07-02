#include "parkassist/gles/Projection.h"
#include "glm/gtc/matrix_transform.hpp"
#include <math.h>

using namespace nb;

Projection::Projection()
	: matrix(1.0f)
{
}

void Projection::ortho(float left, float right, float bottom, float top, float near, float far)
{
	matrix = glm::ortho(left, right, bottom, top, near, far);
}

void Projection::perspective(float fovy, float aspect, float near, float far)
{
	matrix = glm::perspective(glm::radians(fovy), aspect, near, far);
}
