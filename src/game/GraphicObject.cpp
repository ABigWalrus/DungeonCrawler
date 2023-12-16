#include "GraphicObject.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <GL/glew.h>

#include <glfw3.h>

#include <glm/glm.hpp>

GraphicObject::GraphicObject(): M(glm::mat4(1.0f)){}

