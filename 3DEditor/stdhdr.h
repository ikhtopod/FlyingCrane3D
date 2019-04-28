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

#include <imgui.h>
#include <imgui_impl_glfw.h>

#undef IMGUI_IMPL_OPENGL_LOADER_GL3W
#undef IMGUI_IMPL_OPENGL_LOADER_GLEW
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <numeric>
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
#include "GUI.h"
#include "CameraSwitcher.h"
#include "Camera.h"
#include "TargetCamera.h"
#include "FreeCamera.h"
#include "Scene.h"
#include "Vertex.h"
#include "Edge.h"
#include "Face.h"
#include "SelectionInfo.h"
#include "SelectionSwitcher.h"
#include "Selection.h"
#include "SelectionObject.h"
#include "SelectionPoint.h"
#include "SelectionEdge.h"
#include "SelectionFace.h"
#include "Mesh.h"
#include "Object.h"
#include "GridObject.h"
#include "Axis.h"
#include "Shader.h"
#include "Projection.h"
#include "Model.h"


#endif // !STDHDR_H
