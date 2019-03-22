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

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>

// future include: imgui

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <cstddef>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <memory>
#include <filesystem>
#include <chrono>
#include <thread>


/* app headers */

#include "ITriada.h"

#include "Util.h"

#include "DeltaTime.h"
#include "ScreenResolution.h"
#include "Application.h"
#include "Window.h"
#include "CameraSwitcher.h"
#include "Camera.h"
#include "FreeCamera.h"
#include "TargetCamera.h"
#include "Scene.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Object.h"
#include "GridObject.h"
#include "Axis.h"
#include "Shader.h"
#include "Model.h"


#endif // !STDHDR_H
