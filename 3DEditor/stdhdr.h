#pragma once

#ifndef STDHDR_H
#define STDHDR_H


#include <glad\glad.h>
#include <GLFW\glfw3.h>

// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// future include: imgui

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstddef>
#include <cmath>
#include <stdexcept>
#include <type_traits>



/* app headers */

#include "Util.h"
#include "Application.h"
#include "Window.h"
#include "ScreenResolution.h"
#include "DeltaTime.h"
#include "Scene.h"
#include "Vertex.h"
#include "Polygon.h"
#include "Mesh.h"
#include "Object.h"
#include "GridObject.h"
#include "Transform.h"
#include "Position.h"
#include "Rotation.h"
#include "Scale.h"
#include "ArithmeticVec3.h"
#include "Axis.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"


#endif // !STDHDR_H
